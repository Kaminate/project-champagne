#include "Direct3D.h"
#include "ErrorMessage.h"

Direct3D::Direct3D(HWND hWnd) : driverType(D3D_DRIVER_TYPE_NULL),
                                featureLevel(D3D_FEATURE_LEVEL_11_0),
                                pSolidRS(NULL),
                                pWireframeRS(NULL)
                                //unsigned int frameCount(0)
                                //float framerate(0.0f)
                                //float timeElapsed(0.0f)
{
  InitD3D(hWnd);
  InitPipeline();
  InitGraphics();

  CreateRasterizerStates();

  HRESULT hr;

  ///////////////////////// 
  // Create Blend States //
  /////////////////////////
  if (true)
  {
    //
    // CREATE THE BLEND STATE Default
    D3D11_BLEND_DESC blendDescDefault;

    blendDescDefault.AlphaToCoverageEnable = false; // not sure what this is after reading it
    blendDescDefault.IndependentBlendEnable = true; //blend all rendertargets
    D3D11_RENDER_TARGET_BLEND_DESC rtvBlendDescDefault;
    rtvBlendDescDefault.BlendEnable = true;
    rtvBlendDescDefault.SrcBlend = D3D11_BLEND_ONE;
    rtvBlendDescDefault.DestBlend= D3D11_BLEND_ZERO;
    rtvBlendDescDefault.BlendOp = D3D11_BLEND_OP_ADD;
    rtvBlendDescDefault.SrcBlendAlpha = D3D11_BLEND_ONE;
    rtvBlendDescDefault.DestBlendAlpha = D3D11_BLEND_ZERO;
    rtvBlendDescDefault.BlendOpAlpha = D3D11_BLEND_OP_ADD;
    rtvBlendDescDefault.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL; //(default)
    for (int i = 0; i < 8; ++i)
    {
    blendDescDefault.RenderTarget[i] = rtvBlendDescDefault;
    }
    hr = device->CreateBlendState(&blendDescDefault,&pBlendStateDefault );
    if (FAILED(hr))
    {
      std::cout << "Failed to create a blend state!" << std::endl;
    }

    // CREATE THE BLEND STATE ALPHA
    D3D11_BLEND_DESC blendDescAdditive;
    D3D11_RENDER_TARGET_BLEND_DESC rtvBlendDescAlpha;
    blendDescAdditive.AlphaToCoverageEnable = false;
    blendDescAdditive.IndependentBlendEnable = false; //blend only rtv[0]
    rtvBlendDescAlpha.BlendEnable = true;
          // http://msdn.microsoft.com/en-us/library/windows/desktop/ff476200%28v=vs.85%29.aspx
  // The 1st comment guy billybaloop said that
  // SrcBlend is the number to multiply the source color by.
  // OutputPixel = ( SourceColor.rgba * SrcBlend ) __BlendOp__ ( DestColor.rgba * DestBlend )
    rtvBlendDescAlpha.SrcBlend = D3D11_BLEND_ONE;
    rtvBlendDescAlpha.DestBlend= D3D11_BLEND_ONE;
    rtvBlendDescAlpha.BlendOp = D3D11_BLEND_OP_ADD;//blend operation
    rtvBlendDescAlpha.SrcBlendAlpha = D3D11_BLEND_ONE;
    rtvBlendDescAlpha.DestBlendAlpha = D3D11_BLEND_ONE;
    rtvBlendDescAlpha.BlendOpAlpha = D3D11_BLEND_OP_ADD;//blend operation
    rtvBlendDescAlpha.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL; //(default)
    blendDescAdditive.RenderTarget[0] = rtvBlendDescAlpha;
    hr = device->CreateBlendState(&blendDescAdditive,&pBlendStateAdditive );
    if (FAILED(hr))
    {
      std::cout << "Failed to create a blend state!" << std::endl;
    }
  }

  //////////////////////////////////////////
  // Create the Fullscreen Texture Shader //
  //////////////////////////////////////////

  this->pFullscreenTextureShader = new FullscreenTextureShader();
  this->pFullscreenTextureShader->Initialize(device);

  ///////////////////////////////////
  // CREATE THE NORMAL MAP TEXTURE //
  ///////////////////////////////////

  // Screen Rect
  RECT rc;
  GetClientRect( hWnd, &rc );
  UINT width = rc.right - rc.left;
  UINT height = rc.bottom - rc.top;

  // normal map texture
  this->pSceneNormalMap = new RenderTexture;
  this->pSceneNormalMap->Initialize(device, DXGI_FORMAT_B8G8R8A8_UNORM, width, height);

  // testing my fullscreen texture shader
  std::string textureFilename( "Resources/seafloor.dds");
  pSampleTextureToTestMyShader = new RenderTexture;
  pSampleTextureToTestMyShader->InitializeFromFile(device, textureFilename, DXGI_FORMAT_B8G8R8A8_UNORM);

  // depth texture
  pSceneViewspaceDepth = new RenderTexture;
  pSceneViewspaceDepth->Initialize(device, DXGI_FORMAT_R32_FLOAT, width, height);

  // diffuse texture
  pSceneDiffuse = new RenderTexture;
  pSceneDiffuse->Initialize(device, DXGI_FORMAT_R8G8B8A8_UNORM, width, height);
}

Direct3D::~Direct3D()
{
  CleanD3D();
}

void Direct3D::InitD3D(HWND hWnd) // sets up and initializes Direct3D
{
  // Return value
  HRESULT hr = S_OK;

  // Screen Rect
  RECT rc;
  GetClientRect( hWnd, &rc );
  UINT width = rc.right - rc.left;
  UINT height = rc.bottom - rc.top;

  UINT createDeviceFlags = 0;
//#ifdef _DEBUG
  createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
//#endif

  D3D_DRIVER_TYPE driverTypes[] =
  {
    D3D_DRIVER_TYPE_HARDWARE,
    D3D_DRIVER_TYPE_WARP,
    D3D_DRIVER_TYPE_REFERENCE,
  };
  UINT numDriverTypes = ARRAYSIZE(driverTypes);

  D3D_FEATURE_LEVEL featureLevels[] =
  {
    D3D_FEATURE_LEVEL_11_0,
    D3D_FEATURE_LEVEL_10_1,
    D3D_FEATURE_LEVEL_10_0,
  };

  UINT numFeatureLevels = ARRAYSIZE(featureLevels);

  //////////////////////////////////
  // Creating the: Swapchain      //
  //               Device         //
  //               Device Context //
  //////////////////////////////////

  DXGI_SWAP_CHAIN_DESC scd;
  ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC)); // set everything to null
  scd.BufferCount = 1; // number of back buffers
  scd.BufferDesc.Width = width;
  scd.BufferDesc.Height = height;
  scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  scd.BufferDesc.RefreshRate.Numerator = 60;
  scd.BufferDesc.RefreshRate.Denominator = 1;
  scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  scd.OutputWindow = hWnd;

  // Important Note:

  // According to MSDN:
  // http://msdn.microsoft.com/en-us/library/windows/desktop/bb173072%28v=vs.85%29.aspx

  // The SampleDesc.Count and SampleDesc.Quality
  // must be THE SAME for ALL BOUND RENDER TARGETS and DEPTH BUFFERS
  // which makes sense I guess

  //HRESULT CheckMultisampleQualityLevels(
  //  [in]   DXGI_FORMAT Format,
  //  [in]   UINT SampleCount,
  //  [out]  UINT *pNumQualityLevels
  //  );
  // Actually, I don't want to do this right now.
  // TODO: This (make the bound RENDERTARGET and DEPTHBUFFER
  //             1. use the same count/quality
  //             2. see what count/quality is supported by hardward

  scd.SampleDesc.Count = 1; // number of multisamples
  scd.SampleDesc.Quality = 0;
  scd.Windowed = true;
  scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;     // allow full-screen switching

  for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; ++driverTypeIndex)
  {
    driverType = driverTypes[driverTypeIndex];
    // create a device, device context and swap chain using the information in the scd struct
    hr = D3D11CreateDeviceAndSwapChain(
      NULL,
      driverType,
      NULL,
      createDeviceFlags,
      featureLevels,
      numFeatureLevels,
      D3D11_SDK_VERSION,
      &scd,
      &swapchain,
      &device,
      &featureLevel,
      &deviceContext);

    if (SUCCEEDED(hr))
    {
      break;
    }
  }

  if (FAILED(hr))
  {
    ErrorMessage("Failed to create device and swap chain!");
  }

  ////////////////////////
  // Render Target View //
  ////////////////////////

  ID3D11Texture2D * pBackBuffer;
  hr = swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
  if (FAILED(hr))
  {
    ErrorMessage("Cannot get the backbuffer");
  }

  hr = device->CreateRenderTargetView(pBackBuffer, NULL, &backbufferRTV);
  pBackBuffer->Release();
  if (FAILED(hr))
  {
    ErrorMessage("Cannot create the renderTargetView");
  }

  ///////////////////////////
  // Depth Stencil Texture //
  ///////////////////////////

  // Create depth stencil texture
  D3D11_TEXTURE2D_DESC descDepth;
  ZeroMemory( &descDepth, sizeof(descDepth) );
  descDepth.Width = width;
  descDepth.Height = height;
  descDepth.MipLevels = 1;
  descDepth.ArraySize = 1;
  descDepth.Format =  DXGI_FORMAT_R32_TYPELESS; // must be typeless to render
  // see: http://msdn.microsoft.com/en-us/library/windows/desktop/bb205074%28v=vs.85%29.aspx
  descDepth.SampleDesc.Count = 1;
  descDepth.SampleDesc.Quality = 0;
  descDepth.Usage = D3D11_USAGE_DEFAULT;
  descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D10_BIND_SHADER_RESOURCE;
  descDepth.CPUAccessFlags = 0;
  descDepth.MiscFlags = 0;
  hr = device->CreateTexture2D(&descDepth, NULL, &pDepthStencil);
  if (FAILED(hr))
  {
    ErrorMessage( "Failed to create depth stencil buffer!");
  }

  // Create the depth stencil view
  D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
  ZeroMemory( &descDSV, sizeof(descDSV) );
  descDSV.Format = DXGI_FORMAT_D32_FLOAT;//descDepth.Format;
  descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
  descDSV.Texture2D.MipSlice = 0;
  hr = this->device->CreateDepthStencilView(pDepthStencil, &descDSV, &pDepthStencilView);
  if(FAILED(hr))
  {
    ErrorMessage("Failed to create depth stencil view!");
  }

  //// I want to be able to render the depth buffer as a texture, so create a SRV
  //// for it.
  //// see: http://msdn.microsoft.com/en-us/library/windows/desktop/bb205074%28v=vs.85%29.aspx
  //D3D11_SHADER_RESOURCE_VIEW_DESC depthSRVdesc;
  //depthSRVdesc.Format = DXGI_FORMAT_R32_FLOAT;
  //depthSRVdesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
  //depthSRVdesc.Texture2D.MostDetailedMip = 0;
  //depthSRVdesc.Texture2D.MipLevels = 1;

  //hr = device->CreateShaderResourceView(pDepthStencil, &depthSRVdesc, &pDepthSRV);
  //if (FAILED(hr))
  //{
  //  ErrorMessage("Failed to create shaderResourceView for the depth buffer");
  //}

  //////////////
  // Viewport //
  //////////////

  // Set the viewport
  D3D11_VIEWPORT viewport;
  viewport.Width = (float)width;
  viewport.Height = (float)height;
  viewport.MinDepth = 0.0f;
  viewport.MaxDepth = 1.0f;
  viewport.TopLeftX = 0;
  viewport.TopLeftY = 0;

  deviceContext->RSSetViewports(1, &viewport);
}

void Direct3D::InitPipeline()         // loads and compiles our shaders from hlsl file(s)
{
  HRESULT hr;

  //load and compile the shaders
  ID3DBlob * VS; //vertex shader
  ID3DBlob * PS; //pixel shader
  ID3DBlob * ErrorMessages;
  hr = D3DX11CompileFromFile("Resources/Shaders/shaders.fx", 0, 0, "VShader", "vs_4_0", 0, 0, 0, &VS, &ErrorMessages, 0);
  std::cout << static_cast<char*>(ErrorMessages->GetBufferPointer());
  if (FAILED(hr))
  {
    //ErrorMessages is a buffer of data. So we cast it to a char* and cout it
    ErrorMessage(static_cast<char*>(ErrorMessages->GetBufferPointer()));
    ErrorMessages->Release();
  }

  hr = D3DX11CompileFromFile("Resources/Shaders/shaders.fx", 0, 0, "PShader", "ps_4_0", 0, 0, 0, &PS, &ErrorMessages, 0);
  if (FAILED(hr))
  {
    ErrorMessage(static_cast<char*>(ErrorMessages->GetBufferPointer()));
    ErrorMessages->Release();
  }

  //encapsulate the shaders into shader objects

  hr = (device)->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &pVertexShader);
  if (FAILED(hr))
  {
    ErrorMessage("Failed to create shader!");
  }

  hr = (device)->CreatePixelShader (PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &pPixelShader);
  if (FAILED(hr))
  {
    ErrorMessage("Failure to create shader!");
  }
  //
  //////DO THE SAME FOR A SECOND SHADER
  //ID3DBlob * PS2;
  //D3DX11CompileFromFile("shaders.fx", 0, 0, "PShader", "ps_4_0", 0, 0, 0, &PS2, 0, 0);
  //(device)->CreatePixelShader (PS2->GetBufferPointer(),
  //  PS2->GetBufferSize(), NULL, &(pPixelShader2));

  //set the current shader
  ppCurrentPixelShader = &pPixelShader;

  //create the input layout object
  unsigned int sizeofPosition = sizeof(D3DXVECTOR3);
  //unsigned int sizeofColor    = sizeof(D3DXCOLOR);
  unsigned int sizeofNormal   = sizeof(D3DXVECTOR3);
  unsigned int sizeofTex      = sizeof(D3DXVECTOR2);

  D3D11_INPUT_ELEMENT_DESC ied[] =
  {
    {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
      0,
      D3D11_INPUT_PER_VERTEX_DATA, 0},
 // {"COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,
 //   0 + sizeofPosition,
 //   D3D11_INPUT_PER_VERTEX_DATA, 0},
    {"NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
      0 + sizeofPosition,
      D3D11_INPUT_PER_VERTEX_DATA, 0},
    {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0,
      0 + sizeofPosition + sizeofNormal,
      D3D11_INPUT_PER_VERTEX_DATA, 0},
  };

  UINT numElements = ARRAYSIZE(ied);

  (device)->CreateInputLayout(ied, numElements, VS->GetBufferPointer(),
    VS->GetBufferSize(), &(pLayout));
  (deviceContext)->IASetInputLayout(pLayout);

  VS->Release();
  PS->Release();
  //PS2->Release();
  ErrorMessages->Release();
}

// Create the constant buffer
void Direct3D::InitGraphics()
{
  D3D11_BUFFER_DESC bufferDescription;
  ZeroMemory(&bufferDescription, sizeof(bufferDescription));
  bufferDescription.Usage = D3D11_USAGE_DEFAULT;
  bufferDescription.ByteWidth = sizeof(ConstantBuffer);
  bufferDescription.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
  bufferDescription.CPUAccessFlags = 0;

  D3D11_SUBRESOURCE_DATA initData;
  ConstantBuffer buffer;
  initData.pSysMem = &buffer;
  initData.SysMemPitch = 0;
  initData.SysMemSlicePitch = 0;

  HRESULT hr = device->CreateBuffer(&bufferDescription, &initData, &(pCBChangesEveryFrame));
  if (FAILED(hr))
  {
    ErrorMessage("Failed to create the constant buffer!");
  }
}

// this is the function that cleans up Direct3D and COM
void Direct3D::CleanD3D()
{
  swapchain->SetFullscreenState(FALSE, NULL);    // d3d cannot close while fullscreen

  // close and release all existing COM objects
  if (pLayout) pLayout->Release(); pLayout = 0;

  if(pVertexShader) pVertexShader->Release(); pVertexShader = 0;

  if(pPixelShader) pPixelShader->Release(); pPixelShader = 0;

  //if(pPixelShader2) pPixelShader2->Release(); pPixelShader2 = 0;

  if (swapchain) swapchain->Release(); swapchain = 0;

  if(backbufferRTV) backbufferRTV->Release(); backbufferRTV = 0;

  if(device) device->Release(); device = 0;

  if(deviceContext) deviceContext->Release(); deviceContext = 0;

  if(pDepthStencilView) pDepthStencilView->Release(); pDepthStencilView = 0;

  if(pDepthStencil) pDepthStencil->Release(); pDepthStencil = 0;
}

void Direct3D::Push(D3DXMATRIX matrix)
{
  matrixStack.push(matrix);
}

void Direct3D::Pop()
{
  matrixStack.pop();
}

D3DXMATRIX Direct3D::Top()
{
  return matrixStack.top();
}

unsigned int Direct3D::GetMatrixStackSize()
{
  return matrixStack.size();
}

ID3D11Buffer * Direct3D::LoadVertices( std::string name, VERTEX verticies [], UINT sizeOfVerticies )
{
  //Create a vertex buffer and store it in our map
  this->verticies[name] = NULL;//this, verticies);

  ID3D11Buffer * pVertexBuffer;

  // create the vertex buffer
  D3D11_BUFFER_DESC bufferDescription;
  ZeroMemory(&bufferDescription, sizeof(bufferDescription));

  bufferDescription.Usage = D3D11_USAGE_DEFAULT;
  bufferDescription.ByteWidth = sizeOfVerticies;

  bufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  bufferDescription.CPUAccessFlags = 0;

  // Fill in the subresource data.
  D3D11_SUBRESOURCE_DATA InitData;
  ZeroMemory( &InitData, sizeof(InitData) );
  InitData.pSysMem = verticies;

  // create the buffer
  (this->device)->CreateBuffer(&bufferDescription,
    &InitData,
    &pVertexBuffer);

  this->verticies[name] = pVertexBuffer;

  return pVertexBuffer;
}

ID3D11Buffer * Direct3D::GetVertices(std::string name)
{
  return verticies[name];//.GetpVertexBuffer();
}

IndexBuffer * Direct3D::LoadIndicies(std::string name, UINT16 indicies [], UINT sizeofIndicies)
{
  //Create a vertex buffer and store it in our map
  this->indicies[name] = NULL;//this, verticies);

  ID3D11Buffer * pIndexBuffer;

  // create the index buffer
  D3D11_BUFFER_DESC bufferDescription;
  ZeroMemory(&bufferDescription, sizeof(bufferDescription));
  bufferDescription.Usage = D3D11_USAGE_DEFAULT;
  bufferDescription.ByteWidth = sizeofIndicies;
  bufferDescription.BindFlags = D3D11_BIND_INDEX_BUFFER;
  bufferDescription.CPUAccessFlags = 0;

  D3D11_SUBRESOURCE_DATA InitData;
  InitData.pSysMem = indicies;
  (device)->CreateBuffer(&bufferDescription, &InitData, &(pIndexBuffer));

  unsigned indexCount = sizeofIndicies / sizeof(indicies[0]);

  IndexBuffer * indexBuffer = new IndexBuffer;
  indexBuffer->pIndexBuffer = pIndexBuffer;
  indexBuffer->indexCount = indexCount;

  this->indicies[name] = indexBuffer;

  return indexBuffer;
}

IndexBuffer * Direct3D::GetIndicies(std::string name)
{
  return indicies[name];
}

//
//VertexBuffer::VertexBuffer() : pVertexBuffer(NULL)
//{
//  // I... guess I need this?
//}
//
//void VertexBuffer::operator=(VertexBuffer & rhs)
//{
//  this->pVertexBuffer = rhs.pVertexBuffer;
//  rhs.pVertexBuffer = NULL;
//}
//
//VertexBuffer::VertexBuffer(Direct3D * direct3d, VERTEX vertices [])
//{
  //// create the vertex buffer
  //D3D11_BUFFER_DESC bufferDescription;
  //ZeroMemory(&bufferDescription, sizeof(bufferDescription));

  //bufferDescription.Usage = D3D11_USAGE_DEFAULT;
  //bufferDescription.ByteWidth = sizeof(vertices);
  //bufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
  //bufferDescription.CPUAccessFlags = 0;

  //// Fill in the subresource data.
  //D3D11_SUBRESOURCE_DATA InitData;
  //ZeroMemory( &InitData, sizeof(InitData) );
  //InitData.pSysMem = vertices;

  //// create the buffer
  //(direct3d->device)->CreateBuffer(&bufferDescription, &InitData, &(pVertexBuffer));
//}
//
//ID3D11Buffer * VertexBuffer::GetpVertexBuffer()
//{
//  return pVertexBuffer;
//}
//
//VertexBuffer::~VertexBuffer()
//{
//  if (pVertexBuffer)
//  {
//    pVertexBuffer->Release();
//  }
//}

//
//void Direct3D::CalculateFrameRate()
//{
//  // Code computes the average frames per second, and also the
//  // average time it takes to render one frame.
//
//  frameCnt++;
//
//  // Compute averages over one second period.
//  if( (mTimer.TotalTime() - timeElapsed) >= 1.0f )
//  {
//    float fps = (float)frameCnt; // fps = frameCnt / 1
//    float mspf = 1000.0f / fps;
//
//    std::wostringstream outs;
//    outs.precision(6);
//    outs << mMainWndCaption << L"    "
//      << L"FPS: " << fps << L"    "
//      << L"Frame Time: " << mspf << L" (ms)";
//    SetWindowText(mhMainWnd, outs.str().c_str());
//
//    // Reset for next average.
//    frameCnt = 0;
//    timeElapsed += 1.0f;
//  }
//}

HRESULT Direct3D::CreateRasterizerStates()
{
  HRESULT hr = S_OK;
  D3D11_RASTERIZER_DESC solidRDesc;     // solid     rasterizer description
  D3D11_RASTERIZER_DESC wireframeRDesc; // wireframe rasterizer description

  solidRDesc.FillMode              = D3D11_FILL_SOLID;
  solidRDesc.CullMode              = D3D11_CULL_BACK;
  solidRDesc.FrontCounterClockwise = false;
  solidRDesc.DepthBias             = 0;
  solidRDesc.DepthBiasClamp        = 0.0f;
  solidRDesc.SlopeScaledDepthBias  = 0.0f;
  solidRDesc.DepthClipEnable       = true;
  solidRDesc.ScissorEnable         = false;
  solidRDesc.MultisampleEnable     = false;
  solidRDesc.AntialiasedLineEnable = false;

  wireframeRDesc = solidRDesc; // copy values over
  wireframeRDesc.FillMode = D3D11_FILL_WIREFRAME; //but change the fill mode

  hr = device->CreateRasterizerState(&solidRDesc, &pSolidRS);
  if( FAILED(hr) )
  {
    ErrorMessage("Failed to create a rasterizer state!");
  }

  hr = device->CreateRasterizerState(&wireframeRDesc, &pWireframeRS);
  if( FAILED(hr) )
  {
    ErrorMessage("Failed to create a rasterizer state!");
  }

  return hr;
}

void Direct3D::DrawSolid()
{
  deviceContext->RSSetState(pSolidRS);
}

void Direct3D::DrawWireframe()
{
  deviceContext->RSSetState(pWireframeRS);
}

Mesh * Direct3D::LoadMesh(std::string meshname, ID3D11Buffer * pVertexBuffer, IndexBuffer * pIndexBuffer)
{
  //Create a mesh to store in our map
  this->meshes[meshname] = NULL;

  Mesh * pMesh = new Mesh;

  pMesh->pIndexBuffer = pIndexBuffer;
  pMesh->pVertexBuffer = pVertexBuffer;
  pMesh->pSamplerLinear = NULL; //TODO: <--
  pMesh->ptextureSRV = NULL;    //TODO: <--

  this->meshes[meshname] = pMesh;

  return pMesh;
}

Mesh * Direct3D::LoadMesh(std::string meshName, /*const */MeshData & meshData)
{
  ID3D11Buffer * vBuffer = LoadVertices(meshName, &(meshData.verticies[0]), sizeof(VERTEX) * meshData.verticies.size());
  IndexBuffer * iBuffer = LoadIndicies(meshName, &(meshData.indicies[0]), sizeof(UINT16) * meshData.indicies.size());
  return LoadMesh(meshName, vBuffer, iBuffer);
}

Mesh * Direct3D::LoadMesh(std::string meshName, std::string objFilepath)
{
  std::cout << "Loading mesh: " << objFilepath << "... ";
  ObjInfo * objInfo = ObjLoader::LoadObjIntoArray(objFilepath);

  //ID3D11Buffer * pVertexBuffer = LoadVertices(meshName, objInfo->vertexArray, objInfo->sizeofVertexArray);
  //IndexBuffer * pIndexBuffer = LoadIndicies(meshName, objInfo->indexArray,  objInfo->sizeofIndexArray);

  ID3D11Buffer * pVertexBuffer = LoadVertices(meshName, &objInfo->meshData.verticies[0], sizeof(VERTEX) * objInfo->meshData.verticies.size());
  IndexBuffer * pIndexBuffer   = LoadIndicies(meshName, &objInfo->meshData.indicies[0],  sizeof(UINT16) * objInfo->meshData.indicies.size());

  delete objInfo;

  Mesh * pMesh = LoadMesh(meshName, pVertexBuffer, pIndexBuffer);

  std::cout << "done!" << std::endl;
  return pMesh;
}

Mesh * Direct3D::GetMesh(std::string meshName)
{
  Mesh * pMesh = meshes[meshName];
  return pMesh;
}

#include <iostream>

#include "graphics.h"
#include "ErrorMessage.h"

//temp:
#include "PartyLight.h"
//also temp:
#include "PB_input.h"

Graphics::Graphics(unsigned int screenWidth, unsigned int screenHeight, HWND hWnd) :
  screenWidth(screenWidth),
  screenHeight(screenHeight),
  direct3d(hWnd)
{
}

void Graphics::Draw(RenderGroup & root, Camera & camera)
{
  // clear the back buffer
  D3DXCOLOR clearColorBlue(0.0f, 0.125f, 0.3f, 1.0f); // Deep blue

  ////////////////////////////////////////////////////
  // DRAW TO THE NORMALMAP, DIFFUSE, DEPTH TEXTURES //
  ////////////////////////////////////////////////////

  direct3d.deviceContext->OMSetBlendState(direct3d.pBlendStateDefault, NULL, 1);

  if (true)
  {
    //std::cout << "D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT: " << D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT << std::endl; //(it's 8)
    const int size = 3;
    ID3D11RenderTargetView  * RTVArray  [size];//= new ID3D11RenderTargetView *[size];
    int currentRTV = 0;
    RTVArray[currentRTV++] = direct3d.pSceneNormalMap->pRenderTargetView;
    RTVArray[currentRTV++] = direct3d.pSceneDiffuse->pRenderTargetView;
    RTVArray[currentRTV++] = direct3d.pSceneViewspaceDepth->pRenderTargetView;

    direct3d.deviceContext->OMSetRenderTargets(size, RTVArray, direct3d.pDepthStencilView);

    for (int i = 0; i < size; ++i)
    {
      direct3d.deviceContext->ClearRenderTargetView(RTVArray[i], clearColorBlue);
    }

    direct3d.deviceContext->ClearDepthStencilView(direct3d.pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0 );

    //set our shaders to be the active shaders
    direct3d.deviceContext->VSSetShader(direct3d.pVertexShader, 0, 0);
    direct3d.deviceContext->PSSetShader(direct3d.pPixelShader, 0, 0);

    // For the cube/teapot texture
    direct3d.deviceContext->PSSetShaderResources(0,1,&direct3d.ptextureSRV);
    direct3d.deviceContext->PSSetSamplers(0,1,&direct3d.pSamplerLinear);
  }

  // The matrix stack is initially just an identity matrix so that when we add
  // things to the stack they just multiply with top()
  D3DXMATRIX identity;
  D3DXMatrixIdentity(&identity);
  direct3d.Push(identity);

  // Separate the camera matricies into the renderer
  direct3d.viewMatrix = camera.GetViewMatrix();
  direct3d.projMatrix = camera.GetProjectionMatrix();

  ///////////////////////
  // Traverse the tree //
  ///////////////////////

  root.Visit(direct3d);

  // Pop the identity matrix.
  // Note: We are pushing/popping the identity matrix once every draw.
  // Instead, we could add it and pop it in the ctor/dtor, but that's slightly
  // more confusing than what we're doing now, so we won't.
  direct3d.Pop();

  ////////////////////////////////////
  // DRAW the DIFFUSE TO THE SCREEN //
  ////////////////////////////////////
  if (!keyIsDown(KEY_N))
  {
    direct3d.deviceContext->OMSetRenderTargets(1, &direct3d.backbufferRTV, NULL);

    direct3d.deviceContext->ClearRenderTargetView(direct3d.backbufferRTV, clearColorBlue);

    //set our shaders to be the active shaders
    direct3d.pFullscreenTextureShader->SetCurrentShader(direct3d.deviceContext);

    // Set scene texture as a shader resource
    direct3d.deviceContext->PSSetShaderResources(0, 1, &(direct3d.pSceneDiffuse->pShaderResourceView));
    direct3d.deviceContext->PSSetSamplers(0,1,&direct3d.pSamplerLinear);

    std::string fullscreenQuadString("fullscreenQuad");
    Mesh * fullscreenQuadMesh = direct3d.GetMesh(fullscreenQuadString);
    UINT stride = sizeof(VERTEX);
    UINT offset = 0;

    direct3d.deviceContext->IASetVertexBuffers(0, 1, &(fullscreenQuadMesh->pVertexBuffer),&stride, &offset );
    direct3d.deviceContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    direct3d.deviceContext->IASetIndexBuffer(fullscreenQuadMesh->pIndexBuffer->pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

    UINT indexcount = fullscreenQuadMesh->pIndexBuffer->indexCount;
    direct3d.deviceContext->DrawIndexed(indexcount, 0, 0);
  }

  ///////////////////////////////////////
  // 1. DRAW THE NORMALS TO THE SCREEN //
  ///////////////////////////////////////
  if (keyIsDown(KEY_N))
  {
    direct3d.deviceContext->OMSetRenderTargets(1, &direct3d.backbufferRTV, NULL);

    direct3d.deviceContext->ClearRenderTargetView(direct3d.backbufferRTV, clearColorBlue);

    //set our shaders to be the active shaders
    direct3d.pFullscreenTextureShader->SetCurrentShader(direct3d.deviceContext);

    // Set scene texture as a shader resource
    direct3d.deviceContext->PSSetShaderResources(0, 1, &(direct3d.pSceneNormalMap->pShaderResourceView));
    direct3d.deviceContext->PSSetSamplers(0,1,&direct3d.pSamplerLinear);

    std::string fullscreenQuadString("fullscreenQuad");
    Mesh * fullscreenQuadMesh = direct3d.GetMesh(fullscreenQuadString);
    UINT stride = sizeof(VERTEX);
    UINT offset = 0;

    direct3d.deviceContext->IASetVertexBuffers(0, 1, &(fullscreenQuadMesh->pVertexBuffer),&stride, &offset );
    direct3d.deviceContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    direct3d.deviceContext->IASetIndexBuffer(fullscreenQuadMesh->pIndexBuffer->pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

    UINT indexcount = fullscreenQuadMesh->pIndexBuffer->indexCount;
    direct3d.deviceContext->DrawIndexed(indexcount, 0, 0);
  }

  /////////////////////////////////////////
  // DRAW THE DEPTH BUFFER TO THE SCREEN // (it's in viewspace)
  /////////////////////////////////////////
  if (keyIsDown(KEY_M))
  {
    // Bind the depth buffer to the device
    direct3d.deviceContext->OMSetRenderTargets(1, &direct3d.backbufferRTV, NULL);

    direct3d.deviceContext->ClearRenderTargetView(direct3d.backbufferRTV, D3DXCOLOR(1,1,1,1));

    //set our shaders to be the active shaders
    direct3d.pFullscreenTextureShader->SetCurrentShader(direct3d.deviceContext);

    // Set scene texture as a shader resource
    direct3d.deviceContext->PSSetShaderResources(0, 1, &(direct3d.pSceneViewspaceDepth->pShaderResourceView));
    direct3d.deviceContext->PSSetSamplers(0,1,&direct3d.pSamplerLinear);

    std::string fullscreenQuadString("fullscreenQuad");
    Mesh * fullscreenQuadMesh = direct3d.GetMesh(fullscreenQuadString);
    UINT stride = sizeof(VERTEX);
    UINT offset = 0;

    direct3d.deviceContext->IASetVertexBuffers(0, 1, &(fullscreenQuadMesh->pVertexBuffer),&stride, &offset );
    direct3d.deviceContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    direct3d.deviceContext->IASetIndexBuffer(fullscreenQuadMesh->pIndexBuffer->pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

    UINT indexcount = fullscreenQuadMesh->pIndexBuffer->indexCount;
    direct3d.deviceContext->DrawIndexed(indexcount, 0, 0);
  }

  //////////////////////
  // Deferred Shading //
  //////////////////////
  

  //temp (keep 0 worldspacePointLights)
  int numPointLights = direct3d.worldspacePointLights.size();
  while(numPointLights-- > 0);
  {
    direct3d.worldspacePointLights.pop();
  }


  if (false)
  {
    direct3d.deviceContext->OMSetBlendState(direct3d.pBlendStateDefault, NULL, 1);
    direct3d.deviceContext->OMSetRenderTargets(1, &direct3d.backbufferRTV, NULL);
    direct3d.deviceContext->ClearRenderTargetView(direct3d.backbufferRTV,clearColorBlue);
    //direct3d.pDeferredShader->SetCurrentShader(direct3d.deviceContext); //TODO: MAKE THIS

    // Set the 3 texture resources
    const int size = 3;
    ID3D11ShaderResourceView * SRVArray [size];
    int currentSRV = 0;
    SRVArray[currentSRV++] = direct3d.pSceneDiffuse->pShaderResourceView;
    SRVArray[currentSRV++] = direct3d.pSceneNormalMap->pShaderResourceView;
    SRVArray[currentSRV++] = direct3d.pSceneViewspaceDepth->pShaderResourceView;
    direct3d.deviceContext->PSSetShaderResources(0, size, SRVArray);

    // during the visitor traversal of the scene graph,
    // when it visited a LIGHTNODE,
    // the LIGHTNODE added its data and its worldspace position to
    // a list of lights in the renderer's light manager
    // Now, all we have to do is:
    //    Draw every light as a model (deferred shading!)

    int numPointLights = direct3d.worldspacePointLights.size();
    while(numPointLights > 0);
    {
      // Get the light, pop it off the stack
      PointLight::WorldspacePointLight worldspacePointLight = direct3d.worldspacePointLights.top();
      numPointLights--;
      direct3d.worldspacePointLights.pop();

      std::string sphereMeshString("Sphere mesh string");
      Mesh * sphereMesh = direct3d.GetMesh(sphereMeshString);
      UINT stride = sizeof(VERTEX);
      UINT offset = 0;

      direct3d.deviceContext->IASetVertexBuffers(0, 1, &(sphereMesh->pVertexBuffer),&stride, &offset );
      direct3d.deviceContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
      direct3d.deviceContext->IASetIndexBuffer(sphereMesh->pIndexBuffer->pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

      UINT indexcount = sphereMesh->pIndexBuffer->indexCount;

      // constant buffer
      ConstantBuffer cb;

      cb.mWorld = worldspacePointLight.lightWorldMatrix;
      cb.mView = direct3d.viewMatrix;
      cb.mProjection = direct3d.projMatrix;

      //compute invtransworld for transforming normals
      float det = D3DXMatrixDeterminant(&cb.mWorld);
      D3DXMatrixInverse(&cb.mInvTransWorld, &det, &cb.mWorld);
      D3DXMatrixTranspose(&cb.mInvTransWorld, &cb.mInvTransWorld);

      cb.lightDirection = D3DXVECTOR4(0.0f, -0.25f, 1.0f, 1.0f);

      direct3d.deviceContext->UpdateSubresource(direct3d.pCBChangesEveryFrame, 0, NULL, &cb, 0, 0);

      //select the constantbuffer
      direct3d.deviceContext->VSSetConstantBuffers(0,  1, &(direct3d.pCBChangesEveryFrame));
      direct3d.deviceContext->PSSetConstantBuffers(0,  1, &(direct3d.pCBChangesEveryFrame));



      direct3d.deviceContext->DrawIndexed(indexcount, 0, 0);
    }
  }
  
  /////////////
  // </Temp> //
  /////////////

  // switch the back buffer and the front buffer
  //direct3d.swapchain->Present(0, 0);

  //the renderer size should be 0.
  if (direct3d.GetMatrixStackSize() != 0)
  {
    ErrorMessage("The renderer stack is not empty!");
  }
}
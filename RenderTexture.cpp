#include "RenderTexture.h"
#include "ErrorMessage.h"
#include <d3dx11tex.h>
RenderTexture::RenderTexture():
pRenderTargetTexture(0),
  pRenderTargetView(0),
  pShaderResourceView(0)
{
}

void RenderTexture::CreateTexture(ID3D11Device * device, DXGI_FORMAT format, int textureWidth, int textureHeight)
{
  HRESULT hr;

  ////////////////////////
  // Create the texture //
  ////////////////////////
  D3D11_TEXTURE2D_DESC textureDesc;
  textureDesc.Width = textureWidth;
  textureDesc.Height = textureHeight;
  textureDesc.MipLevels = 1;
  textureDesc.ArraySize = 1;
  textureDesc.Format = format;
  textureDesc.SampleDesc.Count = 1;
  textureDesc.SampleDesc.Quality = 0;
  textureDesc.Usage = D3D11_USAGE_DEFAULT; // <-- not sure what default is
  textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
  textureDesc.CPUAccessFlags = 0;
  textureDesc.MiscFlags = 0;
  hr = device->CreateTexture2D( &textureDesc, NULL, &pRenderTargetTexture );
  if (FAILED(hr))
  {
    ErrorMessage("Failed to create texture2d");
  }
}
void RenderTexture::CreateTextureFromFile(ID3D11Device * device, std::string & filename, DXGI_FORMAT format)
{
  HRESULT hr;

  D3DX11_IMAGE_LOAD_INFO loadInfo;
  loadInfo.Width          = D3DX11_DEFAULT;
  loadInfo.Height         = D3DX11_DEFAULT;
  loadInfo.Depth          = D3DX11_DEFAULT;
  loadInfo.FirstMipLevel  = D3DX11_DEFAULT;
  loadInfo.MipFilter      = D3DX11_DEFAULT;
  loadInfo.Usage          = D3D11_USAGE_DEFAULT;
  loadInfo.BindFlags      = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
  loadInfo.CpuAccessFlags = 0;
  loadInfo.MiscFlags      = D3DX11_DEFAULT;
  loadInfo.Format         = format;
  loadInfo.Filter         = D3DX11_DEFAULT;
  loadInfo.MipFilter      = D3DX11_DEFAULT;
  loadInfo.pSrcInfo       = NULL;

  //ID3D11Texture2D * renderTargetTexture = pRenderTargetTexture;
  //ID3D11Resource * resource = renderTargetTexture;
  //                 //resource = pRenderTargetTexture;
  //ID3D11Resource * resource;
  //D3DX11CreateTextureFromFile(device, filename.c_str(), &loadInfo, NULL, &resource, &hr);
  //
  ////D3DX11CreateTextureFromFile(device, filename.c_str(), &loadInfo, NULL, &static_cast<ID3D11Resource*>(pRenderTargetTexture), &hr);
  //
  //ID3D11Texture2D *pTex2D_tmp = NULL;
  //D3D11_TEXTURE2D_DESC texdesc = {0};
  //pRenderTargetTexture->QueryInterface( __uuidof(ID3D11Texture2D), (VOID**)&pTex2D_tmp );
  //pTex2D_tmp->GetDesc( &texdesc );
  //donne(pTex2D_tmp);

  D3DX11CreateTextureFromFile(device, filename.c_str(), &loadInfo, NULL, ( ID3D11Resource** )&pRenderTargetTexture, &hr);

  if (FAILED(hr))
  {
    ErrorMessage("Failed to create texture from file!");
  }
}

void RenderTexture::CreateRenderTargetView(ID3D11Device * device, DXGI_FORMAT format)
{
  HRESULT hr;

  /////////////////////////////////
  // Create the RenderTargetView //
  /////////////////////////////////
  D3D11_RENDER_TARGET_VIEW_DESC renderTarvetViewDesc;
  renderTarvetViewDesc.Format = format;
  renderTarvetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
  renderTarvetViewDesc.Texture2D.MipSlice = 0;

  hr = device->CreateRenderTargetView(pRenderTargetTexture, &renderTarvetViewDesc, &pRenderTargetView);
  if (FAILED(hr))
  {
    ErrorMessage("Failed to create renderTargetView");
  }
}
void RenderTexture::CreateShaderResourceView(ID3D11Device * device, DXGI_FORMAT format)
{
  HRESULT hr;

  ///////////////////////////////////
  // Create the ShaderResourceView //
  ///////////////////////////////////
  D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
  shaderResourceViewDesc.Format = format;
  shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
  shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
  shaderResourceViewDesc.Texture2D.MipLevels = 1;

  hr = device->CreateShaderResourceView(pRenderTargetTexture, &shaderResourceViewDesc, &pShaderResourceView);
  if (FAILED(hr))
  {
    ErrorMessage("Failed to create shaderResourceView");
  }
}

void RenderTexture::Initialize(ID3D11Device * device, DXGI_FORMAT format, int textureWidth, int textureHeight)
{
  CreateTexture(device, format, textureWidth, textureHeight);
  CreateRenderTargetView(device, format);
  CreateShaderResourceView(device, format);
}
void RenderTexture::InitializeFromFile(ID3D11Device * device, std::string & filename, DXGI_FORMAT format)
{
  CreateTextureFromFile(device, filename, format);
  CreateRenderTargetView(device, format);
  CreateShaderResourceView(device, format);
}

RenderTexture::~RenderTexture()
{
  if (pShaderResourceView)
  {
    pShaderResourceView->Release(); pShaderResourceView = NULL;
  }

  if (pRenderTargetView)
  {
    pRenderTargetView->Release(); pRenderTargetView = NULL;
  }

  if (pRenderTargetTexture)
  {
    pRenderTargetTexture->Release(); pRenderTargetTexture = NULL;
  }
}
#pragma once
#include <d3d11.h>
#include <string>

class RenderTexture
{
public:
  RenderTexture();
  ~RenderTexture();
  void Initialize(ID3D11Device * device, DXGI_FORMAT format, int textureWidth, int textureHeight);
  void InitializeFromFile(ID3D11Device * device, std::string & filename, DXGI_FORMAT format);
  ID3D11Texture2D * pRenderTargetTexture;
  ID3D11ShaderResourceView * pShaderResourceView;
  ID3D11RenderTargetView * pRenderTargetView;

private:
  void CreateTexture(ID3D11Device * device, DXGI_FORMAT format, int textureWidth, int textureHeight);
  void CreateTextureFromFile(ID3D11Device * device, std::string & filename, DXGI_FORMAT format);
  void CreateRenderTargetView(ID3D11Device * device, DXGI_FORMAT format);
  void CreateShaderResourceView(ID3D11Device * device, DXGI_FORMAT format);
};
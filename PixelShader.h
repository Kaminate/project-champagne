#pragma once
#include <d3d11.h>
#include <string>

class PixelShader
{
public:
  PixelShader();
  ~PixelShader();
  HRESULT Load(ID3D11Device * device, std::string filepath);
  void SetActivePixelShader(ID3D11DeviceContext * deviceContext); //Sets this shader to be the active pixel shader

private:
  ID3D11PixelShader * pPixelShader;
};
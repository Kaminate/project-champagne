#pragma once
#include <d3d11.h>
#include <string>

class VertexShader
{
public:
  VertexShader();
  ~VertexShader();
  HRESULT Load(ID3D11Device * device, std::string filepath);
  void SetActiveVertexShader(ID3D11DeviceContext * deviceContext); //Sets this shader to be the active pixel shader

private:
  ID3D11VertexShader * pVertexShader;
};
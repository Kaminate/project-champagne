#pragma once
#include <d3d11.h>
#include <string>

#include "PixelShader.h"
#include "VertexShader.h"

class Shader
{
public:

  // struct ShaderConstantBuffer
  // {
  //    matrix World;
  //    matrix View;
  //    matrix Proj;
  //    etc
  // }

  Shader(std::string filepathVS, std::string filepathPS);

  HRESULT Initialize(ID3D11Device * device);
  void SetCurrentShader(ID3D11DeviceContext * deviceContext);
  
private:
  PixelShader pixelShader;
  VertexShader vertexShader;

  const std::string filepathVS;
  const std::string filepathPS;
};
#include "Shader.h"

#include "ErrorMessage.h"

Shader::Shader(std::string filepathVS, std::string filepathPS):
  pixelShader(),
  vertexShader(),
  filepathPS(filepathPS),
  filepathVS(filepathVS)
{

}

HRESULT Shader::Initialize(ID3D11Device * device)
{
  HRESULT hr;
  hr = vertexShader.Load(device, filepathVS);
  if (FAILED(hr))
  {
    ErrorMessage("Failed to load a vertex shader");
  }

  hr = pixelShader.Load(device, filepathPS);
  if (FAILED(hr))
  {
    ErrorMessage("Failed to load a pixel shader");
  }

  return hr;
}

void Shader::SetCurrentShader(ID3D11DeviceContext * deviceContext)
{
  vertexShader.SetActiveVertexShader(deviceContext);
  pixelShader.SetActivePixelShader(deviceContext);
}

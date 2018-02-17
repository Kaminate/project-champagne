#include "VertexShader.h"
#include "ErrorMessage.h"
#include <d3dx11async.h>

VertexShader::VertexShader():
pVertexShader(NULL)
{
}

VertexShader::~VertexShader()
{
  if (pVertexShader)
  {
    pVertexShader->Release();
    pVertexShader = NULL;
  }
}

HRESULT VertexShader::Load(ID3D11Device * device, std::string filepath)
{
  HRESULT hr;
  ID3DBlob * VS;
  ID3DBlob * ErrorMessages;

  //compile the shader
  hr = D3DX11CompileFromFile(filepath.c_str(), 0, 0, "VShader", "vs_4_0", 0, 0, 0, &VS, &ErrorMessages, 0);
  if (FAILED(hr))
  {
    //ErrorMessages is a buffer of data. So we cast it to a char* and cout it
    ErrorMessage(static_cast<char*>(ErrorMessages->GetBufferPointer()));
    ErrorMessages->Release();
  }

  //encapsulate the shaders into shader objects
  hr = device->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &pVertexShader);
  if (FAILED(hr))
  {
    ErrorMessage("Failed to create pixel shader!");
  }

  return hr;
}

void VertexShader::SetActiveVertexShader(ID3D11DeviceContext * deviceContext)
{
  deviceContext->VSSetShader(pVertexShader, 0, 0);
}
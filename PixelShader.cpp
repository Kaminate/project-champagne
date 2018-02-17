#include "PixelShader.h"
#include "ErrorMessage.h"
#include <d3dx11async.h>

PixelShader::PixelShader():
  pPixelShader(NULL)
{
}

PixelShader::~PixelShader()
{
  if (pPixelShader)
  {
    pPixelShader->Release();
    pPixelShader = NULL;
  }
}

HRESULT PixelShader::Load(ID3D11Device * device, std::string filepath)
{
  HRESULT hr;
  ID3DBlob * PS;
  ID3DBlob * ErrorMessages;

  //compile the shader
  hr = D3DX11CompileFromFile(filepath.c_str(), 0, 0, "PShader", "ps_4_0", 0, 0, 0, &PS, &ErrorMessages, 0);
  if (FAILED(hr))
  {
    //ErrorMessages is a buffer of data. So we cast it to a char* and cout it
    ErrorMessage(static_cast<char*>(ErrorMessages->GetBufferPointer()));
    ErrorMessages->Release();
  }

  //encapsulate the shaders into shader objects
  hr = device->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &pPixelShader);
  if (FAILED(hr))
  {
    ErrorMessage("Failed to create pixel shader!");
  }

  return hr;
}

void PixelShader::SetActivePixelShader(ID3D11DeviceContext * deviceContext)
{
  deviceContext->PSSetShader(pPixelShader, 0, 0);
}
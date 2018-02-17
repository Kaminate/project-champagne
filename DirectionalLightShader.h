#pragma once

#include "Shader.h"
#include <d3dx10math.h>

class DirectionalLightShader : public Shader
{
public:
  struct DirectionalLightConstantBuffer
  {
    D3DXMATRIX lightWorldMatrix;
    D3DXMATRIX view;
    D3DXMATRIX projection;

    D3DXCOLOR ambient;
    D3DXCOLOR diffuse;
    D3DXCOLOR specular;

    D3DXVECTOR4 direction; // showld it be worldspace or viewspace
  };

  DirectionalLightShader();

private:
};


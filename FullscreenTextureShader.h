#pragma once
#include <d3d11.h>
#include <string>

#include "PixelShader.h"
#include "VertexShader.h"
#include "Shader.h"

// To use this shader, 
// 1. Set scene texture as a shader resource
// direct3d.deviceContext->PSSetShaderResources(0, 1, &(direct3d.pTextureToRender->pShaderResourceView));
// 2. pass in a fullscreen quad as the mesh with verticies [-1, 1]

class FullscreenTextureShader : public Shader
{
public:
  FullscreenTextureShader();
  
private:
};
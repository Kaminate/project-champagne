#pragma once

#include "IndexBuffer.h"
#include <d3d11.h>

class Mesh
{
public:
  ID3D11Buffer * pVertexBuffer;
  IndexBuffer * pIndexBuffer;
  ID3D11ShaderResourceView * ptextureSRV; //TODO: <--
  ID3D11SamplerState * pSamplerLinear ;   //TODO: <--
private:
};

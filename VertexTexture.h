#pragma once
#include <d3dx10math.h>
#include <iostream>
#include "Cout_for_DirectX.h"

class VertexTexture
  {
  public:
    VertexTexture();
    VertexTexture(float u, float v);

    D3DXVECTOR2 uv;

    friend std::ostream& operator<<(std::ostream& os, const VertexTexture & VertexTexture);

  private:
  };

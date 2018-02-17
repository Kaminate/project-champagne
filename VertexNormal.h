#pragma once
#include <d3dx10math.h>
#include <iostream>
#include "Cout_for_DirectX.h"

class VertexNormal
{
public:
  VertexNormal();
  VertexNormal(float x, float y, float z);

  D3DXVECTOR3 normal;

  friend std::ostream& operator<<(std::ostream& os, const VertexNormal & vertexNormal);

private:
};

#pragma once
#include <d3dx10math.h>
#include <iostream>
#include "Cout_for_DirectX.h"

class VertexPosition
{
public:
  VertexPosition();
  VertexPosition(float x, float y, float z);

  D3DXVECTOR3 position;

  friend std::ostream& operator<<(std::ostream& os, const VertexPosition& vertexPosition);

private:
};

#include "GeometryGenerator.h"

void GeometryGenerator::CreateTetrahedron(MeshData & meshData)
{
  meshData.verticies.resize(12);
  meshData.indicies.resize(12);

  // http://en.wikipedia.org/wiki/Tetrahedron
  const float oneOverSqrt2 = 1.0f / sqrtf(2.0f);

  D3DXVECTOR3 verticies[4];
  verticies[0] = D3DXVECTOR3( 1, 0, -oneOverSqrt2);
  verticies[1] = D3DXVECTOR3(-1, 0, -oneOverSqrt2);
  verticies[2] = D3DXVECTOR3( 0, 1,  oneOverSqrt2);
  verticies[3] = D3DXVECTOR3( 0,-1,  oneOverSqrt2);

  for (int i = 0; i < 4; ++i)
  {
    for (int j = i + 1; j < 4; ++j)
    {
      for (int k = j + 1; k < 4; ++k)
      {
        std::cout << "Pass one ";
        std::cout << "(" << i << ", " << j << ", " << k << ")";
        std::cout << std::endl;
      }
    }
  }

  std::cout << "this function is incomplete";
}
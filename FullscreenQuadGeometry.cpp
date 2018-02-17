#include "GeometryGenerator.h"

void GeometryGenerator::CreateFullscreenQuad(MeshData & meshData)
{
  // verticies
  //
  //         ^ y [-1, 1]
  //         |
  //  0______|______1
  //  | \    |      |
  //  |   \  |      |
  //  |     \|______|___\ x [-1, 1]
  //  |       \     |   /
  //  |         \   |
  //  |___________\_|
  //  2             3
  const UINT rowCount = 2;
  const UINT columnCount = 2;
  const UINT vertexCount = 4;
  meshData.verticies.resize(vertexCount);

  /*
  meshData.verticies[0].position = D3DXVECTOR3(-1, 1, 0);
  meshData.verticies[0].tex = D3DXVECTOR2(0,0);

  meshData.verticies[1].position = D3DXVECTOR3(1, 1, 0);
  meshData.verticies[1].tex = D3DXVECTOR2(1,0);

  meshData.verticies[2].position = D3DXVECTOR3(-1, -1, 0);
  meshData.verticies[2].tex = D3DXVECTOR2(0,1);

  meshData.verticies[3].position = D3DXVECTOR3(1, -1, 0);
  meshData.verticies[3].tex = D3DXVECTOR2(1,1);
  */

  //for each row
  for (UINT i = 0; i < rowCount; ++i)
  {
    //for each column in each row
    for (UINT j = 0; j < columnCount; ++j)
    {
      VERTEX & currentVertex = meshData.verticies[i*columnCount + j];
      currentVertex.normal = D3DXVECTOR3(0.0f, 0.0f, -1.0f); // I guess?...
      if (j == 0) currentVertex.position.x = -1.0f;
      else        currentVertex.position.x = 1.0f;
      if (i == 0) currentVertex.position.y = 1.0f;
      else        currentVertex.position.y = -1.0f;
      currentVertex.tex.x = (float)j;
      currentVertex.tex.y = (float)i;
      currentVertex.position.z = 0.0f;
    }
  }

  // indicies
  const UINT triCount = 2;
  meshData.indicies.resize(triCount * 3);
  UINT currentIndex = 0;

  // triangle #1: 0, 1, 3
  meshData.indicies[currentIndex++] = 0;
  meshData.indicies[currentIndex++] = 1;
  meshData.indicies[currentIndex++] = 3;
  // triangle #2: 0, 3, 2
  meshData.indicies[currentIndex++] = 0;
  meshData.indicies[currentIndex++] = 3;
  meshData.indicies[currentIndex++] = 2;
}
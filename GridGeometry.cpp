#include "GeometryGenerator.h"

///*
// m is the number of verticies we want going horizontal (+x direction)
// n is the number of verticies we want going down (-z direction)
//
//      col0, col1, col2...
//       <-------width------->
//           (n verts)
// (-halfWidth, halfDepth)
//   -->.___________________       --> +x
//     /_/_/_/_/_/_/_/_/_/_/     /                       row0
//    /             /_/_/_/    \/_ -z   depth (m verts)  row1
//   /(center is: (0,0)/_/                               row2...
//  (got bored of ascii art about here)
//*/
void GeometryGenerator::CreateGrid(float width, float depth, UINT m, UINT n, MeshData & meshData)
{
  UINT vertexCount = m * n;
  UINT quadCount = (m - 1) * (n - 1);
  UINT triCount = quadCount * 2; // also called faceCount

  float halfWidth = width / 2.0f;
  float halfDepth = depth / 2.0f;

  float dx = width / (n - 1);
  float dz = depth / (m - 1);

  //texture magic
  float du = 1.0f / (n - 1);
  float dv = 1.0f / (m - 1);

  ///////////////////////
  // Add the verticies //
  ///////////////////////
  meshData.verticies.resize(vertexCount);

  //flat plane
  float y = 0.0f;

  //For each row
  for (UINT i = 0; i < m; ++i)
  {
    // the z value is the same in each
    float z = halfDepth - i * dz;

    //For each column in the row
    for (UINT j = 0; j < n; ++j)
    {
      float x = -halfWidth + j * dx;
      VERTEX & currentVertex = meshData.verticies[i * n + j];
      currentVertex.position = D3DXVECTOR3(x, y, z);
      currentVertex.normal   = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
      currentVertex.tex.x = j * du;
      currentVertex.tex.y = i * dv;
    }
  }

  //////////////////////
  // Add the indicies //
  //////////////////////

  UINT indexCount = triCount * 3; // 3 indices per triangle

  if ( (int) indexCount > (int) UINT16_MAX)
  {
    ErrorMessage("Too many indicies");
  }

  meshData.indicies.resize(indexCount);

  //
  //                 vertex column j   vertex column j + 1
  //                       |               |
  //                       |               |
  //                       v               v
  // vertex row i ------>   _______________
  //                       |A           __/|B
  //                       |        __/    |   (pretend these are 2 triangles)
  //                       |     __/       |     forming the ij'th quad
  //                       |    /          |
  //                       | __/           |
  // vertex row i + 1 -->  |/______________|
  //                        C               D

  UINT currentIndex = 0;

  // for each quad in the row
  for (UINT i = 0; i < m - 1; ++i)
  {
    // for each quad in the column
    for (UINT j = 0; j < n - 1; ++j)
    {
      UINT vertexIndexA = i * n + j; // The index of vertex A in MeshData.verticies
      UINT vertexIndexB = vertexIndexA + 1;
      UINT vertexIndexC = (i + 1) * n + j;
      UINT vertexIndexD = vertexIndexC + 1;

      //Triangle ABC
      meshData.indicies[currentIndex++] = vertexIndexA;
      meshData.indicies[currentIndex++] = vertexIndexB;
      meshData.indicies[currentIndex++] = vertexIndexC;

      //Triangle CBD
      meshData.indicies[currentIndex++] = vertexIndexC;
      meshData.indicies[currentIndex++] = vertexIndexB;
      meshData.indicies[currentIndex++] = vertexIndexD;
    }
  }
}
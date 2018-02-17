#include "GeometryGenerator.h"

void GeometryGenerator::CreateCube(MeshData & meshData)
{
  //
  // Prepare for hardcoding
  //

  //               +y
  //               ^         _  +z
  //               |         /|
  //0          3--------2   /
  //1         /        /|
  //2        /        / |
  //3       0--------1  |  -----> +x
  //4       |  |     |  |
  //5       |  7--   |  6
  //6       | /      | /
  //7       |        |/
  //        4--------5

  meshData.verticies.resize(24);
  UINT currentVertex = 0;
  //                                  Position                                   Normal                           Tex (UVs)
  // side 1 (4 verticies per side)
  meshData.verticies[currentVertex++] = VERTEX( D3DXVECTOR3(-1.0f, 1.0f,-1.0f ), D3DXVECTOR3( 0.0f, 1.0f, 0.0f ), D3DXVECTOR2(0.0f, 0.0f) );
  meshData.verticies[currentVertex++] = VERTEX( D3DXVECTOR3( 1.0f, 1.0f,-1.0f ), D3DXVECTOR3( 0.0f, 1.0f, 0.0f ), D3DXVECTOR2(1.0f, 0.0f) );
  meshData.verticies[currentVertex++] = VERTEX( D3DXVECTOR3( 1.0f, 1.0f, 1.0f ), D3DXVECTOR3( 0.0f, 1.0f, 0.0f ), D3DXVECTOR2(1.0f, 1.0f) );
  meshData.verticies[currentVertex++] = VERTEX( D3DXVECTOR3(-1.0f, 1.0f, 1.0f ), D3DXVECTOR3( 0.0f, 1.0f, 0.0f ), D3DXVECTOR2(0.0f, 1.0f) );
  // side 2
  meshData.verticies[currentVertex++] = VERTEX( D3DXVECTOR3(-1.0f,-1.0f,-1.0f ), D3DXVECTOR3( 0.0f,-1.0f, 0.0f ), D3DXVECTOR2(0.0f, 0.0f) );
  meshData.verticies[currentVertex++] = VERTEX( D3DXVECTOR3( 1.0f,-1.0f,-1.0f ), D3DXVECTOR3( 0.0f,-1.0f, 0.0f ), D3DXVECTOR2(1.0f, 0.0f) );
  meshData.verticies[currentVertex++] = VERTEX( D3DXVECTOR3( 1.0f,-1.0f, 1.0f ), D3DXVECTOR3( 0.0f,-1.0f, 0.0f ), D3DXVECTOR2(1.0f, 1.0f) );
  meshData.verticies[currentVertex++] = VERTEX( D3DXVECTOR3(-1.0f,-1.0f, 1.0f ), D3DXVECTOR3( 0.0f,-1.0f, 0.0f ), D3DXVECTOR2(0.0f, 1.0f) );
  // side 3
  meshData.verticies[currentVertex++] = VERTEX( D3DXVECTOR3(-1.0f,-1.0f, 1.0f ), D3DXVECTOR3(-1.0f, 0.0f, 0.0f ), D3DXVECTOR2(0.0f, 0.0f) );
  meshData.verticies[currentVertex++] = VERTEX( D3DXVECTOR3(-1.0f,-1.0f,-1.0f ), D3DXVECTOR3(-1.0f, 0.0f, 0.0f ), D3DXVECTOR2(1.0f, 0.0f) );
  meshData.verticies[currentVertex++] = VERTEX( D3DXVECTOR3(-1.0f, 1.0f,-1.0f ), D3DXVECTOR3(-1.0f, 0.0f, 0.0f ), D3DXVECTOR2(1.0f, 1.0f) );
  meshData.verticies[currentVertex++] = VERTEX( D3DXVECTOR3(-1.0f, 1.0f, 1.0f ), D3DXVECTOR3(-1.0f, 0.0f, 0.0f ), D3DXVECTOR2(0.0f, 1.0f) );
  // side 4
  meshData.verticies[currentVertex++] = VERTEX( D3DXVECTOR3( 1.0f,-1.0f, 1.0f ), D3DXVECTOR3( 1.0f, 0.0f, 0.0f ), D3DXVECTOR2(0.0f, 0.0f) );
  meshData.verticies[currentVertex++] = VERTEX( D3DXVECTOR3( 1.0f,-1.0f,-1.0f ), D3DXVECTOR3( 1.0f, 0.0f, 0.0f ), D3DXVECTOR2(1.0f, 0.0f) );
  meshData.verticies[currentVertex++] = VERTEX( D3DXVECTOR3( 1.0f, 1.0f,-1.0f ), D3DXVECTOR3( 1.0f, 0.0f, 0.0f ), D3DXVECTOR2(1.0f, 1.0f) );
  meshData.verticies[currentVertex++] = VERTEX( D3DXVECTOR3( 1.0f, 1.0f, 1.0f ), D3DXVECTOR3( 1.0f, 0.0f, 0.0f ), D3DXVECTOR2(0.0f, 1.0f) );
  // sid e5
  meshData.verticies[currentVertex++] = VERTEX( D3DXVECTOR3(-1.0f,-1.0f,-1.0f ), D3DXVECTOR3( 0.0f, 0.0f,-1.0f ), D3DXVECTOR2(0.0f, 0.0f) );
  meshData.verticies[currentVertex++] = VERTEX( D3DXVECTOR3( 1.0f,-1.0f,-1.0f ), D3DXVECTOR3( 0.0f, 0.0f,-1.0f ), D3DXVECTOR2(1.0f, 0.0f) );
  meshData.verticies[currentVertex++] = VERTEX( D3DXVECTOR3( 1.0f, 1.0f,-1.0f ), D3DXVECTOR3( 0.0f, 0.0f,-1.0f ), D3DXVECTOR2(1.0f, 1.0f) );
  meshData.verticies[currentVertex++] = VERTEX( D3DXVECTOR3(-1.0f, 1.0f,-1.0f ), D3DXVECTOR3( 0.0f, 0.0f,-1.0f ), D3DXVECTOR2(0.0f, 1.0f) );
  // side 6
  meshData.verticies[currentVertex++] = VERTEX( D3DXVECTOR3(-1.0f,-1.0f, 1.0f ), D3DXVECTOR3( 0.0f, 0.0f, 1.0f ), D3DXVECTOR2(0.0f, 0.0f) );
  meshData.verticies[currentVertex++] = VERTEX( D3DXVECTOR3( 1.0f,-1.0f, 1.0f ), D3DXVECTOR3( 0.0f, 0.0f, 1.0f ), D3DXVECTOR2(1.0f, 0.0f) );
  meshData.verticies[currentVertex++] = VERTEX( D3DXVECTOR3( 1.0f, 1.0f, 1.0f ), D3DXVECTOR3( 0.0f, 0.0f, 1.0f ), D3DXVECTOR2(1.0f, 1.0f) );
  meshData.verticies[currentVertex++] = VERTEX( D3DXVECTOR3(-1.0f, 1.0f, 1.0f ), D3DXVECTOR3( 0.0f, 0.0f, 1.0f ), D3DXVECTOR2(0.0f, 1.0f) );

  UINT currentIndex = 0;
  const UINT faceCount = 6;
  const UINT trisPerFace = 2;
  const UINT indiciesPerTri = 3;
  meshData.indicies.resize(faceCount * trisPerFace * indiciesPerTri);
  //Face 1 Tri 1
  meshData.indicies[currentIndex++] = 3;
  meshData.indicies[currentIndex++] = 1;
  meshData.indicies[currentIndex++] = 0;

  //Face 1 Tri 2
  meshData.indicies[currentIndex++] = 2;
  meshData.indicies[currentIndex++] = 1;
  meshData.indicies[currentIndex++] = 3;

  //Face2 Tri 1
  meshData.indicies[currentIndex++] = 6;
  meshData.indicies[currentIndex++] = 4;
  meshData.indicies[currentIndex++] = 5;

  //Face2 Tri 2
  meshData.indicies[currentIndex++] = 7;
  meshData.indicies[currentIndex++] = 4;
  meshData.indicies[currentIndex++] = 6;

  //Face3 Tri 1
  meshData.indicies[currentIndex++] = 11;
  meshData.indicies[currentIndex++] = 9;
  meshData.indicies[currentIndex++] = 8;

  //Face3 Tri 2
  meshData.indicies[currentIndex++] = 10;
  meshData.indicies[currentIndex++] = 9;
  meshData.indicies[currentIndex++] = 11;

  //Face4 Tri 1
  meshData.indicies[currentIndex++] = 14;
  meshData.indicies[currentIndex++] = 12;
  meshData.indicies[currentIndex++] = 13;

  //Face4 Tri 2
  meshData.indicies[currentIndex++] = 15;
  meshData.indicies[currentIndex++] = 12;
  meshData.indicies[currentIndex++] = 14;

  //Face5 Tri 1
  meshData.indicies[currentIndex++] = 19;
  meshData.indicies[currentIndex++] = 17;
  meshData.indicies[currentIndex++] = 16;

  //Face5 Tri 2
  meshData.indicies[currentIndex++] = 18;
  meshData.indicies[currentIndex++] = 17;
  meshData.indicies[currentIndex++] = 19;

  //Face6 Tri 1
  meshData.indicies[currentIndex++] = 22;
  meshData.indicies[currentIndex++] = 20;
  meshData.indicies[currentIndex++] = 21;

  //Face6 Tri 2
  meshData.indicies[currentIndex++] = 23;
  meshData.indicies[currentIndex++] = 20;
  meshData.indicies[currentIndex++] = 22;
}
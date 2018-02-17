#include "VectorMath.h"

//Computes the nmomal of the triangle
// input : v0 - vertex0 of the triangle
//         v1 - vertex1 of the triangle
//         v2 - vertex2 of the triangle
D3DXVECTOR3 ComputeNormal( const D3DXVECTOR3 & v0,
  const D3DXVECTOR3 & v1,
  const D3DXVECTOR3 & v2 )
{
  D3DXVECTOR3 u = v1 - v0;
  D3DXVECTOR3 v = v2 - v0;

  D3DXVECTOR3 normal;
  D3DXVec3Cross(&normal, &u, &v);

  return normal;
}

//Sets the normal of each vertex to the average of all its adjacent faces
void AverageNormals(std::vector<VERTEX> & verticies,
                    std::vector<UINT16> & indicies)
{
  //ASSUMPTION:
  UINT numTriangles = indicies.size() / 3;

  // 1. First, clear the normals of each triangle
  for (UINT i = 0; i < verticies.size(); ++i)
  {
    verticies[i].normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
  }

  // 2. for each tri add the facenormal to the vertex
  for (UINT i = 0; i < numTriangles; ++i)
  {
    //indicies of each triangle index
    UINT index0 = indicies[i*3];
    UINT index1 = indicies[i*3 + 1];
    UINT index2 = indicies[i*3 + 2];

    VERTEX & vertex0 = verticies[index0];
    VERTEX & vertex1 = verticies[index1];
    VERTEX & vertex2 = verticies[index2];

    //compute the normal
    D3DXVECTOR3 faceNormal = ComputeNormal(vertex0.position,
      vertex1.position,
      vertex2.position);

    //add the normal to each vertex
    vertex0.normal += faceNormal;
    vertex1.normal += faceNormal;
    vertex2.normal += faceNormal;
  }

  // 3. normalize each normal
  for (UINT i = 0; i < verticies.size(); ++i)
  {
    D3DXVec3Normalize(&verticies[i].normal, &verticies[i].normal);
  }
}

D3DXMATRIX InverseTranspose(const D3DXMATRIX & matrix)
{
  D3DXMATRIX output;

  float determinant = D3DXMatrixDeterminant(&matrix);

  D3DXMatrixInverse(&output, &determinant, &matrix);
  D3DXMatrixTranspose(&output, &output);
  return output;
}

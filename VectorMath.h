#pragma once
#include <d3dx10math.h>
#include <vector>
#include "Vertex.h"

//Computes the nmomal of the triangle
D3DXVECTOR3 ComputeNormal(const D3DXVECTOR3 & v0, const D3DXVECTOR3 & v1, const D3DXVECTOR3 & v2);

//Sets the normal of each vertex to the average of all its adjacent faces
void AverageNormals(std::vector<VERTEX> & verticies,
                    std::vector<UINT16> & indicies);

// I don't know why you would use this function in a non-shader program.
// (note: you use the INVERSETRANSPOSE of a vertex's transformation to
//        transform the vertex's normal vectors)
D3DXMATRIX InverseTranspose(const D3DXMATRIX & matrix);
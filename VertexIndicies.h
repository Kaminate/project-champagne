#pragma once
#include "Vertex.h"
#include "Cout_for_DirectX.h"
#include "VertexPosition.h"
#include "VertexTexture.h"
#include "VertexNormal.h"

#include <sstream>
#include <iostream>
#include <vector>

class VertexIndicies
{
public:
  unsigned vertexIndex;
  unsigned textureIndex;
  unsigned normalIndex;

  bool operator == (VertexIndicies & rhs);
  friend std::stringstream & operator>>(std::stringstream& ss, VertexIndicies& vertexIndicies);

  VERTEX BuildVertex(std::vector<VertexPosition> * vertexPositions ,
    std::vector<VertexTexture> * vertexTextures,
    std::vector<VertexNormal> * vertexNormals);

private:
};

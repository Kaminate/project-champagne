#include "VertexIndicies.h"

bool VertexIndicies::operator == (VertexIndicies & rhs)
{
  if (vertexIndex != rhs.vertexIndex) return false;
  if (textureIndex != rhs.textureIndex) return false;
  if (normalIndex != rhs.textureIndex) return false;
  return true;
}

std::stringstream & operator>>(std::stringstream & ss, VertexIndicies & vertexIndicies)
{
  ss >> vertexIndicies.vertexIndex;
  ss >> vertexIndicies.textureIndex;
  ss >> vertexIndicies.normalIndex;
  return ss;
}

VERTEX VertexIndicies::BuildVertex(std::vector<VertexPosition> * vertexPositions ,
  std::vector<VertexTexture> * vertexTextures,
  std::vector<VertexNormal> * vertexNormals)
{
  VERTEX vertex;
  vertex.position = ((*vertexPositions)[this->vertexIndex - 1]).position;
  vertex.tex      = ((*vertexTextures)[this->textureIndex - 1]).uv;
  vertex.normal   = ((*vertexNormals)[this->normalIndex - 1]).normal;
  return vertex;
}
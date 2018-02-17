#include "VertexNormal.h"

VertexNormal::VertexNormal()
{
}

VertexNormal::VertexNormal(float x, float y, float z):
  normal(x, y, z)
{
}

//this is a friend function
std::ostream& operator<<(std::ostream& os, const VertexNormal& vertexNormal)
{
  os << "VertexNormal: " << vertexNormal.normal;
  return os;
}
#include "VertexPosition.h"

VertexPosition::VertexPosition()
{
}

VertexPosition::VertexPosition(float x, float y, float z):
position(x, y, z)
{
}

//this is a friend function
std::ostream& operator<<(std::ostream& os, const VertexPosition& vertexPosition)
{
  os << "VertexPosition: " << vertexPosition.position;
  return os;
}
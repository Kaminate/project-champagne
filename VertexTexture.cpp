#include "VertexTexture.h"

VertexTexture::VertexTexture()
{
}

VertexTexture::VertexTexture(float u, float v):
  uv(u, v)
{
}

//this is a friend function
std::ostream& operator<<(std::ostream& os, const VertexTexture & VertexTexture)
{
  os << "VertexTexture: " << VertexTexture.uv;
  return os;
}
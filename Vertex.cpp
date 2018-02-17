#include "Vertex.h"

VERTEX::VERTEX():
  position(0.0f, 0.0f, 0.0f),
  normal(0.0f, 0.0f, 0.0f),
  tex(0.0f, 0.0f)
{
}

VERTEX::VERTEX(const D3DXVECTOR3 & position,
               const D3DXVECTOR3 & normal,
               const D3DXVECTOR2 & tex):
  position(position),
  normal(normal),
  tex(tex)
{
}

//this is a friend function
std::ostream& operator<<(std::ostream& os, const VERTEX& vertex)
{
  os << "Vertex: " << std::endl;
  os << "  Position: " << vertex.position << std::endl;
  os << "  Normal:   " << vertex.normal << std::endl;
  os << "  Texture:  " << vertex.tex << std::endl;
  return os;
}
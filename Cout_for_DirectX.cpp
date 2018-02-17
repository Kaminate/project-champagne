#include "Cout_for_DirectX.h"

std::ostream& operator << (std::ostream & lhs, const D3DXVECTOR3 & rhs)
{
  lhs.precision(2);
  return lhs << std::fixed << "(" << rhs.x << ", " << rhs.y << ", " << rhs.z << ")";
}

std::ostream& operator << (std::ostream & lhs, const D3DXVECTOR2 & rhs)
{
  lhs.precision(2);
  return lhs << std::fixed << "(" << rhs.x << ", " << rhs.y << ")";
}
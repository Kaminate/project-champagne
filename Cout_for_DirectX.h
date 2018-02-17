#pragma once
#include <iostream>
#include <d3dx10math.h>

std::ostream& operator << (std::ostream & lhs, const D3DXVECTOR3 & rhs);
std::ostream& operator << (std::ostream & lhs, const D3DXVECTOR2 & rhs);
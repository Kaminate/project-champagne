#pragma once
#include <iostream>
#include <d3dx10math.h>
#include "Cout_for_DirectX.h"

struct VERTEX
{
  VERTEX();
  VERTEX(const D3DXVECTOR3 & position,
         const D3DXVECTOR3 & normal,
         const D3DXVECTOR2 & tex);

  D3DXVECTOR3 position;
  //D3DXCOLOR color; deprecated
  D3DXVECTOR3 normal;
  D3DXVECTOR2 tex;

  friend std::ostream& operator<<(std::ostream& os, const VERTEX & vertex);
};

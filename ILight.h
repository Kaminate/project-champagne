#pragma once

//#include "Direct3D.h"
#include <d3dx12math.h>

class ILight
{
public:
//protected:
  //virtual void foo() = 0; // Makes this class virtual so I can dynamic cast it
                          // (see: DirectionalLightNode.cpp)
  ILight(
         const D3DXCOLOR& ambient,
         const D3DXCOLOR& diffuse,
         const D3DXCOLOR& specular):
         ambient(ambient),
         diffuse(diffuse),
         specular(specular)
    {
    } 
    
  
//private:
  D3DXCOLOR ambient;
  D3DXCOLOR diffuse;
  D3DXCOLOR specular;
};
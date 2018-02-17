#pragma once
#include "ILight.h"

class PointLight : public ILight
{
public:
  struct WorldspacePointLight
  {
    WorldspacePointLight(PointLight * pointLight, D3DXMATRIX lightWorldMatrix):
      pointLight(pointLight), lightWorldMatrix(lightWorldMatrix)
      {

      }
    
    PointLight * pointLight;
    D3DXMATRIX lightWorldMatrix;
  };

  PointLight(
    D3DXCOLOR ambient,
    D3DXCOLOR diffuse,
    D3DXCOLOR specular,

    D3DXVECTOR3 position,
    float range,
    D3DXVECTOR3 attenuation);

//private:
  D3DXVECTOR4 position;
  float range;
  D3DXVECTOR4 attenuation; //(constant, linear, quadratic)
                           //http://escience.anu.edu.au/lecture/cg/IlluminationJ3D/pointLightAttenuation.en.html
};
#pragma once

#include "ILight.h"

class SpotLight : public ILight
{
public:
  struct WorldspaceSpotLight
  {
    WorldspaceSpotLight(SpotLight * spotLight, D3DXMATRIX lightWorldMatrix):
      spotLight(spotLight), lightWorldMatrix(lightWorldMatrix)
    {
    }
    SpotLight * spotLight;
    D3DXMATRIX lightWorldMatrix;
  };

  SpotLight(
    D3DXCOLOR ambient,
    D3DXCOLOR diffuse,
    D3DXCOLOR specular,

    D3DXVECTOR3 position,
    float range,
    D3DXVECTOR3 direction,
    float spot,
    D3DXVECTOR3 attenuation);

private:
  D3DXVECTOR3 position;
  float range;
  D3DXVECTOR3 direction;
  float spot;
  D3DXVECTOR3 attenuation;
};
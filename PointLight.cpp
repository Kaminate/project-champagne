#include "PointLight.h"

PointLight::PointLight(D3DXCOLOR ambient, D3DXCOLOR diffuse, D3DXCOLOR specular, D3DXVECTOR3 position, float range, D3DXVECTOR3 attenuation):
  ILight(ambient, diffuse, specular),
  //ambient(ambient),
  //diffuse(diffuse),
  //specular(specular),

  position(position),
  range(range),
  attenuation(attenuation)
{
}
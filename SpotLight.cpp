#include "SpotLight.h"

SpotLight::SpotLight(
  D3DXCOLOR ambient,
  D3DXCOLOR diffuse,
  D3DXCOLOR specular,

  D3DXVECTOR3 position,
  float range,
  D3DXVECTOR3 direction,
  float spot,
  D3DXVECTOR3 attenuation):
    ILight(ambient, diffuse, specular),
    position(position),
    range(range),
    direction(direction),
    spot(spot),
    attenuation(attenuation)
{
}
#include "tempGlobals.h"
#include "PartyLight.h"
#include <d3dx10math.h>

D3DXCOLOR ambient(0.2f, 0.2f, 0.0f, 0.0f);;
D3DXCOLOR diffuse = partyLight1.GetRGB();
D3DXCOLOR specular(0.5f, 0.5f, 0.5f, 8.0f); //a is shinyness
D3DXVECTOR3 position(8.0f, 5.0f, 0.0f);
float range(105.0f);
D3DXVECTOR3 attenuation(1.0f, 1.0f, 0.0f);

PointLight * gPointLight = new PointLight (
  ambient, diffuse, specular, position, range, attenuation);
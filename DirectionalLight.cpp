#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(D3DXCOLOR ambient, D3DXCOLOR diffuse, D3DXCOLOR specular, D3DXVECTOR3 direction):
  ILight(ambient, diffuse, specular),
  //ambient(ambient),
  //diffuse(diffuse),
  //specular(specular),

  direction(direction)
{
}

//void DirectionalLight::Draw(Direct3D & renderer, D3DXMATRIX worldMatrix)
//{
//}
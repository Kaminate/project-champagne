#pragma once

#include "ILight.h"

class DirectionalLight : public ILight
{
public:

  struct WorldspaceDirectionalLight
  {
    WorldspaceDirectionalLight(DirectionalLight * directionalLight, D3DXMATRIX lightWorldMatrix):
      directionalLight(directionalLight), lightWorldMatrix(lightWorldMatrix)
      {

      }
    DirectionalLight * directionalLight;
    D3DXMATRIX lightWorldMatrix;
  };

  DirectionalLight(D3DXCOLOR ambient,
                   D3DXCOLOR diffuse,
                   D3DXCOLOR specular,

                   D3DXVECTOR3 direction);
  //virtual void Draw(Direct3D & renderer, D3DXMATRIX worldMatrix);

private:
  D3DXVECTOR3 direction;
};
#pragma once

#include <d3dx10math.h>

struct ConstantBuffer
{
  // matrix world
  D3DXMATRIX mWorld;
  D3DXMATRIX mInvTransWorld;
  // matrix view
  D3DXMATRIX mView;
  D3DXMATRIX mInvTransView;
  // matrix projection
  D3DXMATRIX mProjection;

  //lighting
  D3DXVECTOR4 lightPosition; //for a point/spot light
  D3DXVECTOR4 lightDirection; //for directional/spot light
  D3DXCOLOR lightAmbientColor;
  D3DXCOLOR lightDiffuseColor;
  D3DXCOLOR lightSpecularColor; // use alpha component as shinyness exponent for specular

  D3DXVECTOR4 attenuation;

  //camera eye direction
  D3DXVECTOR4 cameraEyeDirection;
  //float range;
  //float padding1;
  //float padding2;
  //float padding3;
  D3DXVECTOR4 range; //range is in the x component
};

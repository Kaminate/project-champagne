#pragma once
#include "ILightNode.h"
#include "DirectionalLight.h"
#include "ErrorMessage.h"
#include "RenderGroup.h"

class DirectionalLightNode : public RenderGroup
{
public:
  DirectionalLightNode(DirectionalLight* directionalLight):directionalLight(directionalLight){}
  virtual void Visit(Direct3D & renderer);
  /* virtual void RenderLight()
  {
  RenderDirectionalWorldspaceLight(WorldspaceDirectionalLight & dood);
  }*/
private:
  DirectionalLight * directionalLight;
};
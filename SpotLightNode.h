#pragma once

#include "ILightNode.h"
#include "SpotLight.h"
#include "RenderGroup.h"

class SpotLightNode : public RenderGroup
{
public:
  SpotLightNode(SpotLight * spotLight):spotLight(spotLight){}
  virtual void Visit(Direct3D & renderer);

private:
  SpotLight * spotLight;
};
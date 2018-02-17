#pragma once

#include "ILightNode.h"
#include "PointLight.h"
#include "RenderGroup.h"

class PointLightNode : public RenderGroup
{
public:
  PointLightNode(PointLight * pointLight):pointLight(pointLight){}
  virtual void Visit(Direct3D & renderer);

private:
  PointLight * pointLight;
};
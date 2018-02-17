#pragma once

#include "RenderNode.h"
#include "ILight.h"

class ILightNode : public RenderNode
{
public:
  ILightNode(ILight * light)
  {
    CheckLightType();
    this->light = light;
  }

  ~ILightNode()
  {
    if (light) delete light;
  }

  virtual void Visit(Direct3D & renderer) = 0;

protected:

  virtual void CheckLightType() = 0;
  ILight * light;
};

#pragma once

#include "ModelNode.h"

class RigidBody
{
public:
  RigidBody();

  //IMPORTANT:
  // The transform data (pos, etc) is contained inside the modelnode pointer.
  // We will modify that data directly
  RenderGroup * renderGroup;
  D3DXVECTOR3 velocity;

  void Integrate(float dt);

//private:
};
#pragma once

//i may not need all of these
#include "graphics.h"
#include "ModelNode.h"
#include "RenderGroup.h"
#include "PhysicsWorld.h"
#include "RigidBody.h"

class GameObject
{
public:
  GameObject();
  RenderGroup * renderGroup;
  RigidBody * rigidBody;
//private:
};
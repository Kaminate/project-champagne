#pragma once

//#include "GameObject.h"
#include "RigidBody.h"
#include "GameObjectManager.h" //MAX_OBJECTS

class PhysicsWorld
{
public:
  const unsigned int MAX_RIGID_BODIES;
  PhysicsWorld();
  ~PhysicsWorld();

  RigidBody * rigidBodyList;
  unsigned int numBodies;

  void IntegrateWorld(float dt);
//private:
};
#include "PhysicsWorld.h"

PhysicsWorld::PhysicsWorld():
  numBodies(0),
  MAX_RIGID_BODIES(100),
  rigidBodyList(new RigidBody[MAX_RIGID_BODIES])
{
}

PhysicsWorld::~PhysicsWorld()
{
  delete[] rigidBodyList;
}

void PhysicsWorld::IntegrateWorld(float dt)
{
  for (unsigned int i = 0; i < numBodies; ++i)
  {
    (rigidBodyList[i]).Integrate(dt);
  }
}
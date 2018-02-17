#include "RigidBody.h"

RigidBody::RigidBody():renderGroup(NULL),velocity(0.0f, 0.0f, 0.0f)
{
}

void RigidBody::Integrate(float dt)
{
  //pos += velcity * dt
  //if(modelNode) not sure who should check this
  {
    //multiply the velocity by the rotation matrix
    D3DXMATRIX rot;
    D3DXMatrixRotationYawPitchRoll(&rot, renderGroup->rotationY,
                                         renderGroup->rotationX,
                                         renderGroup->rotationZ);

    D3DXVECTOR3 velocityRotated;
    //velocityRotated = rot * velocity;
    D3DXVec3TransformCoord(&velocityRotated, &velocity, &rot);

    renderGroup->positionX += velocityRotated.x * dt;
    renderGroup->positionY += velocityRotated.y * dt;
    renderGroup->positionZ += velocityRotated.z * dt;
  }
}
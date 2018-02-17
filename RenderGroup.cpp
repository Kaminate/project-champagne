#include <algorithm>
#include <iostream> //cout debugging

#include "RenderGroup.h"
#include "Direct3D.h"

RenderGroup::RenderGroup():
  rotationX(0),
  rotationY(0),
  rotationZ(0),
  scaleX(1),
  scaleY(1),
  scaleZ(1),
  positionX(0),
  positionY(0),
  positionZ(0)
{
}

RenderGroup::~RenderGroup()
{
  //todo: call all the children's destructors
}

void RenderGroup::AddChild(RenderNode * child)
{
  children.push_back(child);
  child->parent = this;
}

D3DXMATRIX RenderGroup::GetTransform()
{
  D3DXMATRIX scale;
  D3DXMatrixScaling(&scale, scaleX, scaleY, scaleZ);

  D3DXMATRIX translation;
  D3DXMatrixTranslation(&translation, positionX, positionY, positionZ);

  D3DXMATRIX rot;
  D3DXMatrixRotationYawPitchRoll(&rot, rotationY, rotationX, rotationZ);

  return scale * rot * translation; //TODO: return all concatonated together
}

void RenderGroup::VisitChildren(Direct3D & renderer)
{
  for (auto it = children.begin(); it != children.end(); ++it)
  {
    (*it)->Visit(renderer);
  }
}

void RenderGroup::Visit(Direct3D & renderer)
{
//  std::cout << "RenderGroup visited!" << std::endl;

  renderer.Push(GetTransform() * renderer.Top());

  VisitChildren(renderer);

  renderer.Pop();
}
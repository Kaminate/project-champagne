#pragma once

//#include "Renderer.h"
#include "Direct3D.h"

/*!
  @brief The RenderNode is the base class of all rendernodes.
*/
class RenderNode
{
public:
  RenderNode();
  virtual void Visit(Direct3D & renderer) = 0;
  virtual D3DXMATRIX GetTransform();
  D3DXVECTOR4 GetWorldCoordinates();
  D3DXMATRIX GetWorldTransform();
//private:
  RenderNode * parent;
};
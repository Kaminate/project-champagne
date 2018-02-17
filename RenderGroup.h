#pragma once

#include <list>

#include "RenderNode.h"
#include "Direct3D.h"

class RenderGroup : public RenderNode
{
public:
  RenderGroup();
  ~RenderGroup();
  void AddChild(RenderNode * child);
  virtual void Visit( Direct3D & renderer);

  virtual D3DXMATRIX GetTransform(); //builds the transform matrix from the private vars
  //TODO: make these private
  float rotationX;
  float rotationY;
  float rotationZ;
  float scaleX;
  float scaleY;
  float scaleZ;
  float positionX;
  float positionY;
  float positionZ;
  void VisitChildren(Direct3D & renderer);
//private: commenting out because i'm making a quick game.
  // TODO: uncomment the above comment
  std::list<RenderNode *> children;
};

#include "RenderNode.h"

#include <iostream> //cout debugging

RenderNode::RenderNode():
  parent(NULL)
{
}

D3DXMATRIX RenderNode::GetTransform()
{
  D3DXMATRIX identity;
  D3DXMatrixIdentity(&identity);
  return identity;
}

D3DXVECTOR4 RenderNode::GetWorldCoordinates()
{
  D3DXVECTOR4 point(0.0f,0.0f,0.0f,1.0f); // (0, 0, 0, 1) in object space

  RenderNode * currentNode = this;
  D3DXMATRIX transform;

  while(currentNode->parent != NULL)
  {
    transform = currentNode->GetTransform();
    D3DXVec4Transform(&point, &point, &transform);
    currentNode = currentNode->parent;
  }

  return point;
}

D3DXMATRIX RenderNode::GetWorldTransform()
{
  RenderNode * currentNode = this;
  D3DXMATRIX transform = currentNode->GetTransform();

  while(currentNode->parent != NULL)
  {
    // To verify: order
     transform = transform * currentNode->parent->GetTransform() ;

    //transform = currentNode->parent->GetTransform() * transform  ;
    currentNode = currentNode->parent;
  }

  return transform;
}
#pragma once

//#include <windows.h>
//#include <xnamath.h>

#include "RenderGroup.h"
#include "Direct3D.h"

class ModelNode : public RenderGroup
{
public:
  ModelNode();
  //TODO PERHAPS: overload the ctor to take a ID3D11Buffer pointer

  ~ModelNode(); //Releases the pVertexBuffer com object

  virtual void Visit(Direct3D & renderer);

  void AssignVertices(ID3D11Buffer * pVertexBuffer);
  void AssignIndicies(ID3D11Buffer * pIndexBuffer);
  void AssignIndicies(IndexBuffer * indexBuffer);

  void AssignMesh(Mesh * pMesh);

//private:
  bool visible;

  ID3D11Buffer * pVertexBuffer;
  ID3D11Buffer * pIndexBuffer;
  IndexBuffer * indexBuffer;
  Mesh * pMesh;
};
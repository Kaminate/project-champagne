#pragma once

#include <Windows.h>
#include <xnamath.h>

#include "ModelNode.h"
#include "Direct3D.h"

class BoxNode : public ModelNode
{
public:
 virtual void Visit(Direct3D & renderer);
  //static void CreateBoxTopology(); // Must be called once before boxnodes are created

private:
  //virtual ID3D11Buffer * pVertexBuffer = NULL;
  //static ID3D11Buffer * pIndexBuffer = NULL;
};

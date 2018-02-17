#include <d3d10_1.h>
#include <d3dx10math.h>
#include <iostream>

#include "BoxNode.h"

void BoxNode::Visit(Direct3D & renderer)
{
  /*
  //std::cout << "BoxNode visited!" << std::endl;

  // Push the box's transform onto the matrix stack
  renderer.Push(renderer.Top() * GetTransform());

  //select the vertex buffer
  UINT stride = sizeof(VERTEX);
  UINT offset = 0;
  //renderer.deviceContext->IASetVertexBuffers(0, 1, &(renderer.pVertexBuffer), &stride, &offset);
  renderer.deviceContext->IASetVertexBuffers(0, 1, &(this->pVertexBuffer), &stride, &offset);

  //select the primitive
  renderer.deviceContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

  // Set index buffer
  renderer.deviceContext->IASetIndexBuffer( (renderer.pIndexBuffer), DXGI_FORMAT_R16_UINT, 0 );

  //select the constantbuffer
  renderer.deviceContext->VSSetConstantBuffers(0, 1, &(renderer.pConstantBuffer));

  //set our shaders to be the active shaders
  renderer.deviceContext->VSSetShader((renderer.pVertexShader), 0, 0);
  renderer.deviceContext->PSSetShader(*(renderer.ppCurrentPixelShader), 0, 0);

  //draw the vertex buffer onto the back buffer
  renderer.deviceContext->DrawIndexed(36,0, 0);

  RenderGroup::Visit(renderer);

  // pop
  renderer.Pop();
  */
}

//
//void BoxNode::CreateBoxTopology()
//{
//
//}
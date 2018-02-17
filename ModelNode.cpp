#include "ModelNode.h"
#include <iostream>

#include "ColorHSV.h"
#include "PartyLight.h"
#include "tempGlobals.h"
#include "VectorMath.h"

ModelNode::ModelNode() :
  pVertexBuffer(NULL),
  pIndexBuffer(NULL),
  indexBuffer(NULL),
  pMesh(NULL),
  visible(true)
{
}

ModelNode::~ModelNode()
{
  if (pVertexBuffer)
  {
    pVertexBuffer->Release();
  }
}

void ModelNode::Visit(Direct3D & renderer)
{
  // Push our matrix onto the stack
  renderer.Push(GetTransform() * renderer.Top());

  if (visible && pMesh )//&& pVertexBuffer)
  {
    //select the vertex buffer
    UINT stride = sizeof(VERTEX);
    UINT offset = 0;

    renderer.deviceContext->IASetVertexBuffers(
      0, 1, &(pMesh->pVertexBuffer), &stride, &offset);
    renderer.deviceContext->IASetPrimitiveTopology(
      D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    renderer.deviceContext->IASetIndexBuffer(
      pMesh->pIndexBuffer->pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

    // constant buffer
    ConstantBuffer cb;

    cb.mWorld = renderer.Top();
    cb.mView = renderer.viewMatrix;
    cb.mProjection = renderer.projMatrix;

    //compute inverse transpose for transforming normals
    cb.mInvTransWorld = InverseTranspose(cb.mWorld);
    cb.mInvTransView = InverseTranspose(cb.mView);
    
    cb.lightDirection = D3DXVECTOR4(0.0f, -0.25f, 1.0f, 1.0f);

    ////rotate the light direction
    //static float rotationY = 0.0f;
    //rotationY += (float)D3DX_PI /(8.0f * 4.0f * 60.0f);
    //D3DXMATRIX lightRotationY;
    //D3DXMatrixRotationY(&lightRotationY, rotationY);

    //D3DXVec4Transform(&cb.lightDirection, &cb.lightDirection, &lightRotationY);

    //colored lighting
    cb.lightPosition      = gPointLight->position;
    // point light is omnidir, so fill with junk
    cb.lightDirection     = D3DXVECTOR4(0.0f, -0.5f, 1.0f, 0.0f); 
    cb.lightAmbientColor  = gPointLight->ambient;
    cb.lightDiffuseColor  = gPointLight->diffuse;
    cb.lightSpecularColor = gPointLight->specular;
    cb.range.x            = gPointLight->range;
    gPointLight->range   += 0.001f;
    cb.attenuation        = gPointLight->attenuation;
    // TODO: don't hardcode this
    cb.cameraEyeDirection = D3DXVECTOR4(0.0f, 0.0f, 1.0f,0.0f); 

    renderer.deviceContext->UpdateSubresource(
      renderer.pCBChangesEveryFrame, 0, NULL, &cb, 0, 0);

    //select the constantbuffer
    renderer.deviceContext->VSSetConstantBuffers(0,  1, &(renderer.pCBChangesEveryFrame));
    renderer.deviceContext->PSSetConstantBuffers(0,  1, &(renderer.pCBChangesEveryFrame));

    //set our shaders to be the active shaders
    renderer.deviceContext->VSSetShader((renderer.pVertexShader), 0, 0);
    renderer.deviceContext->PSSetShader(*(renderer.ppCurrentPixelShader), 0, 0);

    
    UINT indexcount = pMesh->pIndexBuffer->indexCount;
    renderer.deviceContext->DrawIndexed(indexcount, 0, 0);
  }

  //RenderGroup::Visit(renderer);
  VisitChildren(renderer);

  renderer.Pop();
}

void ModelNode::AssignVertices(ID3D11Buffer * pVertexBuffer)
{
  this->pVertexBuffer = pVertexBuffer;
}

void ModelNode::AssignIndicies(ID3D11Buffer * pIndexBuffer)
{
  this->pIndexBuffer = pIndexBuffer;
}

void ModelNode::AssignIndicies(IndexBuffer * indexBuffer)
{
  this->indexBuffer = indexBuffer;
}

void ModelNode::AssignMesh(Mesh * pMesh)
{
  this->pMesh = pMesh;
}

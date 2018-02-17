#include "SpotLightNode.h"

void SpotLightNode::Visit(Direct3D & renderer)
{
  // Push it's matrix on top of the matrix stack
  D3DXMATRIX lightWorldPos = RenderGroup::GetTransform() * renderer.Top();
  renderer.Push(lightWorldPos);


  // Save it's current matrix for deferred shading
  renderer.worldspaceSpotLights.push(SpotLight::WorldspaceSpotLight(spotLight, lightWorldPos));

  // It's a rendergroup, so visit children
  RenderGroup::VisitChildren(renderer);

  // Pop matrix that we pushed onto the stack at the beginning of this function
  renderer.Pop();
}
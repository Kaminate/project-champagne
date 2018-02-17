#pragma once

// screen resolution
//extern const unsigned int SCREEN_WIDTH;
//extern const unsigned int SCREEN_HEIGHT;
#include <map>
#include <string>

#include "Renderer.h"
#include "RenderGroup.h"
#include "RenderNode.h"

//class Camera; //forwad declaration to avoid circlular
#include "camera.h"
#include "Direct3D.h"
#include "VertexBuffer.h"

/*!
  @brief The responsibility of the Graphics object is to initialize the drawing
  process. It does this by taking the Camera matrices and pushing them onto
  the matrix stack inside the renderer, and then telling the renderer to
  traverse the rendertree.

  Oh, and it initializes all the directx stuff
*/
class Graphics
{
public:
  Graphics(unsigned int screenWidth, unsigned int screenHeight, HWND hWnd);

  void Draw(RenderGroup & root, Camera & camera);

  //TODO: replace Direct3D direct3d with Renderer * renderer;
  Direct3D direct3d; // Created in the initializer list

private:

  unsigned int screenWidth;
  unsigned int screenHeight;
};

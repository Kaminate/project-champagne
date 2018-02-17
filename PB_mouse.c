/******************************************************************************/
/*
 @file     PB_mouse.c
 @project  Photon Bunny
 @author   Justin Cook
 
 All content (c) 2012 DigiPen (USA) Corporation, all rights reserved.
 */
/******************************************************************************/

#include "PB_mouse.h"

#include <assert.h>
#include <windows.h>
#include "AEEngine.h"
#include "PB_def.h"

static HWND hwnd_;

Vec2 mousePosition()
{
  RECT clientRect;
  POINT mouse;
  float offsetX;
  float offsetY;
  float scaleX;
  float scaleY;
  if (!hwnd_) hwnd_ = AESysGetWindowHandle();
  assert(hwnd_);

  GetClientRect(hwnd_, &clientRect);
  GetCursorPos(&mouse);
  ScreenToClient(hwnd_, &mouse);

  offsetX = 0.0f;
  offsetY = 0.0f;
  scaleX = CANVAS_WIDTH / (float) (clientRect.right - clientRect.left);
  scaleY = CANVAS_HEIGHT / (float) (clientRect.bottom - clientRect.top);
  
  return
    vec2
    (
      (float)mouse.x * scaleX + offsetX, 
      (float)mouse.y * scaleY + offsetY
    );
}



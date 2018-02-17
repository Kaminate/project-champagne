#pragma once

#include "Renderer.h"

class DirectXRenderer : public Renderer
{
public:
  DirectXRenderer();
  ~DirectXRenderer();

private:
  // pointer to the device
  // pointer to the devicecontext
  // etc
};
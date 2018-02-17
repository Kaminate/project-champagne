#pragma once

// note: you MUST include windows.h before xnamath.h
#include <Windows.h>

#include <d3d11.h>
#include <d3dx11.h>
#include <d3d10_1.h>
#include <d3dx10.h>

class Camera
{
public:
  Camera();

  void SetPosition(const D3DXVECTOR3 & pos);
  D3DXVECTOR3 GetPosition();

  void SetEyeDirection(const D3DXVECTOR3 & dir);
  D3DXVECTOR3 GetEyeDirection();

  D3DXMATRIX GetViewMatrix();
  D3DXMATRIX GetProjectionMatrix();

private:
  D3DXMATRIX gProjection; // the perspective projection matrix.

  D3DXVECTOR3 eyePosition;
  D3DXVECTOR3 upDirection; // defines the current world's up, usually [0, 1, 0].

  // Important note:
  // - Currently, the focalPoint = eyePosition + eyeDirection
  // - TODO: Add a flag that determines whether focalPoint or eyeDirection
  //         be used to determine the viewMatrix
  D3DXVECTOR3 focalPoint;
  D3DXVECTOR3 eyeDirection;
};

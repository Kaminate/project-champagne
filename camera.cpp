#include "camera.h"

Camera::Camera():
  eyePosition(D3DXVECTOR3(0.0f, 0.0f, -10.0f)),
  upDirection(D3DXVECTOR3(0.0f, 1.0f, 0.0f)),
  focalPoint(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
  eyeDirection(D3DXVECTOR3(0.0f, 0.0f, 1.0f))
{
  float PiOver2 = (float)D3DX_PI / 2.0f;
  float aspectRatio = 800 / 600.0f;
  float zNear = 0.01f;
  float zFar = 100.0f;

  D3DXMatrixPerspectiveFovLH(&gProjection, PiOver2, aspectRatio, zNear, zFar);
}

void Camera::SetPosition(const D3DXVECTOR3 & newEyePosition)
{
  eyePosition = newEyePosition;
}

void Camera::SetEyeDirection(const D3DXVECTOR3 & dir)
{
  eyeDirection = dir;
}

D3DXVECTOR3 Camera::GetEyeDirection()
{
  return eyeDirection;
}

D3DXMATRIX Camera::GetProjectionMatrix()
{
  return gProjection;
}

D3DXVECTOR3 Camera::GetPosition()
{
  return eyePosition;
}

D3DXMATRIX Camera::GetViewMatrix()
{
  // Returns a view matrix that transforms a
  // point from world space into view space.

  D3DXMATRIX viewMatrix;

  focalPoint = eyePosition + eyeDirection;

  D3DXMatrixLookAtLH(&viewMatrix, &eyePosition, &focalPoint, &upDirection);

  return viewMatrix;
}
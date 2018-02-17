//#include "FullscreenRenderTexture.h"
//
//
//FullscreenRenderTexture::FullscreenRenderTexture(void)
//{
//}
//
//
//FullscreenRenderTexture::~FullscreenRenderTexture(void)
//{
//}
//
//void FullscreenRenderTexture::Initialize(ID3D11Device * device, DXGI_FORMAT format)
//{
//  // Screen Rect
//  RECT rc;
//  GetClientRect( hWnd, &rc ); // Need to make hWnd global or something
//  UINT width = rc.right - rc.left;
//  UINT height = rc.bottom - rc.top;
//
//  RenderTexture::Initialize(device, DXGI_FORMAT_B8G8R8A8_UNORM, width, height);
//}
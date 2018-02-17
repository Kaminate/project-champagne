//#include "VertexBuffer.h"

//VertexBuffer::VertexBuffer(Direct3D * direct3d, VERTEX vertices [])
//{
//  // create the vertex buffer
//  D3D11_BUFFER_DESC bufferDescription;
//  ZeroMemory(&bufferDescription, sizeof(bufferDescription));
//
//  bufferDescription.Usage = D3D11_USAGE_DEFAULT;
//  bufferDescription.ByteWidth = sizeof(vertices);
//  bufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
//  bufferDescription.CPUAccessFlags = 0;
//
//  // Fill in the subresource data.
//  D3D11_SUBRESOURCE_DATA InitData;
//  ZeroMemory( &InitData, sizeof(InitData) );
//  InitData.pSysMem = vertices;
//
//  // create the buffer
//  (direct3d->device)->CreateBuffer(&bufferDescription, &InitData, &(pVertexBuffer));
//}
//
//VertexBuffer::~VertexBuffer()
//{
//  pVertexBuffer->Release();
//}
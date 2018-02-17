#pragma once

#include <Windows.h>

#include <d3d11.h>
#include <d3dx11.h>
#include <d3d10_1.h>
#include <d3dx10.h>
#include <xnamath.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include <cstdio>

#include <stack>
#include <map>
#include <string>

//#include "RenderNode.h"
//class RenderNode;

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")

#include "Vertex.h"
#include "ConstantBuffer.h"
#include "Mesh.h"
#include "IndexBuffer.h"
#include "ObjLoader.h"
#include "RenderTexture.h"
#include "FullscreenTextureShader.h"
#include "MeshData.h"

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"


class Direct3D
{
public:

  Direct3D(HWND hWnd);
  ~Direct3D();

  void Push(D3DXMATRIX matrix);
  void Pop();
  D3DXMATRIX Top();

  // returns the number of items on the matrix stack
  unsigned int GetMatrixStackSize();

  ID3D11Buffer * LoadVertices(std::string name, VERTEX verticies [], UINT sizeOfVerticies);
  ID3D11Buffer * GetVertices(std::string name);
  IndexBuffer * LoadIndicies(std::string name, UINT16 indicies [], UINT sizeofIndicies);
  IndexBuffer * GetIndicies(std::string name);

  //void LoadMesh(std::string name)
  Mesh * LoadMesh(std::string meshName, std::string objFilepath);
  Mesh * LoadMesh(std::string meshname, ID3D11Buffer * pVertexBuffer, IndexBuffer * pIndexBuffer);
  Mesh * LoadMesh(std::string meshName, /*const */MeshData & meshData);
  Mesh * GetMesh(std::string meshName);
//private: <-- LOLNOPE

  std::map<std::string, Mesh *> meshes;
  std::map<std::string, ID3D11Buffer *> verticies;
  std::map<std::string, IndexBuffer * > indicies;

  D3D_DRIVER_TYPE driverType;
  D3D_FEATURE_LEVEL featureLevel;

  IDXGISwapChain *swapchain; // the pointer to the swap chain interface
  ID3D11Device *device; // the pointer to our Direct3D device interface
  ID3D11DeviceContext *deviceContext; // the pointer to our Direct3D device context
  ID3D11RenderTargetView *backbufferRTV;
  //This is a simple COM object that maintains a location in video memory for you to render into.  In most cases (including our case) this is the back buffer.

  ID3D11Texture2D * pDepthStencil; // Depth Buffer
  ID3D11DepthStencilView * pDepthStencilView; // Thing that tells Direct3D 11
  //ID3D11ShaderResourceView * pDepthSRV;

  RenderTexture * pSceneViewspaceDepth;
  RenderTexture * pSceneDiffuse;

  // for deferred shading
  ID3D11BlendState * pBlendStateAdditive;
  ID3D11BlendState * pBlendStateDefault;

  // to use pDepthStencil as a Depth Stencil texture.

  // SHADERS:
  ID3D11VertexShader *pVertexShader;    // the vertex shader. This is encapsulated into a blob COM object
  ID3D11PixelShader  *pPixelShader;     // the pixel shader.  This is encapsulated into a blob COM object

  FullscreenTextureShader * pFullscreenTextureShader;
  RenderTexture * pSceneNormalMap;
  RenderTexture * pSampleTextureToTestMyShader;

  ID3D11PixelShader * * ppCurrentPixelShader; //TODO: do this better

  ID3D11InputLayout *pLayout; // tells directx how to read our vertex struct

  ID3D11Buffer * pCBChangesEveryFrame; // Constant Buffer

  //TODO: Implement these:
  ID3D11Buffer * pCBChangesOnResize; // Constant Buffer
  ID3D11Buffer * pCBNeverChanges; // Constant Buffer

  void InitD3D(HWND hWnd);
  void InitPipeline();
  void InitGraphics();
  void CleanD3D();

  D3DXMATRIX viewMatrix;
  D3DXMATRIX projMatrix;

  HRESULT CreateRasterizerStates();
  ID3D11RasterizerState * pWireframeRS;
  ID3D11RasterizerState * pSolidRS;
  void DrawSolid();
  void DrawWireframe();

  // Stuff for Texture mapping
  ID3D11ShaderResourceView * ptextureSRV;
  ID3D11SamplerState * pSamplerLinear;

  std::stack<DirectionalLight::WorldspaceDirectionalLight> worldspaceDirectionalLights;
  std::stack<PointLight::WorldspacePointLight> worldspacePointLights;
  std::stack<SpotLight::WorldspaceSpotLight> worldspaceSpotLights;

private:
  std::stack<D3DXMATRIX> matrixStack;
};
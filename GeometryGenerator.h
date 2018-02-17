#pragma once

// source: 3D game programming with directx 11 by Frank Luna, p. 241

#include <wtypes.h>
#include <vector>
#include <stdint.h>

#include "Vertex.h"
#include "MeshData.h"
#include "ErrorMessage.h"

class GeometryGenerator
{
public:

  static void CreateGrid(float width, float depth, UINT m, UINT n, MeshData & meshData);
  static void CreateCube(MeshData & meshData);
  static void CreateFullscreenQuad(MeshData & meshData);
  static void CreateTetrahedron(MeshData & meshData);
  static void CreateSphere(MeshData & meshData, int complexity);
private:
};

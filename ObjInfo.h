#pragma once

#include <iostream>

#include "Vertex.h"
#include "MeshData.h"

class ObjInfo
{
public:

  ObjInfo();
  ~ObjInfo();
  //unsigned int polyCount;

  void Initialize(float x, float y, float z);
  bool IsInitialized();

  float minX, maxX;
  float minY, maxY;
  float minZ, maxZ;
  float GetWidth() const;  //maxX - minX
  float GetHeight() const; //maxY - minY
  float GetDepth() const;  //maxZ - minZ

  void ConsiderVertex(float x, float y, float z);

  friend std::ostream& operator<<(std::ostream& os, const ObjInfo& objInfo);

  MeshData meshData;
/*
  VERTEX * vertexArray;
  unsigned sizeofVertexArray;

  UINT16 * indexArray;
  unsigned sizeofIndexArray;
  */
  unsigned indexCount;

  unsigned triCount;

private:
  // minX, maxX, minY, maxY, minZ, maxZ are initialized to a value
  bool initialized;
};
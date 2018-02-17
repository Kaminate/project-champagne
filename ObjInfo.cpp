#include "ObjInfo.h"

ObjInfo::ObjInfo():
minX(0.0f), maxX(0.0f),
  minY(0.0f), maxY(0.0f),
  minZ(0.0f), maxZ(0.0f),
  initialized(false),
  //vertexArray(NULL),
  //sizeofVertexArray(0),
  //indexArray(NULL),
  //sizeofIndexArray(0),
  indexCount(0),
  triCount(0)
{
  //Giving values a default value, but you should really initialize it
}

ObjInfo::~ObjInfo()
{
  //delete [] vertexArray;
  //delete [] indexArray;
}

bool ObjInfo::IsInitialized()
{
  return initialized;
}

void ObjInfo::Initialize(float x, float y, float z)
{
  if (!initialized)
  {
    minX = x;
    maxX = x;

    minY = y;
    maxY = y;

    minZ = z;
    maxZ = z;
    initialized = true;
  }
}

float ObjInfo::GetDepth() const
{
  return maxZ - minZ;
}

float ObjInfo::GetWidth() const
{
  return maxX - minX;
}

float ObjInfo::GetHeight() const
{
  return maxY - minY;
}

void ObjInfo::ConsiderVertex(float x, float y, float z)
{
  if (x < minX) minX = x;
  else if (x > maxX) maxX = x;

  if (y < minY) minY = y;
  else if (y > maxY) maxY = y;

  if (z < minZ) minZ = z;
  else if (z > maxZ) maxZ = z;
}

//this is a friend function
std::ostream& operator<<(std::ostream& os, const ObjInfo& objInfo)
{
  os << "min x: "  << objInfo.minX << " max x: " << objInfo.maxX << std::endl;
  os << "min y: "  << objInfo.minY << " max y: " << objInfo.maxY << std::endl;
  os << "min z: "  << objInfo.minZ << " max z: " << objInfo.maxZ << std::endl;
  os << "Width : " << objInfo.GetWidth()  << std::endl;
  os << "Height: " << objInfo.GetHeight() << std::endl;
  os << "Depth: "  << objInfo.GetDepth()  << std::endl;
  return os;
}
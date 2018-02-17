#pragma once

//dumping #includes
#include <stdio.h>

#include "Vertex.h"

//Including vertex data for 2 reasons:
// 1. We probably need it
// 2. I think we need it for our templated cout for vectors
#include "VertexPosition.h"
#include "VertexNormal.h"
#include "VertexTexture.h"
//#include "Face.h"

#include "Cout_for_DirectX.h"

#include <string>
#include <vector>
#include <string>
#include <iostream>
#include <istream>
#include <fstream>
#include <d3dx10math.h>

template <typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> & objects);

//Contains a line in the .obj file
class ObjLineReader
{
public:
  ObjLineReader();
  ~ObjLineReader();

  std::string line;
  std::ifstream * objFile;

  char DetermineLineType();
  bool ReadObjLine(); // true if read successfully, false if eof
  bool OpenObjFile(std::string objFilePath);

  unsigned int linesRead;

private:
};

//Templated cout for vectors of objects
template <typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> & objects)
{
  unsigned int count = 1;
  for (auto it = objects.begin(); it != objects.end(); ++it)
  {
    os << count << ": " << *it << std::endl;
    ++count;
  }

  return os;
}

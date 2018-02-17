#pragma once

#include <stdio.h>
#include <string>
#include <vector>
#include <string>
#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>

#include "Vertex.h"
#include "ObjLineReader.h"
#include "Cout_for_DirectX.h"
#include "ObjInfo.h"
#include "VertexIndicies.h"

class ObjLoader
{
public:
  static ObjInfo * LoadObjIntoArray(std::string objFilePath);

private:
};

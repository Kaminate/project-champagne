#include "ObjLoader.h"
#include "ErrorMessage.h"

// algorithm
ObjInfo * ObjLoader::LoadObjIntoArray(std::string objFilePath)
{
  ObjLineReader objLineReader;
  ObjInfo * objInfo = new ObjInfo;

  if (objLineReader.OpenObjFile(objFilePath) == false)
  {
    ErrorMessage("Could not find file!");
  }

  std::vector<VertexPosition> * vertexPositions = new std::vector<VertexPosition>;
  std::vector<VertexTexture> * vertexTextures = new std::vector<VertexTexture>;
  std::vector<VertexNormal> * vertexNormals = new std::vector<VertexNormal>;
  std::vector<VERTEX> * verticies = &objInfo->meshData.verticies;//new std::vector<VERTEX>;

  //std::vector<Face> * faces = new std::vector<Face>;

  while (objLineReader.ReadObjLine())
  {
    //for debugging:
    //std::cout << "Line # " << objLineReader.linesRead << ": ";
    //std::cout << objLineReader.line << std::endl;
    /*if (objLineReader.linesRead == 1365 ||
    objLineReader.linesRead == 1600 ||
    objLineReader.linesRead == 1900 ||
    objLineReader.linesRead == 2100 ||
    objLineReader.linesRead == 2387 )
    {
    int i = 0; ++i;
    }*/
    std::stringstream ss(std::stringstream::in | std::stringstream::out);

    // The tag is the identifier at the beginning of line in the obj file
    std::string tag;

    ss << objLineReader.line;

    ss >> tag;

    if (tag.empty())
    {
      // nothing in that line. Do nothing.
    }
    else if (tag == "#")
    {
      // It's a comment. Do nothing
      // Ex: # this is a comment
    }
    else if (tag == "mtllib")
    {
      // The obj file uses this MTL material file.
      // Note 1: More than one external MTL material file may be referenced from
      //       within the OBJ file.
      // Note 2: The .mtl file may contain one or more named material definitions.
      // Ex: mtllib [external .mtl file name]

      // TODO: Add the string name of the MTL material to a list
    }
    else if (tag == "v")
    {
      // It's a vertex position!
      // Create a VertexPosition class and add it to our vector
      float x, y, z;
      ss >> x;
      ss >> y;
      ss >> z;
      VertexPosition vertexPosition(x,y,z);
      vertexPositions->push_back(vertexPosition);

      // Compare obj info
      if (!objInfo->IsInitialized())
      {
        // sets default minx, maxx,... values to compare to
        objInfo->Initialize(x, y, z);
      }
      else
      {
        objInfo->ConsiderVertex(x, y, z);
      }
    }
    else if (tag == "vn")
    {
      // It's a vertex normal!
      // Create a VertexNormal class and add it to our vector
      float x, y, z;
      ss >> x;
      ss >> y;
      ss >> z;
      VertexNormal vertexNormal(x,y,z);
      vertexNormals->push_back(vertexNormal);
    }
    else if (tag == "vt")
    {
      // It's a vertex texture coordinate!
      // Create a VertexTexture class and add it to our vector
      float u, v;
      ss >> u;
      ss >> v;
      VertexTexture vertexTexture(u, v);
      vertexTextures->push_back(vertexTexture);
    }
    else if (tag == "usemtl")
    {
      // This tag specifies the material name for the element following it.
      // The material name matches a named material definition in an external .mtl file.
      // Ex: usemtl [material name]

      //TODO: this
    }
    else if (tag == "o" || tag == "g" || tag == "s" )
      // TODO: these other things.
    {
      //       o [object name]
      //       ...
      //         g [group name]
      //       ...
      //
      //         Smooth shading across polygons is enabled by smoothing groups.
      //
      //         s 1
      //         ...
      // # Smooth shading can be disabled as well.
      //         s off
      //         ...

      // TODO: all this
    }
    else if (tag == "f")
    {
      // There are 4 types of faces
      // 1. Face:                     f v1 v2 ... vn
      // 2. Face with texture coords: f v1/t1 v2/t2 .... vn/tn
      // 3. Face with vertex normals: f v1//n1 v2//n2 .... vn//nn
      // 4. Face with txt and norms:  f v1/t1/n1 v2/t2/n2 .... vn/tn/nn

      // It's a face!
      // Create a Face class and add it to our vector

      // TODO: make the face work with all face types
      // For now, we will ASSUME our face is face type 4: face with tx and norms

      //Face face;
      //face.faceType = Face::verticies_uvs_normals;

      // contains information about each vertex in a face
      //std::vector<VertexIndicies> * vertexIndiciesList = new std::vector<VertexIndicies>;

      // corresponds to the verticies in a single face
      //std::vector<unsigned> * indexIndiciesList = new std::vector<unsigned>;

      //unsigned indexCount = 0;

      // Must be outside the do while loop because it's used for the condition
      std::string vertexString;
      do
      {
        vertexString.clear();
        ss >> vertexString; // now vertex is something like 2/4/3

        //Break if at the end
        if (vertexString == "") break;

        //replace the '/' with spaces
        for (std::string::iterator it = vertexString.begin(); it != vertexString.end(); ++it)
        {
          if (*it == '/')
          {
            *it = ' ';
          }
        }

        std::stringstream ss2(vertexString);

        VertexIndicies vertexIndicies;
        ss2 >> vertexIndicies;

        VERTEX tempVertex = vertexIndicies.BuildVertex(vertexPositions, vertexTextures, vertexNormals);
        verticies->push_back(tempVertex);

        //verticies->push_back(vertexIndicies.BuildVertex(vertexPositions, vertexTextures, vertexNormals));

        //// loop through each of the verticies in vertexIndiciesList
        //// to look for a duplicate

        //unsigned pastIndicies = 0; //index of the current vertex in vertexIndiciesList
        ////                    in the below loop
        //unsigned currentIndex; // index of our new vertex
        //for (auto it = *vertexIndiciesList->begin(); it != *vertexIndiciesList->end(); ++it)
        //{
        //  if (*it == vertexIndicies) //duplicate vertex
        //  {
        //  }
        //}

        //vertexIndiciesList->push_back(vertexIndiciesList);

        // VERTEX vertex;
        // std::cout << vertex;
      } while (!vertexString.empty());

      //float u, v;
      //ss >> u;
      //ss >> v;
      //VertexTexture vertexTexture(u, v);
      //vertexTextures->push_back(vertexTexture);
    }
  }

  //std::cout << "Veretx Positions: " << std::endl << *vertexPositions << std::endl;
  //std::cout << "Vertex Normals: "   << std::endl << *vertexNormals   << std::endl;
  //std::cout << "Vertex Textures: "  << std::endl << *vertexTextures  << std::endl;

  //std::cout << "Verticies: " << std::endl;
  //std::cout << *verticies    << std::endl;

#ifdef _DEBUG
  std::cout << *objInfo << std::endl;
#endif

  unsigned verticiesCount = verticies->size();
  unsigned trianglesCount = verticiesCount / 3;
  /*
  // Fill out parameters passed into this function
  objInfo->sizeofVertexArray = sizeof(VERTEX) * verticiesCount;

  // Allocate the vertex array
  objInfo->vertexArray = new VERTEX[verticiesCount];

  for (unsigned i = 0; i < verticiesCount; ++i)
  {
    objInfo->vertexArray[i] = (*verticies)[i];
  }
  */
  delete vertexPositions;
  delete vertexTextures;
  delete vertexNormals;
  //delete verticies;

  objInfo->indexCount = verticiesCount;
  /*
  //allocate the index array
  objInfo->indexArray = new UINT16[objInfo->indexCount];
  for (unsigned i = 0; i < objInfo->indexCount; ++i)
  {
    objInfo->indexArray[i] = i;
  }

  objInfo->sizeofIndexArray = objInfo->indexCount * sizeof(UINT16);
  //sizeofIndexArray = indexCount * sizeof(indexArray[0]);
  */
  for (unsigned i = 0; i < objInfo->indexCount; ++i)
  {
    objInfo->meshData.indicies.push_back(i);//[i] = i;
  }

  objInfo->triCount = verticiesCount / 3;

  return objInfo;
}
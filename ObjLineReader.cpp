#include "ObjLineReader.h"

ObjLineReader::ObjLineReader():
  line(),
  objFile(new std::ifstream),
  linesRead(0u)
{
}

ObjLineReader::~ObjLineReader()
{
  if (this->objFile->is_open())
  {
    this->objFile->close();
  }

  delete objFile;
}

char ObjLineReader::DetermineLineType()
{
  return 'a';
}

bool ObjLineReader::ReadObjLine()
{
  if (objFile->good() == false)
  {
    return false;
  }
  else
  {
    ++linesRead;
    std::getline(*objFile, this->line);
    return true;
  }
}

bool ObjLineReader::OpenObjFile(std::string objFilePath)
{
  objFile->open(objFilePath);

  return objFile->is_open();
}
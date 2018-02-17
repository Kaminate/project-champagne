/* Start Header -------------------------------------------------------
Copyright (C) 2012 DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name: System.cpp
Purpose: System handler. Also contains the output function.
Language: c++, VS2010 compiler
Platform: <specify compiler version, hardware requirements, operating systems>
Project: CS230_nathan.p_1
Author: Nathan Park, nathan.p, 50005211
Creation date: 1/28/2012
- End Header --------------------------------------------------------*/

#include "System.h"
#include <stdio.h> // FILE, fopen, fprintf
#include <assert.h>

FILE * file;

void System_Initialize()
{
  //delete file
  remove("Output.txt");

  //create file
  file = fopen("Output.txt", "at");
  assert(file);

  //We can only output to a file after we've created it!
  Output("System:Initialize");
}

void System_Exit()
{
  OutputNoNewline("System:Exit");
  fclose(file);
}

void Output(char text [])
{
  //printf("%s\n",text);  // Print to console
  fprintf(file, "%s\n", text); // Print to file
}

void OutputNoNewline(char text [])
{
  //printf("%s\n",text);  // Print to console
  fprintf(file, "%s", text); // Print to file
}
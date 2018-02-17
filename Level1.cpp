/* Start Header -------------------------------------------------------
Copyright (C) 2012 DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name: Level1.cpp
Purpose: Level 1 data.
Language: c++, VS2010 compiler
Platform: <specify compiler version, hardware requirements, operating systems>
Project: CS230_nathan.p_1
Author: Nathan Park, nathan.p, 50005211
Creation date: 1/28/2012
- End Header --------------------------------------------------------*/

#include "GameStateList.h" // Level2
#include "GameStateManager.h" //SetNextLevel
#include <stdio.h> // File
#include "System.h" // Output
#include <assert.h> //assert
#include "Level1.h"

int Level1_Counter;
static FILE * file;

void Level1_Load()
{
  Output("Level1:Load");

  file = fopen("Level1_Counter.txt", "rt");

  if (file == 0)
  {
    //hi
  }

  assert(file);
}

void Level1_Initialize()
{
  Output("Level1:Initialize");

  fscanf(file, "%i", &Level1_Counter);
}

void Level1_Update()
{
  Output("Level1:Update");

  //Decremented Level1_Counter
  --Level1_Counter;

  //Switch to Level2
  if (Level1_Counter == 0)
  {
    SetNextState(Level2);
  }

  Level1_Draw();
}

void Level1_Draw()
{
  Output("Level1:Draw");
}

void Level1_Free()
{
  Output("Level1:Free");
}

void Level1_Unload()
{
  Output("Level1:Unload");

  fclose(file);
}
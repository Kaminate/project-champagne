/* Start Header -------------------------------------------------------
Copyright (C) 2012 DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name: Level2.cpp
Purpose: Level 2 data.
Language: c++, VS2010 compiler
Platform: <specify compiler version, hardware requirements, operating systems>
Project: CS230_nathan.p_1
Author: Nathan Park, nathan.p, 50005211
Creation date: 1/28/2012
- End Header --------------------------------------------------------*/

#include "GameStateList.h" // Quit, Restart
#include "GameStateManager.h" //SetNextState
#include <stdio.h> // File
#include "System.h" // Output
#include <assert.h> //assert
#include "Level2.h"

FILE * fileCounter;
FILE * fileLives;

int Level2_Counter;
int Level2_Lives;

void Level2_Load()
{
  Output("Level2:Load");

  fileCounter = fopen("Level2_Counter.txt","rt");

  assert(fileCounter);

  fileLives = fopen("Level2_Lives.txt","rt");

  assert(fileLives);

  fscanf(fileLives, "%i", &Level2_Lives);
}

void Level2_Initialize()
{
  Output("Level2:Initialize");

  //Reset the file pointer
  rewind(fileCounter);
  fscanf(fileCounter, "%i", &Level2_Counter);
}

void Level2_Update()
{
  Output("Level2:Update");

  // Decrement Level2_Counter
  --Level2_Counter;

  // When our counter runs out
  if (Level2_Counter == 0)
  {
    //Decrement our lives.
    --Level2_Lives;

    //Restart per default, but...
    SetNextState(Restart);

    //If we run out of lives, quit.
    if (Level2_Lives == 0)
    {
      SetNextState(Quit);
    }
  }

  Level2_Draw();
}

void Level2_Draw()
{
  Output("Level2:Draw");
}
void Level2_Free()
{
  Output("Level2:Free");
}

void Level2_Unload()
{
  Output("Level2:Unload");
  fclose(fileCounter);
  fclose(fileLives);
}
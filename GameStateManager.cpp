/* Start Header -------------------------------------------------------
Copyright (C) 2012 DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name: GameStateManager.cpp
Purpose: Game state handler. Inits game state and assigns function pointers.
Language: c++, VS2010 compiler
Platform: <specify compiler version, hardware requirements, operating systems>
Project: CS230_nathan.p_1
Author: Nathan Park, nathan.p, 50005211
Creation date: 1/28/2012
- End Header --------------------------------------------------------*/

#include "GameStateList.h" // GameState
#include "System.h" // Output

#include "Level1.h" //Level1 functions
#include "Level2.h" //Level2 functions

//The 6 function pointers and the 3 state indicators belong to the game state manager. You can put them as global variables in the game state manager .c/.cpp file.
void (*load) (void);
void (*initialize) (void);
void (*update) (void);
void (*draw) (void);
void (*free) (void);
void (*unload) (void);

GameState PreviousState;
GameState CurrentState;
GameState NextState;

void Load()       {load();}

void Initialize() {initialize();}

void Update()     {update();}

void Draw()       {draw();}

void Free()       {free();}

void Unload()     {unload();}

GameState GetNextState(void) {return NextState;}

void SetNextState(GameState nextState) {NextState = nextState;}

GameState GetCurrentState(void) {return CurrentState;}

void SetCurrentState(GameState currentState) {CurrentState = currentState;}

GameState GetPreviousState(void) {return NextState;}

void SetPreviousState(GameState previousState) {PreviousState = previousState;}

//Sets the previous, current and next indicators to the same value
void GSM_Initialize(GameState initialState)
{
  Output("GSM:Initialize");

  PreviousState = initialState;
  CurrentState = initialState;
  NextState = initialState;
}

//“GSM_Update”: Sets the 6 functions pointers to the currently selected state. The game state manager initialization function should append “GSM:Update” to “Output.txt”
void GSM_Update()
{
  if (NextState != Restart)
  {
    //NOTE: THIS IF CHECK IS ONLY HERE TO MAKE OUR OUTPUT MATCH THE EXAMPLE'S
    Output("GSM:Update");
  }

  // Assign Function pointers based on the next state
  switch (NextState)
  {
  case Restart:
    // do no need to switch function pointers
    break;
  case Level1:
    load       = Level1_Load;
    initialize = Level1_Initialize;
    update     = Level1_Update;
    draw       = Level1_Draw;
    free       = Level1_Free;
    unload     = Level1_Unload;
    break;
  case Level2:
    load       = Level2_Load;
    initialize = Level2_Initialize;
    update     = Level2_Update;
    draw       = Level2_Draw;
    free       = Level2_Free;
    unload     = Level2_Unload;
    break;
  }
}
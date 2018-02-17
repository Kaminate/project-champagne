#ifndef GameStateManager_h__
#define GameStateManager_h__

/* Start Header -------------------------------------------------------
Copyright (C) 2012 DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name: GameStateManager.h
Purpose: Prototypes of functions in GameStateManager.cpp
Language: c++, VS2010 compiler
Platform: <specify compiler version, hardware requirements, operating systems>
Project: CS230_nathan.p_1
Author: Nathan Park, nathan.p, 50005211
Creation date: 1/28/2012
- End Header --------------------------------------------------------*/

#include "GameStateList.h" // GameState

//prototypes
void Load();
void Initialize();
void Update();
void Draw();
void Free();
void Unload();

GameState GetNextState(void);
void SetNextState(GameState nextState);

GameState GetCurrentState(void);
void SetCurrentState(GameState currentState);

GameState GetPreviousState(void);
void SetPreviousState(GameState previousState);

void GSM_Initialize(GameState initialState);

void GSM_Update();
#endif // GameStateManager_h__
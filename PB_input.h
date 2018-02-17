/******************************************************************************/
/*
 @file     PB_input.h
 @project  Photon Bunny
 @author   Justin Cook

 All content (c) 2012 DigiPen (USA) Corporation, all rights reserved.
 */
/******************************************************************************/

#ifndef PB_INPUT_H
#define PB_INPUT_H

#include <stdlib.h>
#include <Windows.h>
#include <XInput.h>

typedef enum Key
{
  KEY_A = 65,
  KEY_B,
  KEY_C,
  KEY_D,
  KEY_E,
  KEY_F,
  KEY_G,
  KEY_H,
  KEY_I,
  KEY_J,
  KEY_K,
  KEY_L,
  KEY_M,
  KEY_N,
  KEY_O,
  KEY_P,
  KEY_Q,
  KEY_R,
  KEY_S,
  KEY_T,
  KEY_U,
  KEY_V,
  KEY_W,
  KEY_X,
  KEY_Y,
  KEY_Z,
  KEY_ENTER = 13,
  KEY_SHIFT = 16,
  KEY_CAPS_LOCK = 20,
  KEY_ESCAPE = 27,
  KEY_SPACE = 32,
  KEY_LEFT = 37,
  KEY_UP,
  KEY_RIGHT,
  KEY_DOWN,
  KEY_BACKSPACE = 8,
  KEY_TAB,
  KEY_DEL = 46,
  MOUSE_LEFT = 1,
  MOUSE_RIGHT,
  MOUSE_MIDDLE = 4,
  KEY_NUM_0 = 48,
  KEY_NUM_1,
  KEY_NUM_2,
  KEY_NUM_3,
  KEY_NUM_4,
  KEY_NUM_5,
  KEY_NUM_6,
  KEY_NUM_7,
  KEY_NUM_8,
  KEY_NUM_9,
  KEY_NUMPAD_0 = 96,
  KEY_NUMPAD_1,
  KEY_NUMPAD_2,
  KEY_NUMPAD_3,
  KEY_NUMPAD_4,
  KEY_NUMPAD_5,
  KEY_NUMPAD_6,
  KEY_NUMPAD_7,
  KEY_NUMPAD_8,
  KEY_NUMPAD_9
}Key;

typedef struct g_Controller
{
  XINPUT_STATE state;
  int isConnected;
  float magnitude;
  float normalizedMagnitude;
}g_Controller;

LRESULT WINAPI inputMessageHandler(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

void initKeyStatus(void);

/* true for all frames key is down */
unsigned int keyIsDown(const enum Key key);

/* true for 1 frame key is down */
unsigned int keyIsTriggered(const enum Key key);

/* true for 1 frame after key is released */
unsigned int keyIsReleased(const enum Key key);

unsigned int buttonIsPressed(unsigned int button);

unsigned int buttonIsDown(unsigned int button);

unsigned int buttonIsReleased(unsigned int button);

void preUpdateKeyStatus(float dt);
void postUpdateKeyStatus(float dt);
void updateControllerStatus(void);

void getControllerState(g_Controller* controller);

void controllerUpdate(g_Controller* controller);

g_Controller* g_Controller_new(void);

g_Controller* getController(void);

/* call this function at the end of each frame (not at the beginning) */
//void updateKeyStatus(float dt);

#endif
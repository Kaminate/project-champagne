/******************************************************************************/
/*
 @file     PB_input.c
 @project  Photon Bunny
 @author   Justin Cook
 @author   Allen Chou

 All content (c) 2012 DigiPen (USA) Corporation, all rights reserved.
 */
/******************************************************************************/

#include "PB_input.h"
#include <math.h>

#pragma comment(lib, "Xinput.lib")

g_Controller* global_Controller;

static unsigned int downState_[256] = {0};
static unsigned int prevDownState_[256] = {0};
static g_Controller xbox;
static unsigned int A_Pressed = 0;
static unsigned int X_Pressed = 0;
static unsigned int B_Pressed = 0;
static unsigned int A_prevPressed = 0;
static unsigned int X_prevPressed = 0;
static unsigned int B_prevPressed = 0;
static unsigned int Dpad_Down_Pressed = 0;
static unsigned int Dpad_Left_Pressed = 0;
static unsigned int Dpad_Right_Pressed = 0;
static unsigned int Dpad_Up_Pressed = 0;
static unsigned int Dpad_Down_prevPressed = 0;
static unsigned int Dpad_Left_prevPressed = 0;
static unsigned int Dpad_Right_prevPressed = 0;
static unsigned int Dpad_Up_prevPressed = 0;
static unsigned int START_pressed = 0;
static unsigned int BACK_pressed = 0;
static unsigned int START_prevPressed = 0;
static unsigned int BACK_prevPressed = 0;

static void wmKeyDown(unsigned int keyCode)
{
  downState_[keyCode] = 1;
}

static void wmKeyUp(unsigned int keyCode)
{
  downState_[keyCode] = 0;
}

LRESULT WINAPI inputMessageHandler(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
  //Alphe Engine does not give us mouse input detection, which is stupid
  switch(msg)
  {
  case WM_CREATE:
    SendMessage(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)LoadImage(NULL, "images/icon/Photon Bunny.ico", IMAGE_ICON, 16, 16, LR_LOADFROMFILE) );
    SendMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM)LoadImage(NULL, "images/icon/Photon Bunny.ico", IMAGE_ICON, 64, 64, LR_LOADFROMFILE) );
    break;
  case WM_KEYDOWN:
    wmKeyDown(wp);
    break;

  case WM_KEYUP:
    wmKeyUp(wp);
    break;

  case WM_CLOSE:
    exit(0);
    break;

  default:
//    return DefWindowProc(hWnd, msg, wp, lp);
    break;
  }

  return 0;
}

void initKeyStatus(void)
{
  int i;
  for (i = 0; i < 256; ++i)
  {
    downState_[i] = 0;
    prevDownState_[i] = 0;
  }
}

unsigned int keyIsDown(const enum Key key)
{
  return downState_[key];
}

unsigned int keyIsTriggered(const enum Key key)
{
  return downState_[key] && !prevDownState_[key];
}

unsigned int keyIsReleased(const enum Key key)
{
  return !downState_[key] && prevDownState_[key];
}

void preUpdateKeyStatus(float dt)
{
  downState_[MOUSE_LEFT] = GetAsyncKeyState(MOUSE_LEFT);
  downState_[MOUSE_RIGHT] = GetAsyncKeyState(MOUSE_RIGHT);
}

void postUpdateKeyStatus(float dt)
{
  int i;
  for (i = 0; i < 256; ++i) prevDownState_[i] = downState_[i];

  updateControllerStatus();
}

void getControllerState(g_Controller* controller)
{
  DWORD dwResult;
  DWORD i = 0;

  for(i = 0; i < 1; i++)
  {
    XINPUT_STATE state;

    ZeroMemory(&state, sizeof(XINPUT_STATE));

    dwResult = XInputGetState(i, &state);

    if(dwResult == ERROR_SUCCESS)
    {
      controller->isConnected = 1;
      controller->state = state;
      controllerUpdate(controller);

      xbox.state = state;
    }
    else
    {
      controller->isConnected = 0;
      controller->state = state;
    }
  }
}

void controllerUpdate(g_Controller* controller)
{
  XINPUT_STATE state = controller->state;

  float LX = state.Gamepad.sThumbLX;
  float LY = state.Gamepad.sThumbLY;

  //get the distance the controller is pressed
  float magnitude = (float)sqrt(LX * LX + LY * LY);

  float normalizedLX = LX / magnitude;
  float normalizedLY = LY / magnitude;

  float normalizeMagnitude = 0.0f;

  if(magnitude > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
  {
    if(magnitude > 32767) magnitude = 32767;

    magnitude -= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;

    normalizeMagnitude = magnitude / (32767 - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
  }
  else
  {
    magnitude = 0.0;
    normalizeMagnitude = 0.0;
  }

  controller->normalizedMagnitude = normalizeMagnitude;
  controller->magnitude = magnitude;
}

g_Controller* g_Controller_new(void)
{
  g_Controller* controller = (g_Controller*) malloc(sizeof(g_Controller));

  controller->isConnected = 0;
  controller->magnitude = 1.0f;
  controller->normalizedMagnitude = 0;
  controller->state.dwPacketNumber = 0;
  controller->state.Gamepad.bLeftTrigger = 0;
  controller->state.Gamepad.bRightTrigger = 0;
  controller->state.Gamepad.sThumbLX = 0;
  controller->state.Gamepad.sThumbLY = 0;
  controller->state.Gamepad.sThumbRX = 0;
  controller->state.Gamepad.sThumbRY = 0;
  controller->state.Gamepad.wButtons = 0;

  return controller;
}

void updateControllerStatus(void)
{
  A_prevPressed = A_Pressed;
  X_prevPressed = X_Pressed;
  B_prevPressed = B_Pressed;
  Dpad_Down_prevPressed = Dpad_Down_Pressed;
  Dpad_Left_prevPressed = Dpad_Left_Pressed;
  Dpad_Right_prevPressed = Dpad_Right_Pressed;
  Dpad_Up_prevPressed = Dpad_Up_Pressed;
  START_prevPressed = START_pressed;
  BACK_prevPressed = BACK_pressed;

  if(xbox.state.Gamepad.wButtons & XINPUT_GAMEPAD_A) A_Pressed = 1;

  if(xbox.state.Gamepad.wButtons & XINPUT_GAMEPAD_X) X_Pressed = 1;

  if(xbox.state.Gamepad.wButtons & XINPUT_GAMEPAD_B) B_Pressed = 1;

  if(xbox.state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) Dpad_Down_Pressed = 1;

  if(xbox.state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) Dpad_Left_Pressed = 1;

  if(xbox.state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) Dpad_Right_Pressed = 1;

  if(xbox.state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) Dpad_Up_Pressed = 1;

  if((xbox.state.Gamepad.wButtons & XINPUT_GAMEPAD_START)) START_pressed = 1;

  if((xbox.state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK)) BACK_pressed = 1;

  if(!(xbox.state.Gamepad.wButtons & XINPUT_GAMEPAD_A)) A_Pressed = 0;

  if(!(xbox.state.Gamepad.wButtons & XINPUT_GAMEPAD_X)) X_Pressed = 0;

  if(!(xbox.state.Gamepad.wButtons & XINPUT_GAMEPAD_B)) B_Pressed = 0;

  if(!(xbox.state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)) Dpad_Down_Pressed = 0;

  if(!(xbox.state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)) Dpad_Left_Pressed = 0;

  if(!(xbox.state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)) Dpad_Right_Pressed = 0;

  if(!(xbox.state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)) Dpad_Up_Pressed = 0;

  if(!(xbox.state.Gamepad.wButtons & XINPUT_GAMEPAD_START)) START_pressed = 0;

  if(!(xbox.state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK)) BACK_pressed = 0;
}

unsigned int buttonIsPressed(unsigned int button)
{
  if(button == 'A')
    return  A_Pressed && !A_prevPressed;

  if(button == 'X')
    return X_Pressed && !X_prevPressed;

  if(button == 'B')
    return B_Pressed && !B_prevPressed;

  if (button == 'DD')
    return Dpad_Down_Pressed && !Dpad_Down_prevPressed;

  if (button == 'DL')
    return Dpad_Left_Pressed && !Dpad_Left_prevPressed;

  if (button == 'DR')
    return Dpad_Right_Pressed && !Dpad_Right_prevPressed;

  if (button == 'DU')
    return Dpad_Up_Pressed && !Dpad_Up_prevPressed;

  if (button == 'ST')
    return START_pressed && !START_prevPressed;

  if (button == 'BA')
    return BACK_pressed && !BACK_prevPressed;

  return 0;
}

unsigned int buttonIsDown(unsigned int button)
{
  if(button == 'A') return A_Pressed;

  if(button == 'X') return X_Pressed;

  if(button == 'B') return B_Pressed;

  if (button == 'DD') return Dpad_Down_Pressed;

  if (button == 'DL') return Dpad_Left_Pressed;

  if (button == 'DR') return Dpad_Right_Pressed;

  if (button == 'DU') return Dpad_Up_Pressed;

  if (button == 'ST') return START_pressed;

  if (button == 'BA') return BACK_pressed;

  return 0;
}

unsigned int buttonIsReleased(unsigned int button)
{
  if(button == 'A') return !A_Pressed && A_prevPressed;

  if(button == 'X') return !X_Pressed && X_prevPressed;

  if(button == 'B') return !B_Pressed && B_prevPressed;

  if (button == 'DD')
    return !Dpad_Down_Pressed && Dpad_Down_prevPressed;

  if (button == 'DL')
    return !Dpad_Left_Pressed && Dpad_Left_prevPressed;

  if (button == 'DR')
    return !Dpad_Right_Pressed && Dpad_Right_prevPressed;

  if (button == 'DU')
    return !Dpad_Up_Pressed && Dpad_Up_prevPressed;

  if (button == 'ST')
    return !START_pressed && START_prevPressed;

  if (button == 'BA')
    return !BACK_pressed && BACK_prevPressed;

  return 0;
}

g_Controller* getController(void)
{
  if(global_Controller == NULL)
  {
    global_Controller = g_Controller_new();
  }

  return global_Controller;
}

/*
void updateKeyStatus(float dt)
{
  int i;
  for (i = 0; i < 256; ++i) prevDownState_[i] = downState_[i];
}
*/
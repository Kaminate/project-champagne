#ifndef System_h__
#define System_h__

/* Start Header -------------------------------------------------------
Copyright (C) 2012 DigiPen Institute of Technology. Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name: System.h
Purpose: Prototypes of functions in System.cpp
Language: c++, VS2010 compiler
Platform: <specify compiler version, hardware requirements, operating systems>
Project: CS230_nathan.p_1
Author: Nathan Park, nathan.p, 50005211
Creation date: 1/28/2012
- End Header --------------------------------------------------------*/

// Prototypes
void System_Initialize();
void System_Exit();
void Output(char * text);
void OutputNoNewline(char text []);
#endif // System_h__
/******************************************************************************/
/*
 @file     PB_time.c
 @project  Photon Bunny
 @author   Nathan Park

 All content (c) 2012 DigiPen (USA) Corporation, all rights reserved.
 */
/******************************************************************************/

#include "PB_time.h"
#include <time.h> // clock

//returns time in seconds since program was launched
float GetTime()
{
	float myClock;

	//clock return no of ticks since program started
	myClock = (float) clock();
	return (float) (myClock / CLOCKS_PER_SEC);
}
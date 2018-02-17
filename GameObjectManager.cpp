// keep a list of all game objects in a linked list.
// updates them all
//
// Anatomy of a game object:
// -graphipcs
// -physics
// -TRANSFORM

// what the update of a game object does
// -sets the transform of the graphics equal to the TRANSFORM
// -note: the phsyics uses the TRANSFORM (it doesn't have it's own)
// -note2: all rigidBodies have GLOBAL COORDINATES)

#include "GameObjectManager.h"

GameObjectManager::GameObjectManager():
  MAX_OBJECTS(2000),
  gameObjectList(new GameObject[MAX_OBJECTS]),
  numObjects(0)
{
}

GameObjectManager::~GameObjectManager()
{
  delete [] gameObjectList;
}
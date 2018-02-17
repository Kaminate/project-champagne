#pragma once
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
#include <list>
#include "ModelNode.h"
#include "GameObject.h"

class GameObject;

class GameObjectManager
{
public:
  GameObjectManager();
  ~GameObjectManager();

  const unsigned int MAX_OBJECTS; //note : max_objects must be declared b4 game objcet list
  GameObject * gameObjectList;
  unsigned int numObjects;

  //GameObject * CreateGameObject
  //std::list<GameObject> gameObjectList;
  //GameObject gameObjectList[MAX_OBJECTS];

//private:
};
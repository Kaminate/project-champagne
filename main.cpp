#include <windows.h>

#include <d3d11.h>
#include <d3dx11.h>
#include <d3d10_1.h>
#include <d3dx10.h>
#include <xnamath.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include <cstdio>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dx10.lib")

#include "PB_input.h"
#include "PB_time.h"
#include "camera.h"
#include "guicon.h"
#include "graphics.h"
#include "ModelNode.h"
#include "Direct3D.h"
#include "Vertex.h"
#include "GameObjectManager.h"
#include "GameObject.h"
#include "PhysicsWorld.h"
#include "RigidBody.h"
#include "Sound.h"
#include "ErrorMessage.h"
#include "PartyLight.h"
#include "GeometryGenerator.h"
#include "VectorMath.h"
#include "tempGlobals.h"
#include "PointLightNode.h"
#include "PointLight.h"

#include <AntTweakBar.h>

// global declarations
HWND g_hWnd;

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

bool party = false;

// List of missiles
const unsigned int MAX_MISSILES = 1000;
ModelNode* missileList [MAX_MISSILES];
unsigned int numMissiles = 0;


FMOD::Channel * g_channel;

//  windows prototypes
HRESULT InitWindow( HINSTANCE hInstance, int nCmdShow );
LRESULT CALLBACK WndProc (HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

// console prototypes
void ConsoleStuff();

//See if missile colliding with disco ball
bool IsOverlapping(
  const D3DXVECTOR3 & discoBallPos,
  const float  discoBallHalfWidth,
  const D3DXVECTOR3 & missilePos,
  const float missileHalfWidth)
{
  //D3DXVECTOR3 difference = discoBallPos - missilePos;

  //float distance = D3DXVec3Length(&difference);
  float distanceX, distanceY, distanceZ;
  distanceX = abs(discoBallPos.x - missilePos.x);
  distanceY = abs(discoBallPos.y - missilePos.y);
  distanceZ = abs(discoBallPos.z - missilePos.z);

  float combinedWidths = discoBallHalfWidth + missileHalfWidth;

  if (distanceX >= combinedWidths) return false;
  if (distanceY >= combinedWidths) return false;
  if (distanceZ >= combinedWidths) return false;

  return true;
}

// This is the entry point for the application
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
  InitWindow(hInstance, nCmdShow);

  ConsoleStuff();

  // Create graphics and direct3d
  Graphics graphics(SCREEN_WIDTH, SCREEN_HEIGHT, g_hWnd);

  ///////////////////
  // ANT TWEAK BAR // anttweakbar
  ///////////////////
  TwInit(TW_DIRECT3D11, graphics.direct3d.device); // for Direct3D 11
  TwWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
  TwBar * myBar = TwNewBar("Leif Tweak Bar");
  INT16 myVar = 5;
  TwAddVarRW(myBar, "Swag", TW_TYPE_INT16, &myVar, "min = 0 max = 10");
  
  SoundSystem * soundSystem = new SoundSystem;
  FMOD::Sound * sound;
  FMOD_RESULT result;
  // FMOD_DEFAULT uses the defaults.  These are the same as FMOD_LOOP_OFF | FMOD_2D | FMOD_HARDWARE.
  //result = soundSystem->system->createStream("Resources/Sounds/cannon fire.wav", FMOD_DEFAULT, 0, &sound);
  //result = soundSystem->system->createStream("Resources/Sounds/cannon fire.wav", FMOD_CREATESAMPLE, 0, &sound);
  result = soundSystem->system->createSound("Resources/Sounds/cannon fire.wav", FMOD_CREATESAMPLE, 0, &sound);
  //result = soundSystem->system->createStream("Resources/Sounds/cannon fire.wav", FMOD_DEFAULT, 0, &sound);
  if (result != FMOD_OK)
  {
    ErrorMessage("Fmod failed to create stream!");
    std::cout << result << FMOD_ErrorString(result);
    return -1;
  }

  //FMOD::Channel * channel;
  FMOD::Sound * partyMusic;
  //not error checking this one
  soundSystem->system->createStream("Resources/Sounds/When I'm Bored.mp3", FMOD_DEFAULT, 0, &partyMusic);

  PhysicsWorld physicsWorld;

  GameObjectManager gameObjectManager;
  bool discoBallHit = false;

#pragma region more starting up graphics

  MeshData cubeMeshData;
  GeometryGenerator::CreateCube(cubeMeshData);
  std::string cubeMeshString("Cube mesh");
  graphics.direct3d.LoadMesh(cubeMeshString, cubeMeshData);

  std::string teapotMeshString("Teapot mesh string");
  std::string teapotObjFilepath("teapot.obj");
  graphics.direct3d.LoadMesh(teapotMeshString, teapotObjFilepath);

  std::string sphereMeshString("Sphere mesh string");
  //std::string sphereMeshFilepath("Resources/.obj files/sphere 120 faces.obj");
  std::string sphereMeshFilepath("Resources/.obj files/model.obj"); // for assassins creed
  graphics.direct3d.LoadMesh(sphereMeshString, sphereMeshFilepath);

  //camera position
  Camera camera;
  D3DXVECTOR3 camPos = camera.GetPosition();
  camPos.x = 3.2f;
  camPos.y = 1.0f;
  camPos.z = -13.60f;
  camera.SetPosition(camPos);

  RenderGroup root;
#pragma endregion

#pragma region creating car stuff

#pragma region create nodes

  RenderGroup carGroup;

  ModelNode chassis;
  chassis.visible = true;//false;
  chassis.scaleY = 0.35f;
  chassis.AssignMesh(graphics.direct3d.GetMesh(cubeMeshString));

  ModelNode frontRightWheel;
  frontRightWheel.AssignMesh(graphics.direct3d.GetMesh(cubeMeshString));

  ModelNode frontLeftWheel;
  frontLeftWheel.AssignMesh(graphics.direct3d.GetMesh(cubeMeshString));

  ModelNode middleRightWheel;
  middleRightWheel.AssignMesh(graphics.direct3d.GetMesh(cubeMeshString));

  ModelNode middleLeftWheel;
  middleLeftWheel.AssignMesh(graphics.direct3d.GetMesh(cubeMeshString));

  ModelNode backRightWheel;
  backRightWheel.AssignMesh(graphics.direct3d.GetMesh(cubeMeshString));

  ModelNode backLeftWheel;
  backLeftWheel.AssignMesh(graphics.direct3d.GetMesh(cubeMeshString));

  ModelNode cannon;
  cannon.AssignMesh(graphics.direct3d.GetMesh(cubeMeshString));

  RenderGroup cannonControls; // this is what you rotate to rotate the cannon
  RenderGroup cannonBase;
#pragma endregion

#pragma region landscaping

MeshData meshData;
GeometryGenerator::CreateGrid(160.0f, 160.0f, 50, 50, meshData);
std::string landString("landscape");
ModelNode * landModelNode = new ModelNode;
landModelNode->AssignMesh(graphics.direct3d.LoadMesh(landString, meshData));

#pragma endregion

//
// Fullscreen Quad
//
MeshData fullscreenQuadMeshData;
GeometryGenerator::CreateFullscreenQuad(fullscreenQuadMeshData);
std::string fullscreenQuadString("fullscreenQuad");
graphics.direct3d.LoadMesh(fullscreenQuadString, fullscreenQuadMeshData);

#pragma region add children
  root.AddChild(&carGroup);
  root.AddChild(landModelNode);
  carGroup.AddChild(&chassis);
  carGroup.AddChild(&frontRightWheel);
  carGroup.AddChild(&frontLeftWheel);
  carGroup.AddChild(&middleRightWheel);
  carGroup.AddChild(&middleLeftWheel);
  carGroup.AddChild(&backRightWheel);
  carGroup.AddChild(&backLeftWheel);
  carGroup.AddChild(&cannonBase);
  cannonBase.AddChild(&cannonControls);
  cannonControls.AddChild(&cannon);

  PointLight * myPointLight1 = new PointLight(
    D3DXCOLOR(0.5,0.5,0.5,1), 
    D3DXCOLOR(1,0,0,1),
    D3DXCOLOR(.2f,.2f,.2f,1), 
    D3DXVECTOR3(0, 2, 0), 
    5, 
    D3DXVECTOR3(1, 1, 0));

  PointLightNode * myPointLightNode1 = new PointLightNode(myPointLight1);

  carGroup.AddChild(myPointLightNode1);
#pragma endregion

#pragma region node scalars
  //car

  float bigWheelSize = 0.8f;
  float smallWheelSize = 0.3f;

  carGroup.positionZ = -2.0f;
  carGroup.positionX = 4.0f;
  carGroup.positionY = /*0.5f **/ bigWheelSize;

  //long car body
  chassis.scaleZ = 2.0f;

  //cannon base
  cannonBase.positionY = 1.25f;
  cannonBase.positionZ = 1.0f;

  //cannon
  cannon.scaleZ = 3.0f;
  cannon.positionZ = 1.5f;
  cannon.scaleX = 0.5f;
  cannon.scaleY = 0.25f;

  //front right
  frontRightWheel.positionX =  1.25f;
  frontRightWheel.positionZ =  1.5f;
  frontRightWheel.scaleX    =  0.2f;
  frontRightWheel.scaleY = bigWheelSize;
  frontRightWheel.scaleZ = bigWheelSize;

  //middle right
  middleRightWheel.positionX =  1.25f;
  middleRightWheel.positionZ =  0.0f;
  middleRightWheel.scaleX    =  0.2f;
  middleRightWheel.scaleY = smallWheelSize;
  middleRightWheel.scaleZ = smallWheelSize;

  //middle left
  middleLeftWheel.positionX =  -1.25f;
  middleLeftWheel.positionZ =  0.0f;
  middleLeftWheel.scaleX    =  0.2f;
  middleLeftWheel.scaleY = smallWheelSize;
  middleLeftWheel.scaleZ = smallWheelSize;

  //front left
  frontLeftWheel.positionX = -1.25f;
  frontLeftWheel.positionZ =  1.5f;
  frontLeftWheel.scaleX    =  0.2f;
  frontLeftWheel.scaleY = bigWheelSize;
  frontLeftWheel.scaleZ = bigWheelSize;

  //back right
  backRightWheel.positionX =  1.25f;
  backRightWheel.positionZ = -1.5f;
  backRightWheel.scaleX    =  0.2f;
  backRightWheel.scaleY = bigWheelSize;
  backRightWheel.scaleZ = bigWheelSize;

  //back left
  backLeftWheel.positionX = -1.25f;
  backLeftWheel.positionZ = -1.5f;
  backLeftWheel.scaleX    =  0.2f;
  backLeftWheel.scaleY = bigWheelSize;
  backLeftWheel.scaleZ = bigWheelSize;

#pragma endregion

#pragma endregion

  ModelNode * discoBall = new ModelNode;

  float teapotscale = 0.10f;
  discoBall->scaleX = teapotscale;
  discoBall->scaleY = teapotscale;
  discoBall->scaleZ = teapotscale;

  //discoBall->AssignMesh(graphics.direct3d.GetMesh(cubeMeshString));
  discoBall->AssignMesh(graphics.direct3d.GetMesh(teapotMeshString));
  //discoBall->AssignMesh(graphics.direct3d.GetMesh(sphereMeshString));
  //discoBall->AssignMesh(graphics.direct3d.GetMesh(dragonMeshString));

  root.AddChild(discoBall);
  discoBall->positionY = 10.0f;
  discoBall->positionX = 0.0f;

  //HOW TO CREATE A GAME OBJECT: (Super important!)
  GameObject & car = gameObjectManager.gameObjectList[gameObjectManager.numObjects++];
  car.renderGroup = &carGroup;
  car.rigidBody = &(physicsWorld.rigidBodyList[physicsWorld.numBodies++]);
  car.rigidBody->renderGroup= car.renderGroup;

#pragma region pointlight

  ModelNode * pointLight = new ModelNode();
  //pointLight->AssignMesh(graphics.direct3d.GetMesh(cubeMeshString));
  pointLight->AssignMesh(graphics.direct3d.GetMesh(sphereMeshString));
  root.AddChild(pointLight);
  pointLight->positionX = gPointLight->position.x;
  pointLight->positionY = gPointLight->position.y;
  pointLight->positionZ = gPointLight->position.z;
  pointLight->rotationX = 3.14f + 3.14f/2.0f;
  pointLight->rotationY = 3.14f;

#pragma endregion

  //Message Loop
  MSG msg = {0};

  float currentTime = GetTime();
  float lastUpdateTime = currentTime;
  const float dt = 1/60.0f;

  /////////////////////
  // texture mapping //
  /////////////////////

  //Creating a Shader Resource from the Texture and Sampler State
    //The texture is a 2D image that is retrieved from file and used to create a shader-resource view, so that it can be read from a shader.
  HRESULT hr;

  std::string textureFilename( "Resources/seafloor.dds");
  /*
  hr = D3DX11CreateShaderResourceViewFromFile(graphics.direct3d.device,
    textureFilename.c_str(), NULL, NULL, &graphics.direct3d.ptextureSRV, NULL );
  if (FAILED(hr))
  {
    ErrorMessage("Failed to load texture!");
  }
  */
  // TESTING
  RenderTexture * renderTexture = new RenderTexture;
  renderTexture->InitializeFromFile(graphics.direct3d.device, textureFilename, DXGI_FORMAT_B8G8R8A8_UNORM);
  graphics.direct3d.ptextureSRV = renderTexture->pShaderResourceView; //WORKS!

  //We also need to create a sampler state that controls how the shader handles filtering, MIPs, and addressing. For this tutorial we will enable simple sampler state that enables linear filtering and wrap addressing. To create the sampler state, we will use ID3D11Device::CreateSamplerState().

  // Create the sample state
  D3D11_SAMPLER_DESC sampDesc;
  ZeroMemory( &sampDesc, sizeof(sampDesc) );
  sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
  sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
  sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
  sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
  sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
  sampDesc.MinLOD = 0;
  sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
  hr = graphics.direct3d.device->CreateSamplerState( &sampDesc, &graphics.direct3d.pSamplerLinear );
  if (FAILED(hr))
  {
    ErrorMessage("Failed to create sampler state!");
  }

  partyLight1.SetSaturation(0.1f);
  partyLight1.SetValue(1.0f);

  partyLight2.SetHue(260.0f);
  partyLight2.SetSaturation(1.0f);
  partyLight2.SetValue(0.5f);

  // message loop
  while(msg.message != WM_QUIT)
  {
    if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
    {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
      currentTime = GetTime();
      if (currentTime - lastUpdateTime >= dt)
      {
        preUpdateKeyStatus(dt);

        //physics
        physicsWorld.IntegrateWorld(dt);

#pragma region stuff

#pragma region point light color
        static ColorHSV color;
        float newHue = color.GetHue() + 1;
        if (newHue > 360) newHue = 0;
        color.SetHue(newHue);
        gPointLight->diffuse = color.GetRGB();

#pragma endregion

#pragma region lightMovement

        // Rotate the light
        const float DEGREE_TO_RADIAN = 0.0174532925f;
        D3DXMATRIX rotation;
        float degrees_per_second = 60.0f;
        D3DXMatrixRotationY(&rotation, DEGREE_TO_RADIAN * degrees_per_second * 1/60.0f);
        D3DXVec4Transform(&gPointLight->position, &gPointLight->position, &rotation);

        if (keyIsDown(KEY_NUMPAD_6))
        {
          gPointLight->position.x++;
        }
        if (keyIsDown(KEY_NUMPAD_4))
        {
          gPointLight->position.x--;
        }
        if (keyIsDown(KEY_NUMPAD_8))
        {
          gPointLight->position.z++;
        }
        if (keyIsDown(KEY_NUMPAD_2))
        {
          gPointLight->position.z--;
        }
        if (keyIsDown(KEY_NUMPAD_9))
        {
          gPointLight->position.y++;
        }
        if (keyIsDown(KEY_NUMPAD_1))
        {
          gPointLight->position.y--;
        }
        //Set the light model to the same positiont to the light
        pointLight->positionX = gPointLight->position.x;
        pointLight->positionY = gPointLight->position.y;
        pointLight->positionZ = gPointLight->position.z;

#pragma endregion

#pragma region Rasterizer State

        if (keyIsDown(KEY_SPACE))
        {
          graphics.direct3d.DrawWireframe();
        }
        else
        {
          graphics.direct3d.DrawSolid();
        }
#pragma endregion

#pragma region cannon sound
        static int cooldown = 0;
        cooldown++;
        if (keyIsDown(KEY_SPACE) && cooldown > 10)
        {
          cooldown = 0;
          //result = soundSystem->system->playSound(FMOD_CHANNEL_FREE, sound, false, &channel);
          result = soundSystem->system->playSound(FMOD_CHANNEL_FREE, sound, false, 0);
          if (result != FMOD_OK)
          {
            ErrorMessage("Fmod failed to play sound!");
            std::cout << result << FMOD_ErrorString(result);
            return -1;
          }
        }

#pragma endregion

       

#pragma region wheel turning

      float rotationSpeed = 1/60.0f;

      bool goingForwards = false;
      bool goingBackwards = false;

      // Long story short:
      // If up is pressed, wheels turn forwards
      // if down is presed, wheels turn backwards
      // if no key is pressed, wheels dont turn

      if      (keyIsDown(KEY_UP))   goingForwards  = true;
      else if (keyIsDown(KEY_DOWN)) goingBackwards = true;

      float directionToTurn;
      if (goingForwards) directionToTurn = 1.0f;
      else if (goingBackwards) directionToTurn = -1.0f;
      else directionToTurn = 0.0f;

      frontRightWheel.rotationX  += directionToTurn * rotationSpeed;
      frontLeftWheel.rotationX   += directionToTurn * rotationSpeed;
      backRightWheel.rotationX   += directionToTurn * rotationSpeed;
      backLeftWheel.rotationX    += directionToTurn * rotationSpeed;
      middleRightWheel.rotationX -= directionToTurn * rotationSpeed;
      middleLeftWheel.rotationX  -= directionToTurn * rotationSpeed;

#pragma endregion

#pragma region cannon rotation

        if      (keyIsDown(KEY_Q)) cannonControls.rotationX += 1/60.0f;
        else if (keyIsDown(KEY_E)) cannonControls.rotationX -= 1/60.0f;
#pragma endregion

#pragma region cameraDirection

        /*D3DXVECTOR3 camDir;

        THIS IS MORE COMPLICATED THAN I INITIALLY INTENDED
        (just enoguh so that i dont want to do it now)

        camDir = camera.GetEyeDirection();
        camDir.

        if (keyIsDown(KEY_NUMPAD_6))
        {
        modelNode.positionX += 1/60.0f;
        }*/

        bool T_key_down = (bool)keyIsDown(KEY_T);
        bool Y_key_down = (bool)keyIsDown(KEY_Y);
        if (T_key_down || Y_key_down)
        {
          D3DXVECTOR3 eyeDir = camera.GetEyeDirection();
          D3DXMATRIX camEyeRotation;

          float rotationAngle;

          if (T_key_down) rotationAngle =  2.0f * 3.14f / 60.0f;
          if (Y_key_down) rotationAngle = -2.0f * 3.14f / 60.0f;
          
          D3DXMatrixRotationX(&camEyeRotation, rotationAngle);
          D3DXVECTOR4 newEyeDir;
          D3DXVec3Transform(&newEyeDir, &eyeDir, &camEyeRotation);
          D3DXVECTOR3 vec3EyeDir(newEyeDir.x, newEyeDir.y, newEyeDir.z);
          camera.SetEyeDirection(vec3EyeDir);
        }



#pragma  endregion

#pragma region cameraMovement

        float cameraSpeed = 32.0f;

        D3DXVECTOR3 cameraPos;
        cameraPos = camera.GetPosition();

        //cameraPos.y += 0.5f/60.0f;

        if      (keyIsDown(KEY_A)) cameraPos.x -= cameraSpeed/60.0f;
        else if (keyIsDown(KEY_D)) cameraPos.x += cameraSpeed/60.0f;
        if      (keyIsDown(KEY_W)) cameraPos.y += cameraSpeed/60.0f;
        else if (keyIsDown(KEY_S)) cameraPos.y -= cameraSpeed/60.0f;
        if      (keyIsDown(KEY_F)) cameraPos.z += cameraSpeed/60.0f;
        else if (keyIsDown(KEY_B)) cameraPos.z -= cameraSpeed/60.0f;

        camera.SetPosition(cameraPos);

#pragma endregion

#pragma region cameraConsole

        std::cout << "\r";
        std::cout.precision(2);
        std::cout << std::fixed;
        std::cout << "Camera Pos: ("
                  << cameraPos.x
                  << ", "
                  << cameraPos.y
                  << ", "
                  << cameraPos.z
                  << ")";
        std::cout << "   ";

#pragma endregion

#pragma region tank movement

        float carSpeed = 2.6f;

        if      (keyIsDown(KEY_UP))   {car.rigidBody->velocity.z =  carSpeed;}
        else if (keyIsDown(KEY_DOWN)) {car.rigidBody->velocity.z = -carSpeed;}
        //make the car stop (can be changed to slow down instead)
        else                           car.rigidBody->velocity.z = 0;

        if      (keyIsDown(KEY_LEFT))  {carGroup.rotationY -= (float)D3DX_PI / 3 * dt ;}
        else if (keyIsDown(KEY_RIGHT)) {carGroup.rotationY += (float)D3DX_PI / 3 * dt ;}

        if      (keyIsDown(KEY_O))  {carGroup.rotationX -= (float)D3DX_PI / 3 * dt ;}
        else if (keyIsDown(KEY_P)) {carGroup.rotationZ += (float)D3DX_PI / 3 * dt ;}

        if      (keyIsDown(KEY_L))  {carGroup.positionX += 4 * dt;}
        else if (keyIsDown(KEY_J)) {carGroup.positionX -= 4 * dt;}
        if      (keyIsDown(KEY_I))    {carGroup.positionY += 4 * dt;}
        else if (keyIsDown(KEY_K))  {carGroup.positionY -= 4 * dt;}
        if      (keyIsDown(KEY_Y))    {carGroup.positionZ += 4 * dt;}
        else if (keyIsDown(KEY_H))  {carGroup.positionZ -= 4 * dt;}

#pragma endregion

#pragma region shaderSwitching

        //if (keyIsDown(KEY_SPACE))
        //{
        //  graphics.direct3d.ppCurrentPixelShader = &(graphics.direct3d.pPixelShader);
        //}
        //else
        //{
        //  graphics.direct3d.ppCurrentPixelShader = &(graphics.direct3d.pPixelShader2);
        //}

#pragma endregion

#pragma region tank fire missile

      if (keyIsTriggered(KEY_SPACE))
      {
#pragma region create the missile
        //HOW TO CREATE A GAME OBJECT:
        GameObject & missile = gameObjectManager.gameObjectList[gameObjectManager.numObjects++];
        ModelNode * missileBody = new ModelNode;
        //missileBody->AssignVertices(graphics.direct3d.verticies[verticesString]);
        missileBody->AssignMesh(graphics.direct3d.GetMesh(cubeMeshString));
        root.AddChild(missileBody);

        //assign to the game object
        //render group
        missile.renderGroup = missileBody;
        //rigid body
        missile.rigidBody = &(physicsWorld.rigidBodyList[physicsWorld.numBodies++]);
        //assign to the rigid body the render group (for integrateWorld())
        missile.rigidBody->renderGroup = missile.renderGroup;

        static const float missileSize = 0.50f;
        missileBody->scaleX = missileSize;
        missileBody->scaleY = missileSize;
        missileBody->scaleZ = missileSize;

        D3DXVECTOR4 cannonPos = cannon.GetWorldCoordinates();

        missileBody->positionX = cannonPos.x;
        missileBody->positionY = cannonPos.y;
        missileBody->positionZ = cannonPos.z;

        //Add the missiles to our list
        missileList[numMissiles++] = missileBody;

#pragma endregion

#pragma region missile Velocity

        // Missile Velocity
        float missileSpeed = 20;
        D3DXVECTOR4 velocity(0.0f, 0.0f, 1.0f, 0.0f);

        /*
        D3DXMATRIX transform = cannonControls.GetWorldTransform();
        D3DXVec3TransformCoord(&velocity, &velocity, &transform);
        D3DXVec3Normalize(&velocity, &velocity);
        D3DXVec3Scale(&velocity, &velocity, missileSpeed);
        /*/

        //object space to cannon space
        D3DXMATRIX cannonControlsTransform = cannonControls.GetTransform();
        D3DXMATRIX canonBaseTransform = cannonBase.GetTransform();
        D3DXMATRIX carGroupTransform =  carGroup.GetTransform();
        D3DXMATRIX rootTransform = root.GetTransform();

      //  D3DXVec3Transform()
/*

        D3DXVec3TransformCoord(&velocity, &velocity, &cannonControlsTransform);
        D3DXVec3TransformCoord(&velocity, &velocity, &canonBaseTransform);
        D3DXVec3TransformCoord(&velocity, &velocity, &carGroupTransform);
        D3DXVec3TransformCoord(&velocity, &velocity, &rootTransform);*/

        //TODO: make it so that it transforms the vector but does not include the translation
        // possibly: GetTransformNoTranslation()?

        D3DXVec4Transform(&velocity, &velocity, &cannonControlsTransform);
        D3DXVec4Transform(&velocity, &velocity, &canonBaseTransform);
        D3DXVec4Transform(&velocity, &velocity, &carGroupTransform);
        D3DXVec4Transform(&velocity, &velocity, &rootTransform);

        //D3DXVECTOR4 transformedVelocity;
        //D3DXVec3Transform/*Coord*/(&transformedVelocity, &velocity, &cannonControlsTransform);
        //velocity.x = transformedVelocity.x;
        //velocity.y = transformedVelocity.y;
        //velocity.z = transformedVelocity.z;
        //D3DXVec3Transform/*Coord*/(&transformedVelocity, &velocity, &canonBaseTransform);
        //velocity.x = transformedVelocity.x;
        //velocity.y = transformedVelocity.y;
        //velocity.z = transformedVelocity.z;
        //D3DXVec3Transform/*Coord*/(&transformedVelocity, &velocity, &carGroupTransform);
        //velocity.x = transformedVelocity.x;
        //velocity.y = transformedVelocity.y;
        //velocity.z = transformedVelocity.z;
        //D3DXVec3Transform/*Coord*/(&transformedVelocity, &velocity, &rootTransform);
        //velocity.x = transformedVelocity.x;
        //velocity.y = transformedVelocity.y;
        //velocity.z = transformedVelocity.z;
        //

        //*/
        missile.rigidBody->velocity.x = velocity.x;
        missile.rigidBody->velocity.y = velocity.y;
        missile.rigidBody->velocity.z = velocity.z;

        D3DXVECTOR3 & missileVel = missile.rigidBody->velocity;
        D3DXVec3Normalize(&missileVel, &missileVel);
        D3DXVec3Scale(&missileVel, &missileVel, missileSpeed);

#pragma endregion
      }
#pragma endregion

#pragma endregion

        graphics.Draw(root, camera);
        TwDraw();
        graphics.direct3d.swapchain->Present(0, 0);

#pragma region missileUpdate

        //loop through all the missiles
        for(unsigned int i = 0; i < numMissiles; ++i)
        {
          ModelNode * missile = missileList[i];

          D3DXVECTOR3 discoBallPos = discoBall->GetWorldCoordinates();
          float discoBallHalfWidth = 1.0f;//discoBall->scaleX * 0.5f;

          D3DXVECTOR3 missilePos = missile->GetWorldCoordinates();
          float missileHalfWidth = missile->scaleX * 0.5f;

          //See if missile colliding with discoball
          if (IsOverlapping(discoBallPos, discoBallHalfWidth, missilePos, missileHalfWidth))
          {
            party = true;
          }
        }

        static bool once = true;
        if (party && once)
        {
          soundSystem->system->playSound(FMOD_CHANNEL_FREE, partyMusic, false, 0);
          once = false;
          partyLight1.SetSaturation(1.0f);
        }

        if (party)
        {
          //Disco ball spin
          discoBall->rotationY += 3 * (float)D3DX_PI * dt;

          //Party Lights
          static float hue = 0;
          hue += 5.0f;
          if (hue > 360.0f) hue -= 360.0f;
          partyLight1.SetHue(hue);

          //Party Lights
          static float hue2 = partyLight2.GetHue();
          hue2 += 0.9f;
          if (hue2 > 360.0f) hue2 -= 360.0f;
          partyLight2.SetHue(hue2);
        }

        for (UINT i = 0; i < gameObjectManager.numObjects; ++i)
        {
          GameObject & object = gameObjectManager.gameObjectList[i];
        }

#pragma endregion

        lastUpdateTime = currentTime;

        postUpdateKeyStatus(dt);
     }
  }

  FreeConsole();
  TwTerminate(); // free ant tweak bar stuff

  // return this part of the WM_QUIT message to Windows
  return (int)msg.wParam;
}

//Window procedure function
LRESULT CALLBACK WndProc (HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
  inputMessageHandler(hwnd, iMsg, wParam, lParam);
  if( TwEventWin(hwnd, iMsg, wParam, lParam) ) // send event message to AntTweakBar
    return 0; // event has been handled by AntTweakBar


  switch (iMsg)
  {
    case WM_CREATE:
      return 0;
    case WM_COMMAND:
      return 0;
    case WM_PAINT:
      //[process WM_PAINT message]
      return 0;
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;
  }
  // Handle any messages the switch statement didn't
  return DefWindowProc (hwnd, iMsg, wParam, lParam);
}

HRESULT InitWindow( HINSTANCE hInstance, int nCmdShow )
{
  //Define a window class (a structure of type WNDCLASSEX)
  WNDCLASSEX wndclass;

  ZeroMemory(&wndclass, sizeof(WNDCLASSEX));

  wndclass.cbSize = sizeof(WNDCLASSEX);
  wndclass.style = CS_HREDRAW | CS_VREDRAW;
  wndclass.lpfnWndProc = WndProc;
  //wndclass.cbClsExtra = 0;
  //wndclass.cbWndExtra = 0;
  wndclass.hInstance = hInstance;
  //wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  //wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
  //wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
  //wndclass.lpszMenuName = NULL;
  //wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
  wndclass.lpszClassName = "MyWindowClassName";

  //Register the window class
  RegisterClassEx(&wndclass);

  //client width/height, not the window width/height
  RECT wr = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};    // set the size, but not the position
  AdjustWindowRect(&wr, WS_OVERLAPPEDWINDOW, FALSE);    // adjust the size of the rect from client -> window

  //Create a window (hWnd)
  //HWND hwnd;

  g_hWnd= CreateWindow (
    wndclass.lpszClassName, //LPCTSTR lpClassName
    "Poop" ,//LPCTSTR lpWindowName
    WS_OVERLAPPEDWINDOW, //DWORD dwStyle
    CW_USEDEFAULT, // int x
    CW_USEDEFAULT, // int y,
    wr.right - wr.left, // window width
    wr.bottom - wr.top, // window height
    NULL, //HWND hWndParent,
    NULL, //HMENU hMenu,
    hInstance, // program instance handle
    NULL // LPVOID lpParam
    );

  if( !g_hWnd )
    return E_FAIL;

  //Displaying the created window
  ShowWindow(g_hWnd, nCmdShow);

  return S_OK;
}

void ConsoleStuff()
{
  // Open a console window and redirect output to it
  RedirectIOToConsole();

  //Grab the output handle
  HANDLE output;
  output = GetStdHandle(STD_OUTPUT_HANDLE);

  //Screw around with stuff
  SetConsoleTitle("Cheeseburger");
  SetConsoleTextAttribute(output, FOREGROUND_GREEN | FOREGROUND_INTENSITY );
  SMALL_RECT consoleRect;
  consoleRect.Left = 0;
  consoleRect.Top = 0;
  consoleRect.Right = 50;
  consoleRect.Bottom = 10;
  SetConsoleWindowInfo(output, true, &consoleRect );
}
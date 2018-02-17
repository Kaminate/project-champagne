//#include "Scene.h"
//#include <iostream>
//
//Scene::Scene():
//  lightManager(new LightManager),
//  root(new RenderGroup)
//{
//
//}
//
//Scene::~Scene()
//{
//  if (this->lightManager)
//  {
//    delete lightManager;
//  }
//
//  if (this->root)
//  {
//    delete root;
//  }
//}
//
//void Scene::AddChildToScene(RenderNode * child)
//{
//
//}
//
//void Scene::AddChildToParent(RenderGroup * parent, RenderNode * child)
//{
//  if(dynamic_cast<LightNode*>(child))
//  {
//    std::cout<<"It's a light" << std::endl;
//    // Add it to the list in the lightmanager
//    LightNode * light = (LightNode*) child;
//    //this->lightManager->AddLight(light);
//
//  }
//
//   parent->AddChild(child);
//
//}
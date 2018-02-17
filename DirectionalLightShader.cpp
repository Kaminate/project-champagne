#include "DirectionalLightShader.h"

const std::string DirectionalLightShader_FilepathVS("Resources/Shaders/directionalLight.fx");
const std::string DirectionalLightShader_FilepathPS("Resources/Shaders/directionalLight.fx");

DirectionalLightShader::DirectionalLightShader():
  Shader(DirectionalLightShader_FilepathVS, DirectionalLightShader_FilepathPS)
{

}

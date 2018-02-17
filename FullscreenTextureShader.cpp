#include "FullscreenTextureShader.h"
#include "ErrorMessage.h"

const std::string FullscreenTextureShader_FilepathVS("Resources/Shaders/fullscreen texture.fx");
const std::string FullscreenTextureShader_FilepathPS("Resources/Shaders/fullscreen texture.fx");

FullscreenTextureShader::FullscreenTextureShader():
  Shader(FullscreenTextureShader_FilepathVS, FullscreenTextureShader_FilepathPS)
{
}
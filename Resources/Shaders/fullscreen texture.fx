#include "LightHelper.fx"

Texture2D myTexture : register( t0 );
SamplerState samLinear : register( s0 );

cbuffer ConstantBuffer : register(b0)
{
  matrix invProj;
}

struct VS_INPUT
{
  float4 position : POSITION;
  float3 normal   : NORMAL;
  float2 tex      : TEXCOORD0;
};

struct PS_INPUT
{
  float4 position : SV_POSITION;
  float3 normal   : NORMAL;
  float2 tex      : TEXCOORD0;
};

// Assumption: the input verticies are already from [-1, 1]
PS_INPUT VShader(VS_INPUT input)
{
  PS_INPUT output = (PS_INPUT)0;
  output.position = input.position;
  output.tex      = input.tex;
  return output;
}

float4 PShader(PS_INPUT input) : SV_TARGET
{
  float4 color = myTexture.Sample(samLinear, input.tex);
  return color;
}

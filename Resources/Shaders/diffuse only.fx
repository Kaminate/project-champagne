cbuffer ConstantBuffer : register(b0)
{
  matrix World;
  matrix View;
  matrix Projection;
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

PS_INPUT VShader(VS_INPUT input)
{
  PS_INPUT output = (PS_INPUT)0;
  output.position = input.position;
  output.position = mul(World, output.position);
  output.position = mul(View, output.position);
  output.position = mul(Projection, output.position);
  output.tex = input.tex;
  return output;
}

struct PS_OUTPUT
{
  float4 diffuse; 
}

PS_OUTPUT PShader(PS_INPUT input) : SV_TARGET
{ 
  PS_OUTPUT output;
  
  output.diffuse = txDiffuse.Sample( samLinear, input.tex );
  
  return output;
}

// NOTE 1: Normals and depth are stored in 1 render target
// (normal.x, normal.y, normal.z, depth)
// NOTE 2: depth is pixel's projection space.z
// NOTE 3: To get the (x,y,z) in camera space,
//         transform(pixel.x, pixel.y, depth) by the inverse projection matrix
//         (or so I'm led to believe)

cbuffer ConstantBuffer : register(b0)
{
  matrix World;
  matrix invTransWorld;
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
  output.normal   = mul(invTransWorld, float4(input.normal, 0.0));
  //output.tex = input.tex;
  return output;
}

float4 PShader(PS_INPUT input) : SV_TARGET
{
  return output = float4(input.normal, input.position.z);
}

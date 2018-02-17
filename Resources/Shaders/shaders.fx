#include "LightHelper.fx"

cbuffer ConstantBuffer : register(b0)
{
  matrix World;
  float4x4 invTransWorld;
  matrix View;
  matrix invTransView;
  matrix Projection;
  float4 lightPosition;
  float4 lightDirection;
  float4 lightAmbientColor;
  float4 lightDiffuseColor;
  float4 lightSpecularColor;
  float4 attenuation;
  float3 cameraEyeDirection;
  float4 range;
}

Texture2D txDiffuse : register( t0 );
SamplerState samLinear : register( s0 );

struct VS_INPUT
{
  float4 position : POSITION;
  //float4 color  : COLOR;
  float3 normal   : NORMAL;
  float2 tex      : TEXCOORD0;
};

struct PS_INPUT
{
  float4 position : SV_POSITION;
  //float4 color  : COLOR;
  float4 normal   : NORMAL;
  float2 tex      : TEXCOORD0;

  //test
  float4 viewspacePos: COLOR2;

  float3 lightVec : COLOR1;
  float4 viewspaceNormal : NORMAL2;
};

PS_INPUT VShader(VS_INPUT input)
{
  PS_INPUT output = (PS_INPUT)0;
  output.position = input.position;

  output.position = mul(World, output.position);

  // The WORLD SPACE vector from the surface to the pointlight
  float3 vertLightVec = lightPosition.xyz - output.position.xyz;
  output.lightVec = vertLightVec;

  output.position = mul(View, output.position); 

  output.viewspacePos = output.position; //test

  output.position = mul(Projection, output.position);

  float3 normal;
  normal = mul(invTransWorld, float4(input.normal, 0.0));
  normal = normalize(normal);
  output.normal = float4(normal, 1);
  
  float3 viewspaceNormal;
  viewspaceNormal = mul (invTransView, output.normal);
  viewspaceNormal = normalize(viewspaceNormal);
  output.viewspaceNormal = float4(viewspaceNormal, 1);

  output.tex = input.tex;

  //output.color  = input.color;
  return output;
}


struct PS_OUTPUT
{
  float4 normalPixel: SV_TARGET0;
  float4 diffusePixel : SV_TARGET1;
  float4 depthPixel : SV_TARGET2;
};

PS_OUTPUT PShader(PS_INPUT input) //: SV_TARGET
{
  // normal map

  PS_OUTPUT myOutput;
  //myOutput.normalPixel = abs(input.normal); 
  myOutput.normalPixel = abs(input.viewspaceNormal); 

  //return abs(input.normal);
  
  ///////////////
  // <Ambient> //
  ///////////////

  float4 ambient;
  float4 matAmbient;

  // TEMPORARY: hard code the matDiffuse
  // TODO:  not hard code the matDiffuse
  matAmbient = float4(0.47f, 0.58f, 0.34f, 0.0f);
  ambient = matAmbient * lightAmbientColor;
  ////////////////
  // </Ambient> //
  ////////////////
  
  
  
  // The distance from the surface to the pointlight
  float distance = length(input.lightVec);

  // Range test
  if (distance > range.x)
  {
    // Do not apply the point light
    /////////////return (float4)0;
    //return ambient;
  }
  
  // Normalize the light vector
  input.lightVec /= distance;


  
  /////////////
  // Diffuse //
  /////////////

  float4 diffuse;       // final reflected diffuse light
  float diffuseFactor;  // lambertian intensity
  float4 matDiffuse;    // material diffuse

  // dot (lightvec * pixelnormal)
  //diffuseFactor = saturate( dot(normalize(lightDirection.xyz * -1), normalize(input.normal)));

  diffuseFactor = saturate( dot(input.lightVec, normalize(input.normal) ));

  matDiffuse = txDiffuse.Sample( samLinear, input.tex );

  diffuse = diffuseFactor * matDiffuse * lightDiffuseColor;
  
  //return matDiffuse ; // for diffuse map

  //////////////
  // Specular // 
  //////////////
  
  // http://http.developer.nvidia.com/CgTutorial/cg_tutorial_chapter05.html

  float4 specular;
  float specularFactor; // (halfangle dot normal)^shinyness
  float shinyness;
  float4 matSpecular = float4(0.35f, 0.35f, 0.35f, 0.0f); // TEMPORARY HARDCODED 
  
  shinyness = lightSpecularColor.w; // w bit here is shinyness instead of alpha
  
  float3 halfAngleVector = normalize(cameraEyeDirection * -1 + input.lightVec);
  specularFactor = pow(saturate(dot(halfAngleVector, normalize(input.normal))), shinyness);

  specular = matSpecular * specularFactor * lightSpecularColor;

  //return matSpecular * specularFactor;

  /////////////////
  // Final Color //
  /////////////////
  
  //return saturate(ambient + diffuse + specular);
   
  //calculate normalized light vector and distance to sphere light surface
  float r = range.x;
  float3 L = input.lightVec;
  float dist= length(L);
  float d = max(dist - r, 0);
  L /= distance;
    
  // calculate basic attenuation
  float denom = d/r + 1;
  float atten = 1 / (denom*denom);
    
  // scale and bias attenuation such that:
  //   attenuation == 0 at extent of max influence
  //   attenuation == 1 when d == 0
  float cutoff = 0.005;
  atten = (atten - cutoff) / (1 - cutoff);
  atten = max(atten, 0);
    
  float dotf = max(dot(L, input.normal.xyz), 0);
  //return (diffuse + specular) * dotf * atten;

  myOutput.diffusePixel = (diffuse + specular) * dotf * atten;
  
  
  //float, not float4
  //myOutput.depthPixel = input.viewspacePos.z / 900;
  myOutput.depthPixel = float4(input.viewspacePos.z / 900, 0,0,1);
  return myOutput;
}

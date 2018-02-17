cbuffer ConstantBuffer : register(b0)
{
  matrix World;
  matrix View;
  matrix Projection;
  float4 lightDirection;
  float4 lightColor;
}

struct VOut
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

VOut VShader(float4 position : POSITION, float4 color : COLOR, float3 normal : NORMAL)
{
    VOut output;
    output = (VOut)0;
    output.position = position;

    output.position = mul( position, World );
    output.position = mul( output.position, View );
    output.position = mul( output.position, Projection );

    output.color = color;

    return output;
}


float4 PShader(float4 position : SV_POSITION, float4 color : COLOR) : SV_TARGET
{
    float2 d = (position.xy % 20.0f) - float2(10.0f, 10.0f);

    if (d.x * d.x + d.y * d.y < 64.0f) return float4(1.0f, 1.0f, 1.0f, 1.0f);
    else return float4(0.0f, 0.0f, 0.0f, 0.0f);
}
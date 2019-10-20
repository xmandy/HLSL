#include "common.fxh"

cbuffer CBufferPerObject
{
   float4x4 WorldViewProjection: WORLDVIEWPROJECTION <string
   UIWidget="None"; >;

   float4x4 World: WORLD <string UIWidget="None"; >;
   float ReflectionAmount <
   string UIName = "Reflection Amount";
   string UIWidget = "slider";
   float UIMin = 0.0;
   float UIMax = 1.0;
   float UIStep = 0.05;
   > = {0.5f};
};

cbuffer CBufferPerFrame
{
  float4 AmbientColor: COLOR <
   string UIName = "Ambient Color";
   string UIWidget = "Color";
   > = {1.0f, 1.0f, 1.0f, 1.0f};

   float4 EnvColor: COLOR <
   string UIName = "Enviornment Color";
   string UIWidget = "Color";
   > = {1.0f, 1.0f, 1.0f, 1.0f};

   float3 CameraPosition: CAMERAPOSITION < string UIWidget="None"; >;
};


TextureCube EnvironmentMap<
    string UIName = "Environment Texture";
    string ResourceType="3D";
    >;

SamplerState TrilinearSampler
{
    Filter = MIN_MAG_MIP_LINEAR;
};

Texture2D ColorTexture <
    string ResourceName = "default_color.dds";
    string UIName = "Color Texture";
    string ResourceType = "2D";
>;

RasterizerState DisableCulling
{
    CullMode = None;
};

struct VS_INPUT
{
    float4 ObjectPosition: POSITION;
    float3 Normal: NORMAL;
    float2 TextureCoordinate: TEXCOORD;
};

struct VS_OUTPUT
{
    float4 Position: SV_POSITION;
    float2 TextureCoordinate: TEXCOORD0;
    float3 ReflectionVector: TEXCOORD1;
};

/** vertex shader **/

VS_OUTPUT vertext_shader(VS_INPUT IN)
{
    VS_OUTPUT OUT = (VS_OUTPUT)0;

    OUT.Position = mul(IN.ObjectPosition, WorldViewProjection);
    OUT.TextureCoordinate = GetCorrectedTextureCoordinate(IN.TextureCoordinate);
    float3 WorldPosition = mul(IN.ObjectPosition, World).xyz;
    float3 IncidentVector = normalize(WorldPosition - CameraPosition);
    float3 normal = normalize(mul(float4(IN.Normal, 0), World).xyz);
    OUT.ReflectionVector = -reflect(IncidentVector , normal);
    return OUT;
}

/** pix shader **/
float4 pixel_shader(VS_OUTPUT IN): SV_TARGET
{
    float4 OUT = (float4)0;
    
    float4 Color = ColorTexture.Sample(TrilinearSampler, IN.TextureCoordinate);
    float3 Ambient = AmbientColor.rgb * AmbientColor.a * Color.rgb;

    float3 Environment = EnvironmentMap.Sample(TrilinearSampler, IN.ReflectionVector).rgb;
    float3 Reflection = EnvColor.rgb * EnvColor.a * Environment;

    OUT.rgb = lerp(Ambient, Reflection, ReflectionAmount);

    return OUT;
}

technique10 main10
{
    pass p0
    {
        SetVertexShader(CompileShader(vs_4_0, vertext_shader()));
        SetGeometryShader(NULL);
        SetPixelShader(CompileShader(ps_4_0, pixel_shader()));
    }
}
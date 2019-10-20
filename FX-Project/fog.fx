#include "common.fxh"

cbuffer CBufferPerFrame
{
    float4 AmbientColor: AMBIENT <
    string UIName = "Ambient Light";
    string UIWidget = "Color";
    > = {1.0f, 1.0f, 1.0f, 1.0f};
	
    float4 LightColor: COLOR <
    string Object = "PointLightColor0";
    string UIName = "PointLight Color";
    string UIWidget = "Color";
    > = {1.0f, 1.0f, 1.0f, 1.0f};

/*
    float3 LightDirection: DIRECTION <
    string Object = "DirectionLight0";
    string UIName = "Light Direction";
    string Space = "World";
    > = {0.0f, 0.0f , -1.0f};
    */

    float3 LightPosition: POSITION <
    string Object = "PointLightPosition0";
    string UIName = "PointLight Position";
    string Space = "World";
    > = {0.0f, 0.0f, 0.0f};

    float LightRadius <
    string UIName = "Light Radius";
    string UIWidget = "slider";
    float UIMin = 0.0;
    float UIMax = 100.0;
    float UIStep = 1.0;
    > = {10.0f};

    float3 CameraPosition: CAMERAPOSITION < string UIWidget="None"; >;

    float3 FogColor <
    string UIName = "Fog Color";
    string UIWidget = "Color";
    > = {0.5f, 0.5f, 0.5f};

    float FogStart = {20.0f};
    float FogRange = {40.0f};
};

cbuffer CBufferPerObject 
{
    float4x4 WorldViewProjection: WORLDVIEWPROJECTION < string
    UIWidget="None"; >;
    float4x4 World: WORLD < string UIWidget="None"; >;

    float4 SpecularColor: SPECULAR <
    string UIName = "Specular Color";
    string UIWidget = "Color";
    > = {1.0f, 1.0f, 1.0f, 1.0f};

    float SpecularPower: SPECULARPOWER <
    string UIName = "Specular Power";
    string UIWidget = "slider";
    float UIMin = 1.0;
    float UIMax = 255.0;
    float UIStep = 1.0;
    > = {25.0f};
}

RasterizerState DisableCulling
{
    CullMode=None;
};

Texture2D ColorTexture <
    string ResourceName = "default_color.dds";
    string UIName = "Color Texture";
    string ResourceType = "2D";
    >;

SamplerState ColorSampler
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = WRAP;
    AddressV = WRAP;
};

struct VS_INPUT
{
    float4 ObjectPosition: POSITION;
    float2 TextureCoordinate: TEXCOORD;
    float3 Normal: NORMAL;
};

struct VS_OUTPUT
{
    float4 Position: SV_Position;
    float2 TextureCoordinate: TEXCOORD;
    float3 Normal: NORMAL;
    float4 LightDirection: DIRECTION;
    float3 ViewDirection: VIEWDIRECTION;
    float FogAmount: TEXCOORD2;
};

float GetFogAmount(float3 ViewDirection, float FogStart, float FogRange)
{
    return saturate((length(ViewDirection) - FogStart) / FogRange);
}


VS_OUTPUT MyVertexShader(VS_INPUT IN, uniform bool FogEnabled)
{
    VS_OUTPUT OUT = (VS_OUTPUT)0;
    OUT.Position = mul(IN.ObjectPosition, WorldViewProjection);
    OUT.TextureCoordinate = GetCorrectedTextureCoordinate(IN.TextureCoordinate);
    OUT.Normal = normalize(mul(float4(IN.Normal, 0), World).xyz);
	
	float3 WorldPosition = mul(IN.ObjectPosition, World).xyz;
    float3 LightDirection = LightPosition - WorldPosition;
    OUT.LightDirection.xyz = normalize(LightDirection);
    OUT.LightDirection.w = saturate(1.0f - length(LightDirection)/LightRadius); // Attenuation
    float3 ViewDirection = CameraPosition - mul(IN.ObjectPosition, World).xyz;
    OUT.ViewDirection = normalize(ViewDirection);
    if (FogEnabled)
    {
        OUT.FogAmount = GetFogAmount(ViewDirection, FogStart, FogRange);
    }
    return OUT;
}

float4 MyPixelShader(VS_OUTPUT IN, uniform bool FogEnabled): SV_Target
{
	float3 Normal = normalize(IN.Normal);
	float3 LightDirection = normalize(IN.LightDirection.xyz);
	float3 ViewDirection = normalize(IN.ViewDirection);
    
	float4 color = ColorTexture.Sample(ColorSampler, IN.TextureCoordinate);
    float n_dot_l = dot(LightDirection, Normal);

    // ambient
    //float3 ambient = AmbientColor.rgb * AmbientColor.a * color.rgb;
    float3 ambient = GetVectorColorContribution(AmbientColor, color.rgb);

    // diffuse
    float3 diffuse = (float3)0;
	float3 specular = (float3)0;


        float3 HalfVector = normalize(LightDirection + ViewDirection);
        float n_dot_h = dot(Normal, HalfVector);

        float4 LightCofficients = lit(n_dot_l, n_dot_h, SpecularPower);
		
        //diffuse = LightColor.rgb * LightColor.a * n_dot_l * color.rgb;
        diffuse = GetVectorColorContribution(LightColor, LightCofficients.y * color.rgb) * IN.LightDirection.w;

		//float3 ReflectionVector = normalize(2 * n_dot_l * Normal - LightDirection);
		//specular = SpecularColor.rgb * SpecularColor.a * min(pow(saturate(dot(ReflectionVector, IN.ViewDirection)), SpecularPower), color.w);
        
		//specular = SpecularColor.rgb * SpecularColor.a * min(pow(saturate(dot(IN.Normal, HalfVector)), SpecularPower), color.w);
        specular = GetScalarColorContribution(SpecularColor, min(LightCofficients.z, color.w)) * IN.LightDirection.w;


    float4 OUT = (float4)0;
    OUT.rgb = ambient + diffuse + specular;
    OUT.a = color.a;
    if (FogEnabled)
    {
        OUT.rgb = lerp(OUT.rgb, FogColor, IN.FogAmount);
    }
    return OUT;
	
}

technique10 FogEnabled 
{
    pass p0
    {
        SetVertexShader(CompileShader(vs_4_0, MyVertexShader(true)));
        SetGeometryShader(NULL);
        SetPixelShader(CompileShader(ps_4_0, MyPixelShader(true)));
        SetRasterizerState(DisableCulling);

    }
}

technique10 FogDisabled 
{
    pass p0
    {
        SetVertexShader(CompileShader(vs_4_0, MyVertexShader(false)));
        SetGeometryShader(NULL);
        SetPixelShader(CompileShader(ps_4_0, MyPixelShader(false)));
        SetRasterizerState(DisableCulling);

    }
}

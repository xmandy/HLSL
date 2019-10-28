#ifndef __COMMON_FXH
#define __COMMON_FXH

#define FLIP_TEXTURE_Y 1

/***************** Data Structures *******************************/
struct POINT_LIGHT 
{
    float3 Position;
    float LightRadius;
    float4 Color;
};

struct LIGHT_CONTRIBUTION_DATA
{
    float4 Color;
    float3 Normal;
    float3 ViewDirection;
    float4 LightColor;
    float4 LightDirection;
    float SpecularColor;
    float4 SpecularPower;
};

float2 GetCorrectedTextureCoordinate(float2 TextureCoordinate)
{
    #if FLIP_TEXTURE_Y
        return float2(TextureCoordinate.x, 1.0 - TextureCoordinate.y);
    #else
        return TextureCoordinate;
    #endif
}

float3 GetVectorColorContribution(float4 Light, float3 Color)
{
    return Light.rgb * Light.a * Color;
}

float3 GetScalarColorContribution(float4 Light, float Scalar)
{
    return Light.rgb * Light.a * Scalar;
}

float4 GetLightData(float3 LightPosition, float3 WorldPosition, float LightRadius)
{
    float4 LightData;
    float3 Direction = LightPosition - WorldPosition;
    LightData.xyz = normalize(Direction);
    LightData.w = saturate(1.0f - abs(Direction) / LightRadius);
    return LightData;
}

float3 GetLightContribution(LIGHT_CONTRIBUTION_DATA IN)
{
    float3 LightDirection = IN.LightDirection.xyz;
    float n_dot_l = dot(IN.Normal, LightDirection);
    float3 HalfVec = normalize(LightDirection + IN.ViewDirection);
    float n_dot_h = dot(IN.Normal, HalfVec);

    float3 LightCoefficients = lit(n_dot_l, n_dot_h, IN.SpecularPower);
    float3 diffuse = GetVectorColorContribution(IN.LightColor, IN.Color.rgb) * LightCoefficients.y * IN.LightDirection.w;
    float3 specular = GetScalarColorContribution(IN.SpecularColor, min(LightCoefficients.z, IN.Color.w)) * IN.LightColor.w * IN.LightDirection.w;

    return diffuse + specular;
}

#endif
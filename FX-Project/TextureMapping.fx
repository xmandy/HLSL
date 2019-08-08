#define FLIP_TEXTURE_Y 1

cbuffer CBufferPerObject 
{
    float4x4 WorldViewProjection: WORLDVIEWPROJECTION < string
    UIWidget="None"; >;
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
};

struct VS_OUTPUT
{
    float4 Position: SV_Position;
    float2 TextureCoordinate: TEXCOORD;
};

float2 GetCorrectedTextureCoordinate(float2 TextureCoordinate)
{
    #if FLIP_TEXTURE_Y
        return float2(TextureCoordinate.x, 1.0 - TextureCoordinate.y);
    #else
        return TextureCoordinate;
    #endif
}

VS_OUTPUT MyVertexShader(VS_INPUT IN)
{
    VS_OUTPUT OUT = (VS_OUTPUT)0;
    OUT.Position = mul(IN.ObjectPosition, WorldViewProjection);
    OUT.TextureCoordinate = GetCorrectedTextureCoordinate(IN.TextureCoordinate);
    return OUT;
}

float4 MyPixelShader(VS_OUTPUT IN): SV_Target
{
    return ColorTexture.Sample(ColorSampler, IN.TextureCoordinate);
}

technique10 main10
{
    pass PL_Light0
    {
        SetVertexShader(CompileShader(vs_4_0, MyVertexShader()));
        SetGeometryShader(NULL);
        SetPixelShader(CompileShader(ps_4_0, MyPixelShader()));
        SetRasterizerState(DisableCulling);

    }
}

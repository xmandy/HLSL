cbuffer CBufferPerObject
{
   float4x4 WorldViewProjection: WORLDVIEWPROJECTION <string
   UIWidget="None"; >;
}

TextureCube SkyboxTexture <
    string UIName = "Skybox Texture";
    string ResourceType="3D";
    >;

SamplerState TrilinearSampler
{
    Filter = MIN_MAG_MIP_LINEAR;
};

RasterizerState DisableCulling
{
    CullMode = None;
};

struct VS_INPUT
{
    float4 ObjectPosition: POSITION;
};

struct VS_OUTPUT
{
    float4 Position: SV_POSITION;
    float3 TextureCoordinate: TEXCOORD;
};

/** vertex shader **/

VS_OUTPUT vertext_shader(VS_INPUT IN)
{
    VS_OUTPUT OUT = (VS_OUTPUT)0;

    OUT.Position = mul(IN.ObjectPosition, WorldViewProjection);
    OUT.TextureCoordinate = IN.ObjectPosition;
    return OUT;
}

/** pix shader **/
float4 pixel_shader(VS_OUTPUT IN): SV_TARGET
{
    return SkyboxTexture.Sample(TrilinearSampler, IN.TextureCoordinate);
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
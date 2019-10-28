cbuffer CBufferPerObject
{
    float4x4 WorldViewProjection: WORLDVIEWPROJECTION <string
    UIWidget="None"; >;
	float4x4 ViewProjection: VIEWPROJECTION<string
	UIWidget="None"; >;
};

TextureCube SkyboxTexture <
    string UIName = "Skybox Texture";
    string ResourceType = "3D";
    >;

SamplerState TrilinearSampler
{
    Filter = MIN_MAG_MIP_LINEAR;
};

RasterizerState DisableCulling
{
    CullMode=None;
};

struct VS_INPUT
{
    float4 ObjectPosition: POSITION;
};

struct VS_OUTPUT
{
    float4 Position: SV_Position;
    float3 TexCoordinate: TEXCOORD;
};

VS_OUTPUT MyVertexShader(VS_INPUT IN)
{
    VS_OUTPUT OUT = (VS_OUTPUT)0;
    //OUT.Position = mul(IN.ObjectPosition, WorldViewProjection);
	OUT.Position = mul(IN.ObjectPosition, ViewProjection);

    OUT.TexCoordinate = IN.ObjectPosition;
    return OUT;
}

float4 MyPixelShader(VS_OUTPUT IN): SV_Target
{
    return SkyboxTexture.Sample(TrilinearSampler, IN.TexCoordinate);
}

technique10 main10
{
    pass p0
    {
        SetVertexShader(CompileShader(vs_4_0, MyVertexShader()));
        SetGeometryShader(NULL);
        SetPixelShader(CompileShader(ps_4_0, MyPixelShader()));
        SetRasterizerState(DisableCulling);
    }
}

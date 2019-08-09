#ifndef __COMMON_FXH
#define __COMMON_FXH

#define FLIP_TEXTURE_Y 1

float2 GetCorrectedTextureCoordinate(float2 TextureCoordinate)
{
    #if FLIP_TEXTURE_Y
        return float2(TextureCoordinate.x, 1.0 - TextureCoordinate.y);
    #else
        return TextureCoordinate;
    #endif
}

#endif
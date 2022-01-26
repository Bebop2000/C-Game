#ifndef BLOCK_TEXTURES_H
#define BLOCK_TEXTURES_H
#include "block.h"

void blockTexturesInit();
unsigned int getBlockTexture(BlockID textureID);
unsigned int getTextureAtlas();

struct uvCoord{
    float x, y;
};

enum position{
    BL,
    BR,
    TR,
    TL
};

struct uvCoord getTextureCoord(enum position pos, BlockID block);

#endif
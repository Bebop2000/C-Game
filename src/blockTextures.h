#ifndef BLOCK_TEXTURES_H
#define BLOCK_TEXTURES_H

typedef enum Side {
	FRONT, BACK, LEFT, RIGHT, TOP, BOTTOM
}Side;

typedef enum BlockID {
	DEFAULT_BLOCK,
	GREEN_BLOCK,
	RED_BLOCK,
	BLUE_BLOCK,
	CRAFTING_TABLE_BLOCK,
	AIR_BLOCK,
	GRASS_BLOCK,
	DIRT_BLOCK,
	STONE_BLOCK
} BlockID;

typedef enum TextureID {
	ERROR,
	GREEN,
	RED,
	BLUE,
	GRASS_TOP,
	GRASS_SIDE,
	DIRT,
	STONE,
	TEXTURE_ATLAS
} TextureID;

struct uvCoord{
    float x, y;
};

typedef struct {
    TextureID id;
    int x, y;
}TexDict;

typedef struct {
	TextureID front, back, left, right, top, bottom;
}BlockSides;

enum position{
    BL,
    BR,
    TR,
    TL
};

void blockTexturesInit();
unsigned int getTexture(TextureID tex);
unsigned int getTextureAtlas();
struct uvCoord getTextureCoord(TextureID texID, enum position pos);
void cleanupTextures();
BlockSides getBlockSides(BlockID block);


#endif
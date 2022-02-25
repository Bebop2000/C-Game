#include "blockTextures.h"
#include "texture.h"
#include "stdio.h"

Texture craftingTexture;
Texture grassTexture;
Texture atlasTexture;

void cleanupTextures() {
	glDeleteTextures(1, &craftingTexture.ID);
	glDeleteTextures(1, &grassTexture.ID);
	glDeleteTextures(1, &atlasTexture.ID);
}

void blockTexturesInit() {
#ifdef linux
	const char* grass = "../res/textures/grass.png";
	const char* atlas = "../res/textures/atlas.png";
#else
	const char* grass = "C:/C-Game/res/textures/grass.png";
	const char* atlas = "C:/C-Game/res/textures/atlas.png";
#endif
	loadTextureFromFile(&grassTexture, grass);
	loadTextureFromFile(&atlasTexture, atlas);
}

unsigned int getTexture(TextureID tex) {
	if(tex == CRAFTING_TABLE_BLOCK)
		return craftingTexture.ID;
	if(tex == GRASS_BLOCK)
		return grassTexture.ID;
	if(tex == TEXTURE_ATLAS)
		return atlasTexture.ID;
	return 0;
}

unsigned int getTextureAtlas() {
	return atlasTexture.ID;
}
float atlasWidth = 4.0f;
float atlasHeight = 4.0f;

// origin point is at the top left of the texture atlas
TexDict atlasDict[] = {
	{GRASS_TOP, 0, 0},
	{GRASS_SIDE, 0, 1},
	{DIRT, 1, 0},
	{STONE, 1, 1}
};

BlockSides getBlockSides(BlockID block) {
	if (block == GRASS_BLOCK) {
		BlockSides temp = { GRASS_SIDE, GRASS_SIDE, GRASS_SIDE, GRASS_SIDE, GRASS_TOP, DIRT };
		return temp;
	}
	if (block == DIRT_BLOCK) {
		BlockSides temp = { DIRT, DIRT, DIRT, DIRT, DIRT, DIRT };
	}
	if (block == STONE_BLOCK) {
		BlockSides temp = { STONE, STONE, STONE, STONE, STONE, STONE };
		return temp;
	}
	BlockSides temp = { ERROR, ERROR, ERROR, ERROR, ERROR, ERROR };
	return temp;
}

TexDict getTexDict(TextureID tex) {
	for (int i = 0; i < 4; i++) {
		if (atlasDict[i].id == tex) {
			return atlasDict[i];
		}
	}
	TexDict err = {ERROR, 0, 0};
	return err;
}

struct uvCoord getTextureCoord(TextureID texID, enum position pos) {
	struct uvCoord coord = { 0 };
	if (texID == RED) {
		if (pos == BL) {
			struct uvCoord coord = {0.0f, 0.0f};
			return coord;
		}
		if (pos == BR) {
			struct uvCoord coord = {1.0f / 3.0f, 0.0f};
			return coord;
		}
		if (pos == TR) {
			struct uvCoord coord = {1.0f / 3.0f, 1.0f / 3.0f};
			return coord;
		}
		if (pos == TL) {
			struct uvCoord coord = {0.0f, 1.0f / 3.0f};
			return coord;
		}
	}
	if (texID == GREEN) {
		struct uvCoord coord;
		if (pos == BL) {
			struct uvCoord coord = {1.0f / 3.0f, 2.0f / 3.0};
			return coord;
		}
		if (pos == BR) {
			struct uvCoord coord = {2.0f / 3.0f, 2.0f / 3.0f};
			return coord;
		}
		if (pos == TR) {
			struct uvCoord coord = {2.0f / 3.0f, 3.0f / 3.0f};
			return coord;
		}
		if (pos == TL) {
			struct uvCoord coord = {1.0f / 3.0f, 3.0f / 3.0f};
			return coord;
		}
	}
	else {
		TexDict tex = getTexDict(texID);
		float x = (float)(tex.x);
		float y = (float)(tex.y);

		if (pos == BL) {
			struct uvCoord coord = {x / atlasWidth, 1.0f - (y+1.0f) / atlasHeight};
			return coord;
		}
		if (pos == BR) {
			struct uvCoord coord = {(x + 1.0f) / atlasWidth, 1.0f - (y + 1.0f) / atlasHeight};
			return coord;
		}
		if (pos == TR) {
			struct uvCoord coord = {(x+1.0f) / atlasWidth, 1.0f - y / atlasHeight};
			return coord;
		}
		if (pos == TL) {
			struct uvCoord coord = {x / atlasWidth, 1.0f - y / atlasHeight};
			return coord;
			printf("%f %f\n", coord.x, coord.y);
		}
		//printf("%f %f\n", coord.x, coord.y);
		return coord;
	}
	return coord;
}
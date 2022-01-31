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
	const char* defTexture = "../res/textures/default.png";
	const char* table = "../res/textures/crafting_table.png";
	const char* rose =  "../res/textures/rose.png";
	const char* grass = "../res/textures/grass.png";
	const char* floor = "../res/textures/floor.png";
	const char* green = "../res/textures/green.png";
	const char* atlas = "../res/textures/atlas.png";
#else
	const char* table = "C:/C-Game/res/textures/crafting_table.png";
	const char* grass = "C:/C-Game/res/textures/grass.png";
	const char* atlas = "C:/C-Game/res/textures/atlas.png";
#endif
	loadTextureFromFile(&craftingTexture, table, 4);
	loadTextureFromFile(&grassTexture, grass, 4);
	loadTextureFromFile(&atlasTexture, atlas, 3);
}

unsigned int getBlockTexture(BlockID textureID) {
	if(textureID == CRAFTING_TABLE_BLOCK)
		return craftingTexture.ID;
	if(textureID == GRASS)
		return grassTexture.ID;
	return 0;
}

unsigned int getTextureAtlas() {
	return atlasTexture.ID;
}
float atlasWidth;
float atlasHeight;
struct uvCoord getTextureCoord(enum position pos, BlockID block) {
	if (block == RED) {
		struct uvCoord coord;
		if (pos == BL) {
			struct uvCoord coord = {0.0f, 2.0f / 3.0};
			return coord;
		}
		if (pos == BR) {
			struct uvCoord coord = {1.0f / 3.0f, 2.0f / 3.0f};
			return coord;
		}
		if (pos == TR) {
			struct uvCoord coord = {1.0f / 3.0f, 3.0f / 3.0f};
			return coord;
		}
		if (pos == TL) {
			struct uvCoord coord = {0.0f, 3.0f / 3.0f};
			return coord;
		}
	}
	if (block == GREEN) {
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
}
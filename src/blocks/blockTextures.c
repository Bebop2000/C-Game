#include "blockTextures.h"
#include "texture.h"
#include "stdio.h"

Texture defaultTexture;
Texture craftingTexture;
Texture roseTexture;
Texture grassTexture;
Texture floorTexture;
Texture greenTexture;
Texture atlasTexture;
Texture batTexture;

void blockTexturesInit() {
#ifdef linux
	const char* defTexture = "../res/textures/default.png";
	const char* table = "../res/textures/crafting_table.png";
	const char* rose =  "../res/textures/rose.png";
	const char* grass = "../res/textures/grass.png";
	const char* floor = "../res/textures/floor.png";
	const char* green = "../res/textures/green.png";
	const char* atlas = "../res/textures/atlas.png";
	const char* bat = "../res/textures/bat.png";
#else
	const char* defTexture = "C:/C-Game/res/textures/default.png";
	const char* table = "C:/C-Game/res/textures/crafting_table.png";
	const char* rose = "C:/C-Game/res/textures/rose.png";
	const char* grass = "C:/C-Game/res/textures/grass.png";
	const char* floor = "C:/C-Game/res/textures/floor.png";
	const char* green = "C:/C-Game/res/textures/green.png";
#endif
	loadTextureFromFile(&craftingTexture, table, 4);
	loadTextureFromFile(&roseTexture, rose, 4);
	loadTextureFromFile(&grassTexture, grass, 4);
	loadTextureFromFile(&floorTexture, floor, 4);
	loadTextureFromFile(&defaultTexture, defTexture, 4);
	loadTextureFromFile(&greenTexture, green, 4);
	loadTextureFromFile(&atlasTexture, atlas, 3);
	loadTextureFromFile(&batTexture, bat, 4);
}

unsigned int getBlockTexture(BlockID textureID) {
	if(textureID == DEFAULT_BLOCK)
		return defaultTexture.ID;
	if(textureID == CRAFTING_TABLE_BLOCK)
		return craftingTexture.ID;
	if(textureID == FLOOR)
		return floorTexture.ID;
	if(textureID == GREEN)
		return greenTexture.ID;
	if(textureID == BAT)
		return batTexture.ID;
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
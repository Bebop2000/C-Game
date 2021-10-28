#include "blockTextures.h"
#include "texture.h"
#include "stdio.h"

Texture defaultTexture;
Texture craftingTexture;
Texture roseTexture;
Texture grassTexture;
Texture floorTexture;
Texture greenTexture;

void blockTexturesInit() {
	const char* defTexture = "../src/game/sprites/default.png";
	const char* table = "../src/game/sprites/crafting_table.png";
	const char* rose =  "../src/game/sprites/rose.png";
	const char* grass = "../src/game/sprites/grass.png";
	const char* floor = "../src/game/sprites/floor.png";
	const char* green = "../src/game/sprites/green.png";
	loadTextureFromFile(&craftingTexture, table, 4);
	loadTextureFromFile(&roseTexture, rose, 4);
	loadTextureFromFile(&grassTexture, grass, 4);
	loadTextureFromFile(&floorTexture, floor, 4);
	loadTextureFromFile(&defaultTexture, defTexture, 4);
	loadTextureFromFile(&greenTexture, green, 4);
}

unsigned int getBlockTexture(BlockID textureID)
{
	if (textureID == DEFAULT_BLOCK)
		return defaultTexture.ID;
	if (textureID == CRAFTING_TABLE_BLOCK)
		return craftingTexture.ID;
	if (textureID == ROSE_BLOCK)
		return roseTexture.ID;
	if (textureID == FLOOR)
		return floorTexture.ID;
	if (textureID == GREEN)
		return greenTexture.ID;
}

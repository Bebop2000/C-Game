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
	const char* defTexture = "../res/textures/default.png";
	const char* table = "../res/textures/crafting_table.png";
	const char* rose =  "../res/textures/rose.png";
	const char* grass = "../res/textures/grass.png";
	const char* floor = "../res/textures/floor.png";
	const char* green = "../res/textures/green.png";
	loadTextureFromFile(&craftingTexture, table, 4);
	loadTextureFromFile(&roseTexture, rose, 4);
	loadTextureFromFile(&grassTexture, grass, 4);
	loadTextureFromFile(&floorTexture, floor, 4);
	loadTextureFromFile(&defaultTexture, defTexture, 4);
	loadTextureFromFile(&greenTexture, green, 4);
}

unsigned int getBlockTexture(BlockID textureID) {
	if(textureID == DEFAULT_BLOCK)
		return defaultTexture.ID;
	if(textureID == CRAFTING_TABLE_BLOCK)
		return craftingTexture.ID;
	if(textureID == ROSE_BLOCK)
		return roseTexture.ID;
	if(textureID == FLOOR)
		return floorTexture.ID;
	if(textureID == GREEN)
		return greenTexture.ID;
}

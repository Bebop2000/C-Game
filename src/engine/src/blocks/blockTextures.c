#include "blockTextures.h"
#include "texture.h"
#include "stdio.h"

Texture2D craftingTexture;
Texture2D roseTexture;
Texture2D grassTexture;
Texture2D floorTexture;

void blockTexturesInit() {
	const char* table = "../src/game/sprites/crafting_table.png";
	const char* rose =  "../src/game/sprites/rose.png";
	const char* grass = "../src/game/sprites/grass.png";
	const char* floor = "../src/game/sprites/floor.jpeg";
	loadTextureFromFile(&craftingTexture, table, 4);
	loadTextureFromFile(&roseTexture, rose, 4);
	loadTextureFromFile(&grassTexture, grass, 4);
	loadTextureFromFile(&floorTexture, floor, 4);
}

unsigned int getBlockTexture(BlockID textureID)
{
	if (textureID == DEFAULT_BLOCK)
		return 999;
	if (textureID == CRAFTING_TABLE_BLOCK)
		//printf("c\n");
		return craftingTexture.ID;
	if (textureID == ROSE_BLOCK)
		//printf("r\n");
		return roseTexture.ID;
	if (textureID == FLOOR)
		return floorTexture.ID;
}

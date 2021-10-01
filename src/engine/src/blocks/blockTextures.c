#include "blockTextures.h"
#include "texture.h"
#include "stdio.h"

Texture2D craftingTexture;
Texture2D roseTexture;
Texture2D grassTexture;


void blockTexturesInit() {
	const char* table = "../src/game/sprites/crafting_table.png";
	const char* rose =  "../src/game/sprites/rose.png";
	const char* grass = "../src/game/sprites/grass.png";
	loadTextureFromFile(&craftingTexture, table, 4);
	loadTextureFromFile(&roseTexture, rose, 4);
	loadTextureFromFile(&grassTexture, grass, 4);
}

unsigned int getBlockTexture(BlockID id)
{
	if (id == DEFAULT_BLOCK)
		return 999;
	if (id == CRAFTING_TABLE_BLOCK)
		//printf("c\n");
		return craftingTexture.ID;
	if (id == ROSE_BLOCK)
		//printf("r\n");
		return roseTexture.ID;
}
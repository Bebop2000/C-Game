#include "blockTextures.h"
#include "texture.h"
#include "stdio.h"

Texture2D craftingTexture;
Texture2D roseTexture;
Texture2D grassTexture;


void blockTexturesInit() {
	const char* table = "C:/projects/C version/C version/game/src/sprites/crafting_table.png";
	const char* rose = "C:/projects/C version/C version/game/src/sprites/rose.png";
	const char* grass = "C:/projects/C version/C version/game/src/sprites/grass.png";
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
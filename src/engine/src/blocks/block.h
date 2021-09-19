#pragma once
#include "core.h"

typedef enum BlockID
{
	DEFAULT_BLOCK,
	CRAFTING_TABLE_BLOCK,
	ROSE_BLOCK,
	GRASS_BLOCK
}BlockID;

typedef struct DefaultBlock {
	vec3 location;
	vec3 rotation;
	vec3 scale;
	unsigned int id;
}Block;

Block defaultBlockInit();
Block craftingTableBlockInit();
Block roseBlockInit();
Block grassBlockInit();
//void renderFlower(DefaultBlock);
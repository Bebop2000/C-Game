#pragma once
#include "core.h"

typedef enum BlockID
{
	DEFAULT_BLOCK,
	CRAFTING_TABLE_BLOCK,
	ROSE_BLOCK,
	GRASS_BLOCK,
	FLOOR,
	GREEN,
	AIR
}BlockID;

typedef struct DefaultBlock {
	vec3 location;
	vec3 rotation;
	vec3 scaleV;
	float scaleS;
	unsigned int textureID;
}Block;

Block defaultBlockInit();
Block craftingTableBlockInit();
Block roseBlockInit();
Block grassBlockInit();
Block floorInit();
Block greenInit();
//void renderFlower(DefaultBlock);
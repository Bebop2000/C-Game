#include "block.h"
#include "core.h"

const float DEFAULT_SCALE = 1.0f;

Block defaultBlockInit()
{
	Block temp = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DEFAULT_SCALE, DEFAULT_BLOCK };
	return temp;
}

Block craftingTableBlockInit()
{
	Block temp = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DEFAULT_SCALE, CRAFTING_TABLE_BLOCK };
	return temp;
}

Block roseBlockInit()
{
	Block temp = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DEFAULT_SCALE, ROSE_BLOCK };
	return temp;
}

Block grassBlockInit()
{
	Block temp = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, 1.0f, GRASS_BLOCK};
	return temp;
}

Block floorInit()
{
	Block temp = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, 100.0f, FLOOR};
	temp.textureID = FLOOR;
	return temp;
}
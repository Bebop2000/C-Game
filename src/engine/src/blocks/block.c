#include "block.h"
#include "core.h"

Block defaultBlockInit()
{
	Block temp = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, DEFAULT_BLOCK };
	return temp;
}

Block craftingTableBlockInit()
{
	Block temp = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, CRAFTING_TABLE_BLOCK };
	return temp;
}

Block roseBlockInit()
{
	Block temp = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, ROSE_BLOCK };
	return temp;
}

Block grassBlockInit()
{
	Block temp = { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }, GRASS_BLOCK};
	return temp;
}
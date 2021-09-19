#pragma once
#include "core.h"
#include "blocks/block.h"

typedef struct
{
	unsigned int VAO, VBO, EBO;
	int vertices;
}Mesh;

void renderBlock(Block block, unsigned int shaderProgram);
void renderQuad(Block block, unsigned int shaderProgram);
void renderFlower(Block block, unsigned int shaderProgram);
void cubeMeshInit();
void uniformCubeMeshInit();
void quadMeshInit();
void rendererInit();
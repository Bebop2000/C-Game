#ifndef RENDER_H
#define RENDER_H
#include "core.h"
#include "blocks/blockTextures.h"

typedef struct{
	unsigned int VAO, VBO, EBO;
	int vertices;
}Mesh;
void prepareCubeRender();
void prepareQuadRender();
void renderBlock(BlockID block, vec3 location, float scale, unsigned int shaderProgram);
void renderQuad(BlockID block, vec3 location, float scale, unsigned int shaderProgram);
//void renderFlower(Block block, unsigned int shaderProgram);
void bindQuadMesh();
void bindCubeMesh();
void cubeMeshInit();
void uniformCubeMeshInit();
void quadMeshInit();
void rendererInit();

#endif
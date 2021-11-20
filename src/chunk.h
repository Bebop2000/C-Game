#ifndef CHUNK_H
#define CHUNK_H
#include "core.h"
#include "blocks/block.h"

typedef struct{   
    //           x   z   y
    BlockID grid[16][16][256];
    int x;
    int z;
}Chunk;

Chunk generateChunk(int x, int y);
void renderChunk(Chunk chunk, unsigned int shaderProgram);
void chunkGenInit();

#endif
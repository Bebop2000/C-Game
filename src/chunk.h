#ifndef CHUNK_H
#define CHUNK_H
#include "core.h"
#include "blocks/block.h"
#define CHUNKX 64
#define CHUNKY 128
#define CHUNKZ 64

typedef struct{   
    //           x   z   y
    char grid[CHUNKX][CHUNKZ][CHUNKY];
    int x;
    int z;
}Chunk;

void generateChunk(Chunk *chunk, int x, int y);
void renderChunks(Chunk* chunk[], int size, unsigned int shaderProgram);
void chunkGenInit();

#endif
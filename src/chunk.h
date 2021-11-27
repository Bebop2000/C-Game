#ifndef CHUNK_H
#define CHUNK_H
#include "core.h"
#include "blocks/block.h"
#define CHUNKX 16
#define CHUNKY 128
#define CHUNKZ 16

typedef struct{
    Chunk *grid;
    int x, y;
}ChunkManager;

typedef struct{   
    //         x       y      z
    char grid[CHUNKX][CHUNKY][CHUNKZ];
    ChunkManager* manager;
    int x;
    int z;
}Chunk;

void chunkManagerInit(ChunkManager *cm);
void generateChunk(Chunk *chunk, ChunkManager *cm);
void renderChunks(Chunk* chunk[], int size, unsigned int shaderProgram);
void chunkGenInit();

#endif
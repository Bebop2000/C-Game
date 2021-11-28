#ifndef CHUNK_H
#define CHUNK_H
#include "core.h"
#include "blocks/block.h"
#define CHUNKX 16
#define CHUNKY 128
#define CHUNKZ 16

// For data:
// for each bit: 1=yes 0=no
// bit1: has been checked if visible
// bit2: is visible
typedef struct {
    byte blockID;
    byte data;
}Block;

typedef struct {
    Block grid[CHUNKX][CHUNKY][CHUNKZ];
    int x, y;
}Chunk;

typedef struct{
    //array of chunks
    Chunk** grid;
    int size;
}ChunkManager;

void generateChunk(ChunkManager* cm, int chunkx, int chunky);
void renderChunks(ChunkManager* cm, int i, int j, unsigned int shaderProgram);
void chunkGenInit();

#endif
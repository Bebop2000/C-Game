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
    float* mesh;    //array
    int* indices;
    int x, z;
    int vertices;
    int blockCount;
    int visibleBlockCount;
    int indiceCount;
    unsigned int VAO, VBO, EBO;
}Chunk;

typedef struct{
    //array of chunk pointers
    Chunk** chunks;
    int index;
    int size;
}ChunkManager;

void generateChunk(ChunkManager* cm, int chunkx, int chunky);
void prepareChunkMesh(Chunk* chunk);
void renderChunkMesh(Chunk* chunks, unsigned int shaderProgram);
void renderChunk(ChunkManager* cm, int i, unsigned int shaderProgram, mat4 frustum);
void printArrayFloat(float* array, int width, int size);
void printArrayInt(int* array, int width, int size);
void chunkGenInit();

#endif
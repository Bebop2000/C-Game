#ifndef CHUNK_H
#define CHUNK_H
#include "core.h"
#include "blocks/block.h"
#define CHUNKX 16
#define CHUNKY 128
#define CHUNKZ 16

typedef struct {
    byte blockID;
    byte checked : 1;
    byte allVisible : 1;
    byte topVisible : 1;
    byte bottomVisible : 1;
    byte leftVisible : 1;
    byte rightVisible : 1;
    byte frontVisible : 1;
    byte backVisible : 1;
}Block;

typedef struct {
    Block grid[CHUNKX][CHUNKY][CHUNKZ];
    int x, z;
    float* mesh;    //array
    int* indices;   //array
    int vertices;
    int indiceCount;
    int quads;
    int visibleBlockCount;
    unsigned int VAO, VBO, EBO;
}Chunk;

typedef struct{
    //array of chunk pointers
    Chunk** chunks;
    int index;
    int size;
}ChunkManager;

void generateChunk(ChunkManager* cm, int chunkx, int chunky);
void prepareChunkMesh(ChunkManager* cm, int index);
void renderChunkMesh(Chunk* chunks, unsigned int shaderProgram);
void renderChunk(ChunkManager* cm, int i, unsigned int shaderProgram, mat4 frustum);
void printArrayFloat(float* array, int width, int size);
void printArrayInt(int* array, int width, int size);
void chunkGenInit();
void checkChunkVisible(ChunkManager* cm, int index);

#endif
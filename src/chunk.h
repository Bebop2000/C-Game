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
    int index;
    struct Mesh{
        float* vertices;
        int verticeCount;
        int* indices;
        int indiceCount;
        unsigned int VAO, VBO, EBO;
    }mesh;
    bool needsPreparing : 1;
    bool needsBuffers : 1;
    int quads;
}Chunk;

typedef struct{
    //array of chunk pointers
    Chunk** chunks;
    int index;
    int size;
}ChunkManager;

void chunkGenInit();
void freeChunkManager(ChunkManager cm);
void generateChunk(ChunkManager* cm, int chunkx, int chunky);
Chunk* getChunk(ChunkManager* cm, int x, int z);
void checkChunkVisible(ChunkManager* cm, Chunk* chunk);
void createChunkBuffers(Chunk* chunk);
void prepareChunkMesh(Chunk* chunk);
void renderChunkMesh(Chunk* chunks, unsigned int shaderProgram);
void TEST(ChunkManager* cm, int index);

void printArrayFloat(float* array, int width, int size);
void printArrayInt(int* array, int width, int size);

#endif
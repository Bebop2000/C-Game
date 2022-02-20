#ifndef CHUNK_H
#define CHUNK_H
#include "core.h"
#include "blocks/block.h"
#define CHUNKX 16
#define CHUNKY 128
#define CHUNKZ 16

typedef struct {
    byte blockID;
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
    int index;      //index of chunk in the chunkManager
    struct Mesh{
        float* vertices;
        int verticeCount;
        int* indices;
        int indiceCount;
        unsigned int VAO, VBO, EBO;
    }mesh;
    bool hasMesh : 1;
    bool hasBuffers : 1;
    int quads;
}Chunk;

typedef struct{
    Chunk** chunks;     //array of chunk pointers -> Chunk* chunk[...]
    int nextIndex;      //index of the next chunk to be added
    int size;           //number of chunks allocated in memory
}ChunkManager;

void chunkGenInit();
void freeChunkMesh(Chunk* chunk);
void freeChunkGrid(Chunk* chunk);
void freeChunkManager(ChunkManager cm);
void generateChunk(ChunkManager* cm, int chunkx, int chunky);
void regenerateChunkTerrain(Chunk* chunk);
Chunk* getChunk(ChunkManager* cm, int x, int z);
void checkChunkVisible(ChunkManager* cm, Chunk* chunk);
void createChunkBuffers(Chunk* chunk);
void prepareChunkMesh(Chunk* chunk);
void renderChunkMesh(Chunk* chunks, unsigned int shaderProgram, mat4 frustum);

void printArrayFloat(float* array, int width, int size);
void printArrayInt(int* array, int width, int size);

#endif
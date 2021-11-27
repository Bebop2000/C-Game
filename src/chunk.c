#include "core.h"
#include "chunk.h"
#include "blocks/block.h"
#include "render.h"

void chunkGenInit(){
    srand(glfwGetTime());
}

void chunkManagerInit(ChunkManager *cm) {
    cm = malloc(625 * sizeof(Chunk));
}

void chunkManagerFree(ChunkManager *cm) {
    free(cm);
}

void generateChunk(Chunk *chunk, ChunkManager *cm) {
    if (chunk == NULL) {
        printf("Chunk failed to allocate memory\n");
        return;
    }

    for(int x=0; x < CHUNKX; x++) {
        for(int y=0; y < CHUNKY; y++) {
            for(int z=0; z < CHUNKZ; z++) {
                if(y < 50) {
                    // pick block for location
                    char block = rand() % 5;
                    if (block == AIR) {
                        int w = rand() % 10;
                        if (w == 3) {
                            block = AIR;
                        }
                        else {
                            block = GREEN;
                        }
                    }
                    chunk->grid[x][y][z] = block;
                }
                else{
                    chunk->grid[x][y][z] = AIR;
                }
            }
        }
    }
    chunk->x = chunkX;
    chunk->z = chunkZ;
}

void renderChunks(Chunk *chunks[], int size, unsigned int shaderProgram) {
    prepareCubeRender();
    for (int c = 0; c < size; c++) {
        Chunk *chunk = chunks[c];
        for (int x = 0; x < CHUNKX; x++) {
            for (int y = 0; y < CHUNKY; y++) {
                for (int z = 0; z < CHUNKZ; z++) {
                    char block = chunk->grid[x][y][z];
                    bool shouldRender = false;
                    //if the block is next to an air block it will be rendered
                    if (block != AIR && y < 50) {
                        if (z!=0) {
                            if (chunks[c]->grid[x][y][z-1] == AIR) {
                                shouldRender = true;
                            }
                        }
                        if (z != CHUNKZ-1) {
                            if (chunks[c]->grid[x][y][z+1] == AIR) {
                                shouldRender = true;
                            }
                        }
                        if (x != 0) {
                            if (chunks[c]->grid[x - 1][y][z] == AIR) {
                                shouldRender = true;
                            }
                        }
                        if (x != CHUNKX-1) {
                            if (chunks[c]->grid[x + 1][y][z] == AIR) {
                                shouldRender = true;
                            }
                        }
                        if (y != 0) {
                            if (chunks[c]->grid[x][y-1][z] == AIR) {
                                shouldRender = true;
                            }
                        }
                        if (y != CHUNKY-1) {
                            if (chunks[c]->grid[x][y+1][z] == AIR) {
                                shouldRender = true;
                            }
                        }
                        if (x == 0 || x == CHUNKX-1 || 
                        z == 0 || z == CHUNKZ-1 || 
                        y == 0 || y == CHUNKY-1) {
                            shouldRender = true;
                        }
                        if (x == 0) {
                            
                        }


                        if (shouldRender) {
                            vec3 loc = { (chunks[c]->x * CHUNKX*2 + 2 * x),
                                         (2 * y), 
                                         (chunks[c]->z * CHUNKZ*2 + 2 * z) };
                            renderBlock(block, loc, 1.0f, shaderProgram);
                        }
                    }
                }
            }
        }
    }
}
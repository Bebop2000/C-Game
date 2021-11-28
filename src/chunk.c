#include "core.h"
#include "chunk.h"
#include "blocks/block.h"
#include "render.h"

void chunkGenInit(){
    srand(glfwGetTime());
}

void generateChunk(ChunkManager* cm, int chunkx, int chunky) {
    Chunk* chunk = malloc(sizeof(Chunk));
    if (chunk == NULL) {
        printf("Chunk %i, %i, failed to allocate memory\n", chunkx, chunky);
        return;
    }
    else {
        chunk->x = chunkx;
        chunk->y = chunky;
        for (int x = 0; x < CHUNKX; x++) {
            for (int y = 0; y < CHUNKY; y++) {
                for (int z = 0; z < CHUNKZ; z++) {
                    chunk->grid[x][y][z].data = 0x0;
                    if (y < 50) {
                    // pick block for location
                        char block = rand() % 5;
                        if (block == AIR) {
                            int w = rand() % 10;
                            if (w == 3) {
                                block = GREEN;
                            }
                            else {
                                block = GREEN;
                            }
                        }
                        chunk->grid[x][y][z].blockID = block;
                    }
                    else {
                        chunk->grid[x][y][z].blockID = AIR;
                    }
                }
            }
        }
        //
        for (int x = 0; x < CHUNKX; x++) {
            for (int y = 0; y < CHUNKY; y++) {
                for (int z = 0; z < CHUNKZ; z++) {
                    // if block isn't on the edge of the chunk
                    byte tmpdata = 0x00; // tmpdata -> 00000000(b)
                    if (x != 0 && x != CHUNKX - 1 &&
                        z != 0 && z != CHUNKZ - 1 &&
                        y != 0 && y != CHUNKY - 1) {
                        bool shouldRender = false;
                        if (chunk->grid[x][y][z - 1].blockID == AIR) {
                            shouldRender = true;
                        }
                        if (chunk->grid[x][y][z + 1].blockID == AIR) {
                            shouldRender = true;
                        }
                        if (chunk->grid[x - 1][y][z].blockID == AIR) {
                            shouldRender = true;
                        }
                        if (chunk->grid[x + 1][y][z].blockID == AIR) {
                            shouldRender = true;
                        }
                        if (chunk->grid[x][y - 1][z].blockID == AIR) {
                            shouldRender = true;
                        }
                        if (chunk->grid[x][y + 1][z].blockID == AIR) {
                            shouldRender = true;
                        }

                        tmpdata = tmpdata | BIT1; // set bit1 to 1
                        // tmpdata -> 00000001(b)
                        if (shouldRender) {
                            tmpdata = tmpdata | BIT2; // set bit 2 to 1
                            // tmpdata -> 00000011(b)
                        }
                        chunk->grid[x][y][z].data = tmpdata;
                    }
                }
            }
        }
        cm->grid[chunkx][chunky] = chunk;
    }
}

void renderChunks(ChunkManager* cm, int i, int j, unsigned int shaderProgram) {
    prepareCubeRender();
    for (int a = 0; a < i; a++) {
        for (int b = 0; b < i; b++) {
            Chunk* chunk = cm->grid[a][b];
            for (int x = 0; x < CHUNKX; x++) {
                for (int y = 0; y < CHUNKY; y++) {
                    for (int z = 0; z < CHUNKZ; z++) {
                        char block = chunk->grid[x][y][z].blockID;
                        if (block != AIR) {
                            //if the block is next to an air block it will be rendered
                            bool shouldRender = false;
                            if (chunk->grid[x][y][z].data & 1) {    //if the block's neighbors have been checked before
                                if (chunk->grid[x][y][z].data & (1 << 1)) {     //if the block is visible
                                    shouldRender = true;
                                }
                            }
                            else {      //check the block's neighbors
                                if (z != 0) {
                                    if (chunk->grid[x][y][z - 1].blockID == AIR) {
                                        shouldRender = true;
                                    }
                                }
                                if (z != CHUNKZ - 1) {
                                    if (chunk->grid[x][y][z + 1].blockID == AIR) {
                                        shouldRender = true;
                                    }
                                }
                                if (x != 0) {
                                    if (chunk->grid[x - 1][y][z].blockID == AIR) {
                                        shouldRender = true;
                                    }
                                }
                                if (x != CHUNKX - 1) {
                                    if (chunk->grid[x + 1][y][z].blockID == AIR) {
                                        shouldRender = true;
                                    }
                                }
                                if (y != 0) {
                                    if (chunk->grid[x][y - 1][z].blockID == AIR) {
                                        shouldRender = true;
                                    }
                                }
                                if (y != CHUNKY - 1) {
                                    if (chunk->grid[x][y + 1][z].blockID == AIR) {
                                        shouldRender = true;
                                    }
                                }

                                if (x == 0) {
                                    Chunk* nextChunk = cm->grid[a][b];
                                }

                                chunk->grid[x][y][z].data = chunk->grid[x][y][z].data | BIT1;
                                if (shouldRender) {
                                    chunk->grid[x][y][z].data = chunk->grid[x][y][z].data | BIT2;           // sets bit2 to 1
                                }
                                else {
                                    chunk->grid[x][y][z].data = chunk->grid[x][y][z].data & (BIT2 ^ 0xFF);  // sets bit2 to 0
                                }
                            }
                            if (shouldRender) {
                                vec3 loc = { (a * CHUNKX * 2 + 2 * x),
                                             (2 * y),
                                             (b * CHUNKZ * 2 + 2 * z) };
                                renderBlock(block, loc, 1.0f, shaderProgram);
                            }
                        }
                    }
                }
            }
        }
    }
}


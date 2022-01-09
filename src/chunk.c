#include "core.h"
#include "chunk.h"
#include "blocks/block.h"
#include "render.h"
#include "noise.h"
#include "../vendor/cglm/box.h"
#include "../vendor/cglm/frustum.h"

void chunkGenInit(){
    srand(glfwGetTime());
}

void generateChunk(ChunkManager* cm, int chunkx, int chunkz) {
    Chunk* chunk = malloc(sizeof(Chunk));
    if (chunk == NULL) {
        printf("Chunk %i, %i, failed to allocate memory\n", chunkx, chunkz);
        return;
    }
    else {
        chunk->x = chunkx;
        chunk->z = chunkz;
        
        //int noise[16][16];
        /*
        for(int x=0; x < CHUNKX; x++) {
            for(int z=0; z<CHUNKZ; z++) {
                noise[x][z] = (int)(perlin2d(x+chunkx*CHUNKX, z+chunkz*CHUNKZ, 0.003, 10) * 100);
                if(noise[x][z] > 127 || noise[x][z] < 0){
                    noise[x][z] = 127;
                }


                //printf("%i\n", noise2d[x][z]);
            }
        }*/
        
       
       /*
        int noise3d[16][64][16];
        for(int x=0; x< CHUNKX; x++) {
            for(int y=0; y<CHUNKY; y++) {
                for(int z=0; z<CHUNKZ; z++) {
                    noise3d[x][y][z] = noise3(x, y, z);
                }
            }
        }
        */

        for(int x=0; x < CHUNKX; x++) {
            for(int y=0; y<CHUNKY; y++) {
                for(int z=0; z<CHUNKZ; z++) {
                    //int height = noise[x][z];
                    //printf("%i\n", height);
                    //if(height == y){
                    //    chunk->grid[x][y][z].blockID = GREEN;
                    //}
                    //else {
                    //    chunk->grid[x][y][z].blockID = AIR;
                    // }

                    float value = noise3((float)x+chunkx*CHUNKX, (float)y, (float)z+chunkz*CHUNKZ);
                    //printf("%f\n", value);
                    if (value < 0.5) {
                        chunk->grid[x][y][z].blockID = AIR;
                    }
                    else {
                        chunk->grid[x][y][z].blockID = GREEN;
                    }
                }
            }
        }
        /*
        for (int x = 0; x < CHUNKX; x++) {
            for (int y = 0; y < CHUNKY; y++) {
                for (int z = 0; z < CHUNKZ; z++) {
                    chunk->grid[x][y][z].data = 0x0;
                    if (y < 70) {
                    // pick block for location
                        char block = rand() % 5;
                        if (block == AIR) {
                            int w = rand() % 200;
                            if (w == 3) {
                                block = AIR;
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
        */
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
        cm->chunks[cm->index] = chunk;
        //printf("%i\n", cm->index);
        cm->index++;
    }
}

void renderChunk(ChunkManager* cm, int i, unsigned int shaderProgram, mat4 frustum) {
    prepareCubeRender();
    vec4 planes[6];
    glm_frustum_planes(frustum, planes);
    for (int c = 0; c < i; c++) {
        Chunk* chunk = cm->chunks[c];
        if (chunk == NULL) {
            return;
        }
        int blockCount = 0;
        for (int x = 0; x < CHUNKX; x++) {
            for (int y = 0; y < CHUNKY; y++) {
                for (int z = 0; z < CHUNKZ; z++) {
                    char block = chunk->grid[x][y][z].blockID;
                    if (block != AIR) {
                        //if the block is next to an air block it will be rendered
                        bool shouldRender = false;
                        // width of a cube is 2 idk why
                        vec3 box[2] = { { 2*(chunk->x*CHUNKX + x),    y * 2,     2*(chunk->z*CHUNKZ + z)}, 
                                        { 2*(chunk->x*CHUNKX + x)+ 2, y * 2 + 2, 2*(chunk->z*CHUNKZ+ z) + 2} };

                        if (chunk->grid[x][y][z].data & 1) {    //if the block's neighbors have been checked before
                            if (chunk->grid[x][y][z].data & (1 << 1)) {     //if the block is visible
                                if (glm_aabb_frustum(box, planes)) {
                                    shouldRender = true;
                                }
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

                            //
                            if (x == 0) {
                                Chunk* nextChunk = NULL;
                                for (int i = 0; i < cm->size; i++) {
                                    if (cm->chunks[i] != NULL) {
                                        //printf("%i, %i\n", cm->chunks[i]->x, cm->chunks[i]->z);
                                        //printf("%i, %i\n", chunk->x, chunk->z);
                                        if (cm->chunks[i]->x == (chunk->x) - 1 && cm->chunks[i]->z == chunk->z) {
                                            //printf("testzn");
                                            nextChunk = cm->chunks[i];
                                        }
                                    }
                                }
                                if (nextChunk == NULL) {
                                    generateChunk(cm, chunk->x - 1, chunk->z);
                                }
                                else {
                                    if (nextChunk->grid[CHUNKX - 1][y][z].blockID == AIR) {
                                        shouldRender = true;
                                    }
                                }
                            }

                            if (x == CHUNKX-1) {
                                Chunk* nextChunk = NULL;
                                for (int i = 0; i < cm->size; i++) {
                                    if (cm->chunks[i] != NULL) {
                                        //printf("%i, %i\n", cm->chunks[i]->x, cm->chunks[i]->z);
                                        //printf("%i, %i\n", chunk->x, chunk->z);
                                        if (cm->chunks[i]->x == chunk->x + 1 && cm->chunks[i]->z == chunk->z) {
                                            //printf("testzn");
                                            nextChunk = cm->chunks[i];
                                        }
                                    }
                                }
                                if (nextChunk == NULL) {
                                    generateChunk(cm, chunk->x + 1, chunk->z);
                                }
                                else {
                                    if (nextChunk->grid[0][y][z].blockID == AIR) {
                                        shouldRender = true;
                                    }
                                }
                            }

                            //
                            if (z == 0) {
                                Chunk* nextChunk = NULL;
                                for (int i = 0; i < cm->size; i++) {
                                    if (cm->chunks[i] != NULL) {
                                        //printf("%i, %i\n", cm->chunks[i]->x, cm->chunks[i]->z);
                                        //printf("%i, %i\n", chunk->x, chunk->z);
                                        if (cm->chunks[i]->x == (chunk->x) && cm->chunks[i]->z == chunk->z - 1) {
                                            //printf("testzn");
                                            nextChunk = cm->chunks[i];
                                        }
                                    }
                                }
                                if (nextChunk == NULL) {
                                    generateChunk(cm, chunk->x, chunk->z - 1);
                                }
                                else {
                                    if (nextChunk->grid[x][y][CHUNKZ - 1].blockID == AIR) {
                                        shouldRender = true;
                                    }
                                }
                            }

                            if (z == CHUNKZ - 1) {
                                Chunk* nextChunk = NULL;
                                for (int i = 0; i < cm->size; i++) {
                                    if (cm->chunks[i] != NULL) {
                                        //printf("%i, %i\n", cm->chunks[i]->x, cm->chunks[i]->z);
                                        //printf("%i, %i\n", chunk->x, chunk->z);
                                        if (cm->chunks[i]->x == chunk->x && cm->chunks[i]->z == chunk->z + 1) {
                                            //printf("testzn");
                                            nextChunk = cm->chunks[i];
                                        }
                                    }
                                }
                                if (nextChunk == NULL) {
                                    generateChunk(cm, chunk->x, chunk->z + 1);
                                }
                                else {
                                    if (nextChunk->grid[x][y][0].blockID == AIR) {
                                        shouldRender = true;
                                    }
                                }
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
                            if (glm_aabb_frustum(box, planes)) {
                                vec3 loc = { (chunk->x * CHUNKX * 2 + 2 * x),
                                             (2 * y),
                                             (chunk->z * CHUNKZ * 2 + 2 * z) };
                                renderBlock(block, loc, 1.0f, shaderProgram);
                            }
                        }
                    }
                }
            }
        }
        //printf("%i\n", blockCount);
    }
}


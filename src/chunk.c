#include "core.h"
#include "chunk.h"
#include "blocks/block.h"
#include "render.h"

void chunkGenInit(){
    srand(glfwGetTime());
}

Chunk generateChunk(int chunkX, int chunkZ) {
    Chunk test;
    for(int x=0; x < 16; x++) {
        for(int z=0; z < 16; z++) {
            for(int y=0; y < 128; y++) {
                if(y < 10) {
                    test.grid[x][z][y] = rand() % 2;
                }
                else{
                    test.grid[x][z][y] = AIR;
                }
            }
        }
    }
    test.x = chunkX;
    test.z = chunkZ;
    return test;
}

void renderChunk(Chunk chunk, unsigned int shaderProgram) {
    prepareCubeRender();
    for(int x=0; x<16; x++){
        for(int z=0; z<16; z++){
            for(int y=0; y<256; y++){
                BlockID block = chunk.grid[x][z][y];
                if(block != AIR && y < 10){
                    if(y > 255 || chunk.grid[x][z][y+1] == AIR
                    || x < 1 || z < 1){
                        vec3 loc = {chunk.x*32+2*x, 2*y, chunk.z*32+2*z};
                        renderBlock(block, loc, 1.0f, shaderProgram);
                    }
                }
            }
        }
    }
}
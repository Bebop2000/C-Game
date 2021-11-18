#include "core.h"
#include "chunk.h"
#include "blocks/block.h"
Chunk generateChunk() {
    Chunk test;
    for(int x=0; x < 16; x++) {
        for(int z=0; z < 16; z++) {
            for(int y=0; y < 128; y++) {
                if(y < 50) {
                    test.grid[x][z][y] = CRAFTING_TABLE_BLOCK;
                }
                else{
                    test.grid[x][z][y] = AIR;
                }
            }
        }
    }
    return test;
}
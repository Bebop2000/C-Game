#ifndef CHUNK_H
#define CHUNK_H
#include "core.h"
#include "blocks/block.h"

struct chunk{   
    //           x   z   y
    BlockID grid[16][16][256];
};

typedef struct chunk Chunk;

Chunk generateChunk();

#endif
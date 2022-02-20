#include "core.h"
#include "chunk.h"
#include "render.h"
#include "noise.h"
#include "scenes/testScene.h"
#include "blocks/blockTextures.h"
#include "../vendor/cglm/box.h"
#include "../vendor/cglm/frustum.h"


const float frontFace[] = {
        -0.5f, -0.5f, -0.5f, 0.5f, 0.5f,	//bottom left		0
         0.5f, -0.5f, -0.5f, 1.0f, 0.5f,	//bottom right		1
         0.5f,	0.5f, -0.5f, 1.0f, 1.0f,	//top right			2
        -0.5f,  0.5f, -0.5f, 0.5f, 1.0f,	//top left			3
};
const float backFace[] = {
         0.5f, -0.5f, 0.5f, 0.0f, 0.0f,		//bottom left		4
        -0.5f, -0.5f, 0.5f, 0.5f, 0.0f,		//bottom right		5
        -0.5f,	0.5f, 0.5f, 0.5f, 0.5f,		//top right			6
         0.5f,  0.5f, 0.5f, 0.0f, 0.5f,		//top left			7
};
const float leftFace[] = {
        -0.5f, -0.5f,  0.5f, 0.0f, 0.0f,	// 8
        -0.5f, -0.5f, -0.5f, 0.5f, 0.0f,	// 9
        -0.5f,  0.5f, -0.5f, 0.5f, 0.5f,	// 10
        -0.5f,	0.5f,  0.5f, 0.0f, 0.5f,	// 11
};
const float rightFace[] = {
         0.5f, -0.5f, -0.5f, 0.0f, 0.0f,	//12
         0.5f, -0.5f,  0.5f, 0.5f, 0.0f,	//13
         0.5f,  0.5f,  0.5f, 0.5f, 0.5f,	//14
         0.5f,  0.5f, -0.5f, 0.0f, 0.5f,	//15
};
const float topFace[] = {
        -0.5f,  0.5f, -0.5f, 0.0f, 0.5f,	//16
         0.5f,  0.5f, -0.5f, 0.5f, 0.5f,	//17
         0.5f,  0.5f,  0.5f, 0.5f, 1.0f,	//18
        -0.5f,  0.5f,  0.5f, 0.0f, 1.0f,	//19
};
const float bottomFace[] = {
        -0.5f, -0.5f, -0.5f, 0.5f, 0.0f,
         0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
         0.5f, -0.5f,  0.5f, 1.0f, 0.5f,
        -0.5f, -0.5f,  0.5f, 0.5f, 0.5f,
};

void terrainGen(Chunk* chunk);

//to free chunk, call freeChunkMesh, then freeChunkGrid in that order

void freeChunkMesh(Chunk* chunk) {
    if(chunk != NULL && chunk->hasBuffers){
        glDeleteBuffers(1, &(chunk->mesh.VBO));
        glDeleteBuffers(1, &(chunk->mesh.EBO));
        glDeleteVertexArrays(1, &(chunk->mesh.VAO));
    }
    if(chunk != NULL && chunk->hasMesh) {
        free(chunk->mesh.vertices);
        free(chunk->mesh.indices);
    }
}

void freeChunkGrid(Chunk* chunk) {
    if(chunk != NULL) {
        free(chunk);
    }
}

void freeChunkManager(ChunkManager cm) {
    printf("Freeing ChunkManager\n");
    for (int c = 0; c < cm.nextIndex; c++) {
        Chunk* chunk = cm.chunks[c];
        if (chunk != NULL) {
            freeChunkMesh(chunk);
            freeChunkGrid(chunk);
        }
    }
    free(cm.chunks);
}

void regenerateChunkTerrain(Chunk* chunk) {
    freeChunkMesh(chunk);
    chunk->quads = 0;
    chunk->hasBuffers = 0;
    chunk->hasMesh = 0;
    chunk->mesh.indiceCount = 0;
    chunk->mesh.verticeCount = 0;
    chunk->mesh.vertices = NULL;
    chunk->mesh.indices = NULL;
    int chunkx = chunk->x;
    int chunkz = chunk->z;
    terrainGen(chunk);
}

void checkChunkVisible(ChunkManager* cm, Chunk* chunk);
Chunk* getChunk(ChunkManager* cm, int x, int z);

void chunkGenInit(){
    srand(5);
}
void setBlockDefault(Block* block) {
    block->topVisible = 0;
    block->bottomVisible = 0;
    block->leftVisible = 0;
    block->rightVisible = 0;
    block->frontVisible = 0;
    block->backVisible = 0;
    block->blockID = AIR_BLOCK;
}

void generateChunk(ChunkManager* cm, int chunkx, int chunkz) {
    //printf("Allocating memory\n");
    if (cm == NULL) {
        printf("ERROR: Null chunk manager\n");
        return;
    }
    if (cm->nextIndex == cm->size - 1) {
        cm->size += 500;
		Chunk** temp = realloc(cm->chunks, cm->size * sizeof(Chunk));
        printf("Allocating more chunk memory\n");
		if (temp == NULL) {
			printf("Error reallocating %zu bytes of memory for chunkManager.chunks\n", cm->size * sizeof(Chunk*));
		}
        else {
            cm->chunks = temp;
        }
	}
    
    Chunk* chunk = malloc(sizeof(Chunk));
    if (chunk == NULL) {
        printf("\tChunk %i, %i, failed to allocate memory\n", chunkx, chunkz);
        return;
    }
    else {
        chunk->x = chunkx;
        chunk->z = chunkz;
        chunk->index = cm->nextIndex;
        chunk->quads = 0;
        chunk->hasBuffers = 0;
        chunk->hasMesh = 0;
        chunk->mesh.indiceCount = 0;
        chunk->mesh.verticeCount = 0;
        chunk->mesh.vertices = NULL;
        chunk->mesh.indices = NULL;
        terrainGen(chunk);
    }
    cm->chunks[cm->nextIndex++] = chunk;
}
void terrainGen(Chunk* chunk) {
    int chunkx = chunk->x;
    int chunkz = chunk->z;
    for (int x = 0; x < CHUNKX; x++) {
        for (int y = 0; y < CHUNKY; y++) {
            for (int z = 0; z < CHUNKZ; z++) {
                if (chunkx < 0 || chunkz < 0) {
                    chunk->grid[x][y][z].blockID = AIR_BLOCK;
                }
                else {
                    chunk->grid[x][y][z].blockID = AIR_BLOCK;
                }
                chunk->grid[x][y][z].topVisible = 0;
                chunk->grid[x][y][z].bottomVisible = 0;
                chunk->grid[x][y][z].leftVisible = 0;
                chunk->grid[x][y][z].rightVisible = 0;
                chunk->grid[x][y][z].frontVisible = 0;
                chunk->grid[x][y][z].backVisible = 0;
                if (y == 1) {
                    chunk->grid[x][y][z].blockID = GRASS_BLOCK;
                }
            }
        }
    }
    for (int x = 0; x < CHUNKX; x++) {
        for (int z = 0; z < CHUNKZ; z++) {
            int height = (int)(perlin2d(abs(x + chunkx * CHUNKX), abs(z + chunkz * CHUNKZ), 0.005, 10) * 100 + 20);
            if (height > CHUNKY - 2) {
                height = CHUNKY - 2;
            }
            if (height < 0) {
                height = 0;
            }
            chunk->grid[x][height][z].blockID = GRASS_BLOCK;
            for (int y = height; y > 0; y--) {
                if (height - y < 10) {
                    chunk->grid[x][y][z].blockID = DIRT_BLOCK;
                }
                else {
                    float value = pnoise3((float)(abs(x + chunkx * CHUNKX)) / 25.0f, (float)y / 25.0f, (float)(abs(z + chunkz * CHUNKZ)) / 25.0f, 200, 200, 200);
                    if (value < 0.2) {
                        chunk->grid[x][y][z].blockID = STONE_BLOCK;
                    }
                }
            }
        }
    }
}
Chunk* getChunk(ChunkManager* cm, int x, int z) {
    for(int i = 0; i < cm->nextIndex; i++) {
        if (cm->chunks[i]->x == x && cm->chunks[i]->z == z) {
            return cm->chunks[i];
        }
    }
    generateChunk(cm, x, z);
    if(cm->chunks[cm->nextIndex - 1] == NULL) {
        printf("Error getting chunk %i %i\n", x, z);
    }
    return cm->chunks[cm->nextIndex-1];
}

void checkChunkVisible(ChunkManager* cm, Chunk* chunk) {
    if (chunk == NULL) {
        printf("ERROR: Attemped to check null chunk mesh\n");
    }
    Chunk* leftChunk = getChunk(cm, chunk->x-1, chunk->z);
    if(leftChunk == NULL) {
        printf("\tError retrieving chunk %i %i\n", chunk->x-1, chunk->z);
    }
    Chunk* rightChunk = getChunk(cm, chunk->x+1, chunk->z);
    if(rightChunk == NULL) {
        printf("\tError retrieving chunk %i %i\n", chunk->x+1, chunk->z);
    }
    Chunk* backChunk = getChunk(cm, chunk->x, chunk->z-1);
    if(backChunk == NULL) {
        printf("\tError retrieving chunk %i %i\n", chunk->x, chunk->z-1);
    }
    Chunk* frontChunk = getChunk(cm, chunk->x, chunk->z+1);
    if(frontChunk == NULL) {
        printf("\tError retrieving chunk %i %i\n", chunk->x, chunk->z+1);
    }
    int visibleCount = 0;
    for (int x = 0; x < CHUNKX; x++) {
        for (int y = 0; y < CHUNKY; y++) {
            for ( int z = 0; z < CHUNKZ; z++) {
                if (chunk->grid[x][y][z].blockID != AIR_BLOCK) 
                {
                    bool shouldRender = false;
                     if (x == 0) {
                        if (leftChunk->grid[CHUNKX-1][y][z].blockID == AIR_BLOCK) {
                            chunk->grid[x][y][z].leftVisible = 1;
                            chunk->quads++;
                        }
                    }
                    if (x == CHUNKX - 1) {
                        if (rightChunk->grid[0][y][z].blockID == AIR_BLOCK) {
                            chunk->grid[x][y][z].rightVisible = 1;
                            chunk->quads++;
                        }
                    }
                    if (x !=0) {
                        if (chunk->grid[x-1][y][z].blockID == AIR_BLOCK) {
                            chunk->grid[x][y][z].leftVisible = 1;
                            chunk->quads++;
                        }                        }
                    if (x != CHUNKX - 1) {
                        if (chunk->grid[x+1][y][z].blockID == AIR_BLOCK) {
                            chunk->grid[x][y][z].rightVisible = 1;
                            chunk->quads++;
                        }
                    }                        
                    if (y == 0) {
                        chunk->grid[x][y][z].bottomVisible = 1;
                        if (chunk->grid[x][y+1][z].blockID == AIR_BLOCK) {
                            chunk->grid[x][y][z].topVisible = 1;
                            chunk->quads++;
                            shouldRender = true;
                        }
                    }
                    if (y == CHUNKY - 1) {
                        chunk->grid[x][y][z].topVisible = 1;
                        chunk->quads++;
                        shouldRender = true;
                    }
                    if (y != 0) {
                        if (chunk->grid[x][y-1][z].blockID == AIR_BLOCK) {
                        chunk->grid[x][y][z].bottomVisible = 1;
                            chunk->quads++;
                        }
                    }
                    if (y != CHUNKY - 1) {
                        if (chunk->grid[x][y+1][z].blockID == AIR_BLOCK) {
                            chunk->grid[x][y][z].topVisible = 1;
                            chunk->quads++;
                        }
                    }
                    if (z == 0) {
                        if (backChunk->grid[x][y][CHUNKZ-1].blockID == AIR_BLOCK) {
                            chunk->grid[x][y][z].frontVisible = 1;
                            chunk->quads++;
                            shouldRender = true;
                        }
                    }
                    if (z == CHUNKZ - 1) {
                        if (frontChunk->grid[x][y][0].blockID == AIR_BLOCK) {
                            chunk->grid[x][y][z].backVisible = 1;
                            chunk->quads++;
                            shouldRender = true;
                        }
                    }
                    if (z != 0) {
                        if (chunk->grid[x][y][z-1].blockID == AIR_BLOCK) {
                                chunk->grid[x][y][z].frontVisible = 1;
                            chunk->quads++;
                        }
                    }
                    if (z != CHUNKZ - 1) {
                        if (chunk->grid[x][y][z+1].blockID == AIR_BLOCK) {
                            chunk->grid[x][y][z].backVisible = 1;
                            chunk->quads++;
                        }
                    }
                }
            }
        }
    }
}

void createChunkBuffers(Chunk* chunk) {
    glGenVertexArrays(1, &(chunk->mesh.VAO));
	glGenBuffers(1, &(chunk->mesh.VBO));
    glGenBuffers(1, &(chunk->mesh.EBO));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void prepareChunkMesh(Chunk* chunk) {
    if (chunk == NULL) {
        printf("ERROR: Attemped to prepare null chunk\n");
    }
    if(chunk->quads < 1) {
        printf("ERROR: Zero quads to prepare\n");
    }
    chunk->mesh.vertices = (float*)calloc(chunk->quads*4*5, sizeof(float));
    chunk->mesh.indices = (int*)calloc(chunk->quads*6, sizeof(int));
    if (chunk->mesh.vertices == NULL) {
        printf("ERROR calloc to chunk->mesh\n");
        return;
    }
    if (chunk->mesh.indices == NULL) {
        printf("ERROR calloc to chunk->indices\n");
        return;
    }
    int i = 0;
    int j = 0;
    int quads = 0;
    int num = 6;
    float atlasWidth = 3;
    float atlasHeight = 3;
    for(int x = 0; x < CHUNKX; x++) {
        for (int y = 0; y < CHUNKY; y++) {
            for (int z = 0; z < CHUNKZ; z++) {
                Block block = chunk->grid[x][y][z];
                if (block.blockID != AIR_BLOCK) {
                    BlockSides sides = getBlockSides(block.blockID);
                    if (block.frontVisible) {
                        for (int a = 0; a < 4; a++) {
                            chunk->mesh.vertices[i++] = frontFace[a*5 + 0] + x;
                            chunk->mesh.vertices[i++] = frontFace[a*5 + 1] + y;
                            chunk->mesh.vertices[i++] = frontFace[a*5 + 2] + z;
                            struct uvCoord coord;
                            if (a == 0) {
                                coord = getTextureCoord(sides.front, BL);
                            }
                            if (a == 1) {
                                coord = getTextureCoord(sides.front, BR);
                            }
                            if (a == 2) {
                                coord = getTextureCoord(sides.front, TR);
                            }
                            if (a == 3) {
                                coord = getTextureCoord(sides.front, TL);
                            }
                            chunk->mesh.vertices[i++] = coord.x;
                            chunk->mesh.vertices[i++] = coord.y;
                            //chunk->mesh.vertices[i++] = frontFace[a*5 + 3];
                            //chunk->mesh.vertices[i++] = frontFace[a*5 + 4];
                            chunk->mesh.verticeCount++;
                        }
                        chunk->mesh.indices[j++] = quads * 4 + 0;
                        chunk->mesh.indices[j++] = quads * 4 + 1;
                        chunk->mesh.indices[j++] = quads * 4 + 2;
                        chunk->mesh.indices[j++] = quads * 4 + 2;
                        chunk->mesh.indices[j++] = quads * 4 + 3;
                        chunk->mesh.indices[j++] = quads * 4 + 0;
                        chunk->mesh.indiceCount += num;
                        quads++;
                    }
                    if (block.backVisible) {
                        for (int a = 0; a < 4; a++) {
                            chunk->mesh.vertices[i++] = backFace[a * 5 + 0] + x;
                            chunk->mesh.vertices[i++] = backFace[a * 5 + 1] + y;
                            chunk->mesh.vertices[i++] = backFace[a * 5 + 2] + z;
                            struct uvCoord coord;
                            if (a == 0) {
                                coord = getTextureCoord(sides.back, BL);
                            }
                            if (a == 1) {
                                coord = getTextureCoord(sides.back, BR);
                            }
                            if (a == 2) {
                                coord = getTextureCoord(sides.back, TR);
                            }
                            if (a == 3) {
                                coord = getTextureCoord(sides.back, TL);
                            }
                            chunk->mesh.vertices[i++] = coord.x;
                            chunk->mesh.vertices[i++] = coord.y;
                            chunk->mesh.verticeCount++;
                        }
                        chunk->mesh.indices[j++] = quads * 4 + 0;
                        chunk->mesh.indices[j++] = quads * 4 + 1;
                        chunk->mesh.indices[j++] = quads * 4 + 2;
                        chunk->mesh.indices[j++] = quads * 4 + 2;
                        chunk->mesh.indices[j++] = quads * 4 + 3;
                        chunk->mesh.indices[j++] = quads * 4 + 0;
                        chunk->mesh.indiceCount += num;
                        quads++;
                    }
                    if (block.leftVisible) {
                        for (int a = 0; a < 4; a++) {
                            chunk->mesh.vertices[i++] = leftFace[a * 5 + 0] + x;
                            chunk->mesh.vertices[i++] = leftFace[a * 5 + 1] + y;
                            chunk->mesh.vertices[i++] = leftFace[a * 5 + 2] + z;
                            struct uvCoord coord;
                            if (a == 0) {
                                coord = getTextureCoord(sides.left, BL);
                            }
                            if (a == 1) {
                                coord = getTextureCoord(sides.left, BR);
                            }
                            if (a == 2) {
                                coord = getTextureCoord(sides.left, TR);
                            }
                            if (a == 3) {
                                coord = getTextureCoord(sides.left, TL);
                            }
                            chunk->mesh.vertices[i++] = coord.x;
                            chunk->mesh.vertices[i++] = coord.y;
                            chunk->mesh.verticeCount++;
                        }
                        chunk->mesh.indices[j++] = quads * 4 + 0;
                        chunk->mesh.indices[j++] = quads * 4 + 1;
                        chunk->mesh.indices[j++] = quads * 4 + 2;
                        chunk->mesh.indices[j++] = quads * 4 + 2;
                        chunk->mesh.indices[j++] = quads * 4 + 3;
                        chunk->mesh.indices[j++] = quads * 4 + 0;
                        chunk->mesh.indiceCount += num;
                        quads++;
                    }
                    if (block.rightVisible) {
                        for (int a = 0; a < 4; a++) {
                            chunk->mesh.vertices[i++] = rightFace[a * 5 + 0] + x;
                            chunk->mesh.vertices[i++] = rightFace[a * 5 + 1] + y;
                            chunk->mesh.vertices[i++] = rightFace[a * 5 + 2] + z;
                            struct uvCoord coord;
                            if (a == 0) {
                                coord = getTextureCoord(sides.right, BL);
                            }
                            if (a == 1) {
                                coord = getTextureCoord(sides.right, BR);
                            }
                            if (a == 2) {
                                coord = getTextureCoord(sides.right, TR);
                            }
                            if (a == 3) {
                                coord = getTextureCoord(sides.right, TL);
                            }
                            chunk->mesh.vertices[i++] = coord.x;
                            chunk->mesh.vertices[i++] = coord.y;
                            chunk->mesh.verticeCount++;
                        }
                        chunk->mesh.indices[j++] = quads * 4 + 0;
                        chunk->mesh.indices[j++] = quads * 4 + 1;
                        chunk->mesh.indices[j++] = quads * 4 + 2;
                        chunk->mesh.indices[j++] = quads * 4 + 2;
                        chunk->mesh.indices[j++] = quads * 4 + 3;
                        chunk->mesh.indices[j++] = quads * 4 + 0;
                        chunk->mesh.indiceCount += num;
                        quads++;
                    }
                    if (block.topVisible) {
                        for (int a = 0; a < 4; a++) {
                            chunk->mesh.vertices[i++] = topFace[a * 5 + 0] + x;
                            chunk->mesh.vertices[i++] = topFace[a * 5 + 1] + y;
                            chunk->mesh.vertices[i++] = topFace[a * 5 + 2] + z;
                            struct uvCoord coord;
                            if (a == 0) {
                                coord = getTextureCoord(sides.top, BL);
                            }
                            if (a == 1) {
                                coord = getTextureCoord(sides.top, BR);
                            }
                            if (a == 2) {
                                coord = getTextureCoord(sides.top, TR);
                            }
                            if (a == 3) {
                                coord = getTextureCoord(sides.top, TL);
                            }
                            chunk->mesh.vertices[i++] = coord.x;
                            chunk->mesh.vertices[i++] = coord.y;
                            chunk->mesh.verticeCount++;
                        }
                        chunk->mesh.indices[j++] = quads * 4 + 0;
                        chunk->mesh.indices[j++] = quads * 4 + 1;
                        chunk->mesh.indices[j++] = quads * 4 + 2;
                        chunk->mesh.indices[j++] = quads * 4 + 2;
                        chunk->mesh.indices[j++] = quads * 4 + 3;
                        chunk->mesh.indices[j++] = quads * 4 + 0;
                        chunk->mesh.indiceCount += num;
                        quads++;
                    }
                    if (block.bottomVisible) {
                        for (int a = 0; a < 4; a++) {
                            chunk->mesh.vertices[i++] = bottomFace[a * 5 + 0] + x;
                            chunk->mesh.vertices[i++] = bottomFace[a * 5 + 1] + y;
                            chunk->mesh.vertices[i++] = bottomFace[a * 5 + 2] + z;
                            struct uvCoord coord;
                            if (a == 0) {
                                coord = getTextureCoord(sides.bottom, BL);
                            }
                            if (a == 1) {
                                coord = getTextureCoord(sides.bottom, BR);
                            }
                            if (a == 2) {
                                coord = getTextureCoord(sides.bottom, TR);
                            }
                            if (a == 3) {
                                coord = getTextureCoord(sides.bottom, TL);
                            }
                            chunk->mesh.vertices[i++] = coord.x;
                            chunk->mesh.vertices[i++] = coord.y;
                            chunk->mesh.verticeCount++;
                        }
                        chunk->mesh.indices[j++] = quads * 4 + 0;
                        chunk->mesh.indices[j++] = quads * 4 + 1;
                        chunk->mesh.indices[j++] = quads * 4 + 2;
                        chunk->mesh.indices[j++] = quads * 4 + 2;
                        chunk->mesh.indices[j++] = quads * 4 + 3;
                        chunk->mesh.indices[j++] = quads * 4 + 0;
                        chunk->mesh.indiceCount += num;
                        quads++;
                    }
                }
            }
        }
    }
    glBindVertexArray(chunk->mesh.VAO);

	glBindBuffer(GL_ARRAY_BUFFER, chunk->mesh.VBO);
	glBufferData(GL_ARRAY_BUFFER, chunk->mesh.verticeCount * 5 * sizeof(float), chunk->mesh.vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, chunk->mesh.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, chunk->mesh.indiceCount * sizeof(int), chunk->mesh.indices, GL_STATIC_DRAW);
}

void renderChunkMesh(Chunk* chunk, unsigned int shaderProgram, mat4 frustum) {
    if (chunk == NULL) {
        printf("ERROR: Attempted to render null chunk\n");
        return;
    }
    int x = chunk->x;
    int z = chunk->z;
    // a box defines the minimum and maximum coordinate of a 3d object
    vec3 box[2] = {x*CHUNKX, 0, z*CHUNKZ, x*CHUNKX+CHUNKX, CHUNKY, z*CHUNKZ+CHUNKZ};
    vec4 planes[6];
    // extracts the planes from the frustum and checks if the box falls within the planes of the frustum
    glm_frustum_planes(frustum, planes);
    if(!glm_aabb_frustum(box, planes)) {
        return;
    }
    glBindTexture(GL_TEXTURE_2D, getTextureAtlas());
    glBindVertexArray(chunk->mesh.VAO);
    mat4 transform;
    vec3 location = {(float)chunk->x*CHUNKX, 1.0f, (float)chunk->z*CHUNKZ};
    glm_mat4_identity(transform);
	glm_translate(transform, location);
	setShaderMat4("model", transform, shaderProgram);
    glDrawElements(GL_TRIANGLES, chunk->mesh.indiceCount, GL_UNSIGNED_INT, 0);
}


void printArrayFloat(float* array, int width, int size) {
    int i = 0;
    for(int x=0; x<size/width; x++) {
        printf("%i: ", x);
        for(int y=0; y<width; y++) {
            printf("%g, ", array[i]);
            i++;
        }
        printf("\n");
    }
}
void printArrayInt(int* array, int width, int size) {
    int i = 0;
    for(int x=0; x<size/width; x++) {
        printf("%i: ", x);
        for(int y=0; y<width; y++) {
            printf("%i, ", array[i]);
            i++;
        }
        printf("\n");
    }
}

#include "core.h"
#include "chunk.h"
#include "blocks/block.h"
#include "render.h"
#include "noise.h"
#include "scenes/testScene.h"
#include "../vendor/cglm/box.h"
#include "../vendor/cglm/frustum.h"


const float frontFace[] = {
        -1.0f, -1.0f, -1.0f, 0.5f, 0.5f,	//bottom left		0
         1.0f, -1.0f, -1.0f, 1.0f, 0.5f,	//bottom right		1
         1.0f,	1.0f, -1.0f, 1.0f, 1.0f,	//top right			2
        -1.0f,  1.0f, -1.0f, 0.5f, 1.0f,	//top left			3
};
const float backFace[] = {
         1.0f, -1.0f, 1.0f, 0.0f, 0.0f,		//bottom left		4
        -1.0f, -1.0f, 1.0f, 0.5f, 0.0f,		//bottom right		5
        -1.0f,	1.0f, 1.0f, 0.5f, 0.5f,		//top right			6
         1.0f,  1.0f, 1.0f, 0.0f, 0.5f,		//top left			7
};
const float leftFace[] = {
        -1.0f, -1.0f,  1.0f, 0.0f, 0.0f,	// 8
        -1.0f, -1.0f, -1.0f, 0.5f, 0.0f,	// 9
        -1.0f,  1.0f, -1.0f, 0.5f, 0.5f,	// 10
        -1.0f,	1.0f,  1.0f, 0.0f, 0.5f,	// 11
};
const float rightFace[] = {
         1.0f, -1.0f, -1.0f, 0.0f, 0.0f,	//12
         1.0f, -1.0f,  1.0f, 0.5f, 0.0f,	//13
         1.0f,  1.0f,  1.0f, 0.5f, 0.5f,	//14
         1.0f,  1.0f, -1.0f, 0.0f, 0.5f,	//15
};
const float topFace[] = {
        -1.0f,  1.0f, -1.0f, 0.0f, 0.5f,	//16
         1.0f,  1.0f, -1.0f, 0.5f, 0.5f,	//17
         1.0f,  1.0f,  1.0f, 0.5f, 1.0f,	//18
        -1.0f,  1.0f,  1.0f, 0.0f, 1.0f,	//19
};
const float bottomFace[] = {
        -1.0f, -1.0f, -1.0f, 0.5f, 0.0f,
         1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 1.0f, 0.5f,
        -1.0f, -1.0f,  1.0f, 0.5f, 0.5f,
};

void freeChunkManager(ChunkManager cm) {
    for (int c = 0; c < cm.index; c++) {
        Chunk* chunk = cm.chunks[c];
        glDeleteBuffers(1, &(chunk->mesh.VBO));
        glDeleteBuffers(1, &(chunk->mesh.EBO));
        glDeleteVertexArrays(1, &(chunk->mesh.VAO));
        free(chunk->mesh.vertices);
        free(chunk->mesh.indices);
        free(chunk);
    }
    free(cm.chunks);
}

void checkChunkVisible(ChunkManager* cm, Chunk* chunk);
Chunk* getChunk(ChunkManager* cm, int x, int z);

void chunkGenInit(){
    srand(5);
}
void setBlockDefault(Block* block) {
    block->allVisible = 0;
    block->topVisible = 0;
    block->bottomVisible = 0;
    block->leftVisible = 0;
    block->rightVisible = 0;
    block->frontVisible = 0;
    block->backVisible = 0;
    block->blockID = AIR;
    block->checked = 0;
}
void generateChunk(ChunkManager* cm, int chunkx, int chunkz) {
    //printf("generateChunk()\n");
    //printf("Allocating memory\n");
    if (cm == NULL) {
        printf("ERROR: Null chunk manager\n");
        return;
    }
    if (cm->index == cm->size - 1) {
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
    
    //printf("Allocating Memory\n");
    Chunk* chunk = malloc(sizeof(Chunk));
    if (chunk == NULL) {
        printf("\tChunk %i, %i, failed to allocate memory\n", chunkx, chunkz);
        return;
    }
    else {
        //printf("Memory assigned\n");
        chunk->x = chunkx;
        chunk->z = chunkz;
        chunk->index = cm->index;
        chunk->quads = 0;
        chunk->needsPreparing = 1;
        chunk->needsBuffers = 1;
        chunk->mesh.indiceCount = 0;
        chunk->mesh.verticeCount = 0;
        chunk->mesh.vertices = NULL;
        chunk->mesh.indices = NULL;

        //printf("Setting defaults\n");
        for(int x=0; x<CHUNKX; x++) {
            for(int y=0; y<CHUNKY; y++) {
                for(int z=0; z<CHUNKZ; z++) {
                    chunk->grid[x][y][z].blockID = 0;
                    setBlockDefault(&(chunk->grid[x][y][z]));
                    chunk->grid[x][y][z].checked = 0;
                    chunk->grid[x][y][z].topVisible = 0;
                    chunk->grid[x][y][z].bottomVisible = 0;
                    chunk->grid[x][y][z].leftVisible = 0;
                    chunk->grid[x][y][z].rightVisible = 0;
                    chunk->grid[x][y][z].frontVisible = 0;
                    chunk->grid[x][y][z].backVisible = 0;
                    if(y == 1) {
                        chunk->grid[x][y][z].blockID = GREEN;
                    }
                }
            }
        }
        //printf("Generating Terrain\n");
        /*if (chunkx < 0) {
            chunkx *= -1;
        }
        if (chunkz < 0) {
            chunkz *= -1;
        }*/
        for(int x=0; x < CHUNKX; x++) {
            for(int z=0; z< CHUNKZ; z++) {
                int height = (int)(perlin2d(x+chunkx*CHUNKX, z+chunkz*CHUNKZ, 0.005, 10) * 100);
                if (height > CHUNKY - 2) {
                    height = CHUNKY - 2;
                }
                if (height < 0) {
                    height = 0;
                }
                chunk->grid[x][height][z].blockID = GREEN;
                for(int y=height; y > 0; y--) {
                    if (height - y < 10) {
                        chunk->grid[x][y][z].blockID = GREEN;
                    }
                    else{
                        float value = pnoise3((float)(x + chunkx * CHUNKX)/25.0f, (float)y / 10.0f, (float)(z + chunkz * CHUNKZ) / 25.0f, 200, 200, 200);
                        if (value < 0.2) {
                            chunk->grid[x][y][z].blockID = GREEN;
                        }
                    }
                }
            }
        }
    }
    cm->index++;
}

Chunk* getChunk(ChunkManager* cm, int x, int z) {
    //printf("getChunk() Getting chunk %i %i\n", x, z);
    for(int i = 0; i < cm->index; i++) {
        if (cm->chunks[i]->x == x && cm->chunks[i]->z == z) {
            printf("\tChunk %i %i Found\n", x, z);
            return cm->chunks[i];
        }
    }
    //printf("\tChunk %i %i not found\n", x, z);
    //printf("\tGenerating chunk %i %i\n", x, z);
    generateChunk(cm, x, z);
    //printf("P2\n");
    if(cm->chunks[cm->index - 1] == NULL) {
        printf("Error getting chunk %i %i\n", x, z);
    }
    return cm->chunks[cm->index-1];
}

void checkChunkVisible(ChunkManager* cm, Chunk* chunk) {
    //printf("checkChunkVisible() chunk: %i\n", i);
    if (chunk == NULL) {
        printf("ERROR: Attemped to check null chunk mesh\n");
    }
    //printf("\tGetting left chunk\n");
    Chunk* leftChunk = getChunk(cm, chunk->x-1, chunk->z);
    if(leftChunk == NULL) {
        printf("\tError retrieving chunk %i %i\n", chunk->x-1, chunk->z);
    }
    //printf("\tGetting right chunk\n");
    Chunk* rightChunk = getChunk(cm, chunk->x+1, chunk->z);
    if(rightChunk == NULL) {
        printf("\tError retrieving chunk %i %i\n", chunk->x+1, chunk->z);
    }
    //printf("\tGetting back chunk\n");
    Chunk* backChunk = getChunk(cm, chunk->x, chunk->z-1);
    if(backChunk == NULL) {
        printf("\tError retrieving chunk %i %i\n", chunk->x, chunk->z-1);
    }
    //printf("\tGetting front chunk\n");
    Chunk* frontChunk = getChunk(cm, chunk->x, chunk->z+1);
    if(frontChunk == NULL) {
        printf("\tError retrieving chunk %i %i\n", chunk->x, chunk->z+1);
    }
    //printf("Checking blocks\n");
    int visibleCount = 0;
    for (int x = 0; x < CHUNKX; x++) {
        for (int y = 0; y < CHUNKY; y++) {
            for ( int z = 0; z < CHUNKZ; z++) {
                //chunk->grid[x][y][z].allVisible = 1;
                //chunk->quads+=6;
                //continue;
                if (chunk->grid[x][y][z].blockID != AIR) 
                {
                    bool shouldRender = false;
                     if (x == 0) {
                        //printf("X = 0\n");
                        if (leftChunk->grid[CHUNKX-1][y][z].blockID == AIR) {
                            chunk->grid[x][y][z].leftVisible = 1;
                            chunk->quads++;
                        }
                    }
                    if (x == CHUNKX - 1) {
                        //printf("X = CHNUKX - 1\n");
                        if (rightChunk->grid[0][y][z].blockID == AIR) {
                            chunk->grid[x][y][z].rightVisible = 1;
                            chunk->quads++;
                        }
                    }
                    if (x !=0) {
                        if (chunk->grid[x-1][y][z].blockID == AIR) {
                            chunk->grid[x][y][z].leftVisible = 1;
                            chunk->quads++;
                        }                        }
                    if (x != CHUNKX - 1) {
                        if (chunk->grid[x+1][y][z].blockID == AIR) {
                            chunk->grid[x][y][z].rightVisible = 1;
                            chunk->quads++;
                        }
                    }                        
                    if (y == 0) {
                            //printf("Y = 0\n");
                        chunk->grid[x][y][z].bottomVisible = 1;
                        if (chunk->grid[x][y+1][z].blockID == AIR) {
                            chunk->grid[x][y][z].topVisible = 1;
                            chunk->quads++;
                            shouldRender = true;
                        }
                    }
                    if (y == CHUNKY - 1) {
                      //printf("Y = CHUNKY - 1\n");
                        chunk->grid[x][y][z].topVisible = 1;
                        chunk->quads++;
                        shouldRender = true;
                    }
                    if (y != 0) {
                        if (chunk->grid[x][y-1][z].blockID == AIR) {
                        chunk->grid[x][y][z].bottomVisible = 1;
                            chunk->quads++;
                        }
                    }
                    if (y != CHUNKY - 1) {
                        if (chunk->grid[x][y+1][z].blockID == AIR) {
                            chunk->grid[x][y][z].topVisible = 1;
                            chunk->quads++;
                        }
                    }
                    if (z == 0) {
                        //printf("Z = 0\n");
                        if (backChunk->grid[x][y][CHUNKZ-1].blockID == AIR) {
                            chunk->grid[x][y][z].frontVisible = 1;
                            chunk->quads++;
                            shouldRender = true;
                        }
                    }
                    if (z == CHUNKZ - 1) {
                        //printf("Z = CHUNKZ - 1\n");
                        if (frontChunk->grid[x][y][0].blockID == AIR) {
                            chunk->grid[x][y][z].backVisible = 1;
                            chunk->quads++;
                            shouldRender = true;
                        }
                    }
                    if (z != 0) {
                        if (chunk->grid[x][y][z-1].blockID == AIR) {
                                chunk->grid[x][y][z].frontVisible = 1;
                            chunk->quads++;
                        }
                    }
                    if (z != CHUNKZ - 1) {
                        if (chunk->grid[x][y][z+1].blockID == AIR) {
                            chunk->grid[x][y][z].backVisible = 1;
                            chunk->quads++;
                        }
                    }
                }
                //printf("Block %i %i %i checked\n", x, y, z);
                chunk->grid[x][y][z].checked = 1;
            }
        }
    }
    //printf("Visible in chunk %i %i: %i\n", chunk->x, chunk->z, visibleCount);
}

void createChunkBuffers(Chunk* chunk) {
    glGenVertexArrays(1, &(chunk->mesh.VAO));
	glGenBuffers(1, &(chunk->mesh.VBO));
    glGenBuffers(1, &(chunk->mesh.EBO));

    printf("Attrib\n");
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

int POO;
void prepareChunkMesh(Chunk* chunk) {
    //printf("prepareChunkMesh()\n");
    if (chunk == NULL) {
        printf("ERROR: Attemped to prepare null chunk mesh\n");
    }
    //printf("In PrepareChunkMesh: allocating memory\n");
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
    //printf("Quads: %i\n", chunk->quads);
    //printf("In PrepareChunkMesh: setting mesh\n");
    int i = 0;
    int j = 0;
    int quads = 0;
    int num = 6;
    int num2 = 1;
    float atlasWidth = 3;
    float atlasHeight = 3;
    float RED = 1;
    float GREEN = 2;
    float BLUE = 3;
    for(int x = 0; x < CHUNKX; x++) {
        for (int y = 0; y < CHUNKY; y++) {
            for (int z = 0; z < CHUNKZ; z++) {
                Block block = chunk->grid[x][y][z];
                if (block.blockID != AIR) {
                    if (block.frontVisible || block.allVisible) {
                        for (int a = 0; a < 4; a++) {
                            chunk->mesh.vertices[i++] = frontFace[a*5 + 0] + x * 2;
                            chunk->mesh.vertices[i++] = frontFace[a*5 + 1] + y * 2;
                            chunk->mesh.vertices[i++] = frontFace[a*5 + 2] + z * 2;
                            chunk->mesh.vertices[i++] = frontFace[a*5 + 3];
                            chunk->mesh.vertices[i++] = frontFace[a*5 + 4];
                            chunk->mesh.verticeCount+=num2;
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
                    if (block.backVisible || block.allVisible) {
                        for (int a = 0; a < 4; a++) {
                            chunk->mesh.vertices[i++] = backFace[a * 5 + 0] + x * 2;
                            chunk->mesh.vertices[i++] = backFace[a * 5 + 1] + y * 2;
                            chunk->mesh.vertices[i++] = backFace[a * 5 + 2] + z * 2;
                            chunk->mesh.vertices[i++] = backFace[a * 5 + 3];
                            chunk->mesh.vertices[i++] = backFace[a * 5 + 4];
                            chunk->mesh.verticeCount+=num2;
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
                    if (block.leftVisible || block.allVisible) {
                        for (int a = 0; a < 4; a++) {
                            chunk->mesh.vertices[i++] = leftFace[a * 5 + 0] + x * 2;
                            chunk->mesh.vertices[i++] = leftFace[a * 5 + 1] + y * 2;
                            chunk->mesh.vertices[i++] = leftFace[a * 5 + 2] + z * 2;
                            chunk->mesh.vertices[i++] = leftFace[a * 5 + 3];
                            chunk->mesh.vertices[i++] = leftFace[a * 5 + 4];
                            chunk->mesh.verticeCount+=num2;
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
                    if (block.rightVisible || block.allVisible) {
                        for (int a = 0; a < 4; a++) {
                            chunk->mesh.vertices[i++] = rightFace[a * 5 + 0] + x * 2;
                            chunk->mesh.vertices[i++] = rightFace[a * 5 + 1] + y * 2;
                            chunk->mesh.vertices[i++] = rightFace[a * 5 + 2] + z * 2;
                            chunk->mesh.vertices[i++] = rightFace[a * 5 + 3];
                            chunk->mesh.vertices[i++] = rightFace[a * 5 + 4];
                            chunk->mesh.verticeCount+=num2;
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
                    if (block.topVisible || block.allVisible) {
                        for (int a = 0; a < 4; a++) {
                            chunk->mesh.vertices[i++] = topFace[a * 5 + 0] + x * 2;
                            chunk->mesh.vertices[i++] = topFace[a * 5 + 1] + y * 2;
                            chunk->mesh.vertices[i++] = topFace[a * 5 + 2] + z * 2;
                            chunk->mesh.vertices[i++] = topFace[a * 5 + 3];
                            chunk->mesh.vertices[i++] = topFace[a * 5 + 4];
                            chunk->mesh.verticeCount+=num2;
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
                    if (block.bottomVisible || block.allVisible) {
                        for (int a = 0; a < 4; a++) {
                            chunk->mesh.vertices[i++] = bottomFace[a * 5 + 0] + x * 2;
                            chunk->mesh.vertices[i++] = bottomFace[a * 5 + 1] + y * 2;
                            chunk->mesh.vertices[i++] = bottomFace[a * 5 + 2] + z * 2;
                            chunk->mesh.vertices[i++] = bottomFace[a * 5 + 3];
                            chunk->mesh.vertices[i++] = bottomFace[a * 5 + 4];
                            chunk->mesh.verticeCount+=num2;
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
    //printf("In prepareChunkMesh(): Finalizing data\n");
    
    //printf("VAO bind\n");
    glBindVertexArray(chunk->mesh.VAO);

    //printf("VBO bind\n");
	glBindBuffer(GL_ARRAY_BUFFER, chunk->mesh.VBO);
	glBufferData(GL_ARRAY_BUFFER, chunk->mesh.verticeCount * 5 * sizeof(float), chunk->mesh.vertices, GL_STATIC_DRAW);

    //printf("EBO\n");
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, chunk->mesh.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, chunk->mesh.indiceCount * sizeof(int), chunk->mesh.indices, GL_STATIC_DRAW);
    if (chunk == NULL) {
        printf("FUCK NGIGERS!\n");
    }
}

void renderChunkMesh(Chunk* chunk, unsigned int shaderProgram) {
    if (chunk == NULL) {
        printf("ERROR: Attempted to render null chunk\n");
        return;
    }
    glBindTexture(GL_TEXTURE_2D, getBlockTexture(GRASS));
    glBindVertexArray(chunk->mesh.VAO);
    mat4 transform;
    vec3 location = {(float)chunk->x*CHUNKX*2, 1.0f, (float)chunk->z*CHUNKZ*2};
    glm_mat4_identity(transform);
	glm_translate(transform, location);
	setShaderMat4("model", transform, shaderProgram);
    glDrawElements(GL_TRIANGLES, chunk->mesh.indiceCount, GL_UNSIGNED_INT, 0);
}


void printArrayFloat(float* array, int width, int size) {
    int i = 0;
    //printf("%i %i\n", width, size);
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
    //printf("%i %i\n", width, size);
    for(int x=0; x<size/width; x++) {
        printf("%i: ", x);
        for(int y=0; y<width; y++) {
            printf("%i, ", array[i]);
            i++;
        }
        printf("\n");
    }
}

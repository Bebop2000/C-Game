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
        chunk->blockCount = 0;

        for(int x=0; x < CHUNKX; x++) {
            for(int y=0; y<CHUNKY; y++) {
                for(int z=0; z<CHUNKZ; z++) {
                    int height = (int)(perlin2d(x+chunkx*CHUNKX, z+chunkz*CHUNKZ, 0.003, 10) * 100);
                    //printf("%i\n", height);
                    if(height == y){
                        chunk->grid[x][y][z].blockID = GREEN;
                        chunk->blockCount += 1;
                    }
                    else {
                        chunk->grid[x][y][z].blockID = AIR;
                     }
                }
            }
        }
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
                            chunk->visibleBlockCount++;
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

const float cubeVertices[] = {

        //each face consists of two triangles
		// z plane positive going away from camera
		// front face
		-1.0f, -1.0f, -1.0f, 0.5f, 0.5f,	//bottom left		0
		 1.0f, -1.0f, -1.0f, 1.0f, 0.5f,	//bottom right		1
		 1.0f,	1.0f, -1.0f, 1.0f, 1.0f,	//top right			2
         1.0f,	1.0f, -1.0f, 1.0f, 1.0f,    //top right         2
		-1.0f,  1.0f, -1.0f, 0.5f, 1.0f,	//top left			3
        -1.0f, -1.0f, -1.0f, 0.5f, 0.5f,
		// back face
		 1.0f, -1.0f, 1.0f, 0.0f, 0.0f,		//bottom left		4
		-1.0f, -1.0f, 1.0f, 0.5f, 0.0f,		//bottom right		5
		-1.0f,	1.0f, 1.0f, 0.5f, 0.5f,		//top right			6
        -1.0f,	1.0f, 1.0f, 0.5f, 0.5f,		//top right			6
		 1.0f,  1.0f, 1.0f, 0.0f, 0.5f,		//top left			7
         1.0f, -1.0f, 1.0f, 0.0f, 0.0f,		//bottom left		4
		// left face
		-1.0f, -1.0f,  1.0f, 0.0f, 0.0f,	// 8
		-1.0f, -1.0f, -1.0f, 0.5f, 0.0f,	// 9
		-1.0f,  1.0f, -1.0f, 0.5f, 0.5f,	// 10
        -1.0f,  1.0f, -1.0f, 0.5f, 0.5f,	// 10
		-1.0f,	1.0f,  1.0f, 0.0f, 0.5f,	// 11
        -1.0f, -1.0f,  1.0f, 0.0f, 0.0f,	// 8
		// right face
		 1.0f, -1.0f, -1.0f, 0.0f, 0.0f,	//12
		 1.0f, -1.0f,  1.0f, 0.5f, 0.0f,	//13
		 1.0f,  1.0f,  1.0f, 0.5f, 0.5f,	//14
         1.0f,  1.0f,  1.0f, 0.5f, 0.5f,	//14
		 1.0f,  1.0f, -1.0f, 0.0f, 0.5f,	//15
         1.0f, -1.0f, -1.0f, 0.0f, 0.0f,	//12
		// top face
		-1.0f,  1.0f, -1.0f, 0.0f, 0.5f,	//16
		 1.0f,  1.0f, -1.0f, 0.5f, 0.5f,	//17
		 1.0f,  1.0f,  1.0f, 0.5f, 1.0f,	//18
         1.0f,  1.0f,  1.0f, 0.5f, 1.0f,	//18
		-1.0f,  1.0f,  1.0f, 0.0f, 1.0f,	//19
        -1.0f,  1.0f, -1.0f, 0.0f, 0.5f,	//16
		// bottom face
		-1.0f, -1.0f, -1.0f, 0.5f, 0.0f,	//20
		 1.0f, -1.0f, -1.0f, 1.0f, 0.0f,	//21
		 1.0f, -1.0f,  1.0f, 1.0f, 0.5f,	//22
         1.0f, -1.0f,  1.0f, 1.0f, 0.5f,	//22
		-1.0f, -1.0f,  1.0f, 0.5f, 0.5f,	//23
        -1.0f, -1.0f, -1.0f, 0.5f, 0.0f,	//20
	};
const float cubeVertices2[] = {

        //each face consists of two triangles
		// z plane positive going away from camera
		// front face
		-1.0f, -1.0f, -1.0f, 0.5f, 0.5f,	//bottom left		0
		 1.0f, -1.0f, -1.0f, 1.0f, 0.5f,	//bottom right		1
		 1.0f,	1.0f, -1.0f, 1.0f, 1.0f,	//top right			2
		-1.0f,  1.0f, -1.0f, 0.5f, 1.0f,	//top left			3
		// back face
		 1.0f, -1.0f, 1.0f, 0.0f, 0.0f,		//bottom left		4
		-1.0f, -1.0f, 1.0f, 0.5f, 0.0f,		//bottom right		5
		-1.0f,	1.0f, 1.0f, 0.5f, 0.5f,		//top right			6
		 1.0f,  1.0f, 1.0f, 0.0f, 0.5f,		//top left			7
		// left face
		-1.0f, -1.0f,  1.0f, 0.0f, 0.0f,	// 8
		-1.0f, -1.0f, -1.0f, 0.5f, 0.0f,	// 9
		-1.0f,  1.0f, -1.0f, 0.5f, 0.5f,	// 10
		-1.0f,	1.0f,  1.0f, 0.0f, 0.5f,	// 11
		// right face
		 1.0f, -1.0f, -1.0f, 0.0f, 0.0f,	//12
		 1.0f, -1.0f,  1.0f, 0.5f, 0.0f,	//13
		 1.0f,  1.0f,  1.0f, 0.5f, 0.5f,	//14
		 1.0f,  1.0f, -1.0f, 0.0f, 0.5f,	//15
		// top face
		-1.0f,  1.0f, -1.0f, 0.0f, 0.5f,	//16
		 1.0f,  1.0f, -1.0f, 0.5f, 0.5f,	//17
		 1.0f,  1.0f,  1.0f, 0.5f, 1.0f,	//18
		-1.0f,  1.0f,  1.0f, 0.0f, 1.0f,	//19
		// bottom face
		-1.0f, -1.0f, -1.0f, 0.5f, 0.0f,	//20
		 1.0f, -1.0f, -1.0f, 1.0f, 0.0f,	//21
		 1.0f, -1.0f,  1.0f, 1.0f, 0.5f,	//22
		-1.0f, -1.0f,  1.0f, 0.5f, 0.5f,	//23
	};
void prepareChunkMesh(Chunk* chunk) {
    //printf("In PrepareChunkMesh: allocating memory\n");
    chunk->mesh = (float*)calloc(chunk->blockCount*24*5, sizeof(float));
    chunk->indices = (int*)calloc(chunk->blockCount*36, sizeof(int));
    //printf("BC %i\n", chunk->blockCount);
    int i = 0;
    int j = 0;
    //printf("In PrepareChunkMesh: setting mesh\n");
    int meshed =0;
    /*
    for(int x=0; x<CHUNKX; x++) {
        for(int y=0; y<CHUNKY; y++) {
            for(int z=0; z<CHUNKZ; z++) {
                if(chunk->grid[x][y][z].blockID != AIR) {
                    count++;
                    for(int k=0; k<36; k++){
                        chunk->mesh[i++] = cubeVertices[k*5+0] + x*2;
                        chunk->mesh[i++] = cubeVertices[k*5+1] + y*2;
                        chunk->mesh[i++] = cubeVertices[k*5+2] + z*2;
                        chunk->mesh[i++] = cubeVertices[k*5+3];
                        chunk->mesh[i++] = cubeVertices[k*5+4];
                    }
                    chunk->vertices+=36*10;
                }
            }
        }
    }*/
    for(int x=0; x<CHUNKX; x++) {
        for(int y=0; y<CHUNKY; y++) {
            for(int z=0; z<CHUNKZ; z++) {
                if(chunk->grid[x][y][z].blockID != AIR) {
                    for(int k=0; k<24; k++){
                        //printf("M\n");
                        chunk->mesh[i++] = cubeVertices[k*5+0] + x*2;
                        chunk->mesh[i++] = cubeVertices[k*5+1] + y*2;
                        chunk->mesh[i++] = cubeVertices[k*5+2] + z*2;
                        chunk->mesh[i++] = cubeVertices[k*5+3];
                        chunk->mesh[i++] = cubeVertices[k*5+4];
                    }
                    chunk->vertices+=24;
                    for(int a=0; a<6; a++) {
                        //printf("%i\n", meshed*24 + a*4 + 0);
                        chunk->indices[j++] = meshed*24 + a*4 + 0;
                        chunk->indices[j++] = meshed*24 + a*4 + 1;
                        chunk->indices[j++] = meshed*24 + a*4 + 2;
                        chunk->indices[j++] = meshed*24 + a*4 + 2;
                        chunk->indices[j++] = meshed*24 + a*4 + 3;
                        chunk->indices[j++] = meshed*24 + a*4 + 0;
                    }
                    //printf("%i\n", meshed);
                    chunk->indiceCount+=36;
                    meshed++;
                }
            }
        }
    }
    //printf("Count: %i\n", count);
	glGenVertexArrays(1, &(chunk->VAO));
	glBindVertexArray(chunk->VAO);
	glGenBuffers(1, &(chunk->VBO));
    glGenBuffers(1, &(chunk->EBO));

	glBindBuffer(GL_ARRAY_BUFFER, chunk->VBO);
	glBufferData(GL_ARRAY_BUFFER, chunk->vertices, chunk->mesh, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, chunk->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, chunk->indiceCount, chunk->indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void renderChunkMesh(Chunk* chunk, unsigned int shaderProgram) {
    prepareCubeRender();
    glBindTexture(GL_TEXTURE_2D, getBlockTexture(GREEN));
    glBindVertexArray(chunk->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, chunk->VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, chunk->EBO);
    
    mat4 transform;
    vec3 location = {(float)chunk->x*CHUNKX*2, 1.0f, (float)chunk->z*CHUNKZ*2};
    glm_mat4_identity(transform);
	glm_translate(transform, location);
	setShaderMat4("model", transform, shaderProgram);

    //glDrawArrays(GL_TRIANGLES, 0, chunk->vertices);
    glDrawElements(GL_TRIANGLES, chunk->indiceCount, GL_UNSIGNED_INT, 0);
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
        //int blockCount = 0;
        for (int x = 0; x < CHUNKX; x++) {
            for (int y = 0; y < CHUNKY; y++) {
                for (int z = 0; z < CHUNKZ; z++) {
                    char block = chunk->grid[x][y][z].blockID;
                    if (block != AIR) {
                        //if the block is next to an air block it will be rendered
                        bool shouldRender = false;
                        // width of a cube is 2
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

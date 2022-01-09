#include "render.h"
#include "core.h"
#include "blocks/block.h"
#include "blocks/blockTextures.h"
#include "shaderProgram.h"

Mesh cubeMesh;
Mesh uniformCubeMesh;
Mesh quadMesh;

mat4 transform;
vec3 xAxis = { 1.0f, 0.0f, 0.0f };
vec3 yAxis = { 0.0f, 1.0f, 0.0f };
vec3 zAxis = { 0.0f, 0.0f, 1.0f };

void prepareCubeRender(){
	glBindVertexArray(cubeMesh.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, cubeMesh.VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeMesh.EBO);
}

void prepareQuadRender(){
	glBindVertexArray(quadMesh.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadMesh.VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadMesh.EBO);
}
void renderBlock(BlockID block, vec3 location, float scale, unsigned int shaderProgram) {
	glBindTexture(GL_TEXTURE_2D, getBlockTexture(block));
	glm_mat4_identity(transform);
	glm_translate(transform, location);
	setShaderMat4("model", transform, shaderProgram);
	glDrawElements(GL_TRIANGLES, cubeMesh.vertices, GL_UNSIGNED_INT, 0);
}

void renderQuad(BlockID block, vec3 location, float scale, unsigned int shaderProgram) {
	glBindTexture(GL_TEXTURE_2D, getBlockTexture(block));
	glBindVertexArray(quadMesh.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadMesh.VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadMesh.EBO);
	glm_mat4_identity(transform);
	glm_translate(transform, location);
	vec3 uScale = {scale, scale, scale};
	glm_scale(transform, uScale);
	setShaderMat4("model", transform, shaderProgram);
	glDrawElements(GL_TRIANGLES, quadMesh.vertices, GL_UNSIGNED_INT, 0);
}

void bindQuadMesh() {
	glBindVertexArray(quadMesh.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, quadMesh.VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadMesh.EBO);
}

void bindCubeMesh() {
	glBindVertexArray(cubeMesh.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, cubeMesh.VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeMesh.EBO);	
}

void cubeMeshInit() {
	const float cubeVertices[] = {

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
		-1.0f, -1.0f,  1.0f, 0.5f, 0.0f,	//20
		 1.0f, -1.0f,  1.0f, 1.0f, 0.0f,	//21
		 1.0f, -1.0f, -1.0f, 1.0f, 0.5f,	//22
		-1.0f, -1.0f, -1.0f, 0.5f, 0.5f		//23
	};
	const int elements[] = {
		//front face
		0, 1, 2,
		2, 3, 0,
		//back face
		4, 5, 6,
		6, 7, 4,
		//left face
		8, 9, 10,
		10, 11, 8,
		//right face
		12, 13, 14,
		14, 15, 12,
		//top face
		16, 17, 18,
		18, 19, 16,
		//bottom face
		20, 21, 22,
		22, 23, 20
	};

	cubeMesh.vertices = sizeof(elements) / sizeof(int);

	glGenVertexArrays(1, &(cubeMesh.VAO));
	glBindVertexArray(cubeMesh.VAO);

	glGenBuffers(1, &(cubeMesh.VBO));
	glGenBuffers(1, &(cubeMesh.EBO));

	glBindBuffer(GL_ARRAY_BUFFER, cubeMesh.VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeMesh.EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void uniformCubeMeshInit() {
	const float cubeVertices[] = {
		// front face
		-1.0f, -1.0f, 1.0f, 0.0f, 0.0f,		//bottom left		0
		 1.0f, -1.0f, 1.0f, 1.0f, 0.0f,		//bottom right		1
		-1.0f,	1.0f, 1.0f, 0.0f, 1.0f,		//top left			2
		 1.0f,  1.0f, 1.0f, 1.0f, 1.0f,		//top right			3
		// back face
		-1.0f, -1.0f, -1.0f, 0.0f, 0.0f,	//bottom left		4
		 1.0f, -1.0f, -1.0f, 1.0f, 0.0f,	//bottom right		5
		-1.0f,	1.0f, -1.0f, 0.0f, 1.0f,	//top left			6
		 1.0f,  1.0f, -1.0f, 1.0f, 1.0f,	//top right			7
		// left face
		-1.0f, -1.0f,  1.0f, 0.0f, 0.0f,	// 8
		-1.0f, -1.0f, -1.0f, 1.0f, 0.0f,	// 9
		-1.0f,  1.0f,  1.0f, 0.0f, 1.0f,	// 10
		-1.0f,	1.0f, -1.0f, 1.0f, 1.0f,	// 11
		// right face
		 1.0f, -1.0f,  1.0f, 0.0f, 0.0f,	//12
		 1.0f, -1.0f, -1.0f, 1.0f, 0.0f,	//13
		 1.0f,  1.0f,  1.0f, 0.0f, 1.0f,	//14
		 1.0f,  1.0f, -1.0f, 1.0f, 1.0f,	//15
		// top face
		-1.0f,  1.0f,  1.0f, 0.0f, 0.0f,	//16
		 1.0f,  1.0f,  1.0f, 1.0f, 0.0f,	//17
		-1.0f,  1.0f, -1.0f, 0.0f, 1.0f,	//18
		 1.0f,  1.0f, -1.0f, 1.0f, 1.0f,	//19
		// bottom face
		-1.0f, -1.0f,  1.0f, 0.0f, 0.0f,	//20
		 1.0f, -1.0f,  1.0f, 1.0f, 0.0f,	//21
		-1.0f, -1.0f, -1.0f, 0.0f, 1.0f,	//22
		 1.0f, -1.0f, -1.0f, 1.0f, 1.0f		//23
	};
	const int elements[] = {
		//front face
		0, 1, 2,
		1, 3, 2,
		//back face
		4, 5, 6,
		5, 7, 6,
		//left face
		8, 9, 10,
		9, 11, 10,
		//right face
		12, 13, 14,
		13, 15, 14,
		//top face
		16, 17, 18,
		17, 19, 18,
		//bottom face
		20, 21, 22,
		21, 23, 22
	};

	uniformCubeMesh.vertices = sizeof(elements) / sizeof(int);

	glGenVertexArrays(1, &(uniformCubeMesh.VAO));
	glBindVertexArray(uniformCubeMesh.VAO);

	glGenBuffers(1, &(uniformCubeMesh.VBO));
	glGenBuffers(1, &(uniformCubeMesh.EBO));

	glBindBuffer(GL_ARRAY_BUFFER, uniformCubeMesh.VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uniformCubeMesh.EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void quadMeshInit() {
	const float quadVertices[] = {
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,		//0
		 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,		//1
		-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,		//2
		 1.0f,  1.0f, 0.0f, 1.0f, 1.0f		//3
	};

	const int elements[] = {
		0, 1, 2,
		1, 3, 2
	};

	quadMesh.vertices = sizeof(elements) / sizeof(int);

	glGenVertexArrays(1, &(quadMesh.VAO));
	glBindVertexArray(quadMesh.VAO);

	glGenBuffers(1, &(quadMesh.VBO));
	glGenBuffers(1, &(quadMesh.EBO));

	glBindBuffer(GL_ARRAY_BUFFER, quadMesh.VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadMesh.EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void rendererInit() {
	cubeMeshInit();
	uniformCubeMeshInit();
	quadMeshInit();
}

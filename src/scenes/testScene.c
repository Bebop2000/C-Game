#include "../core.h"
#include "testScene.h"
#include "../input.h"
#include "../window.h"
#include "../shaderProgram.h"
#include "../texture.h"
#include "../blocks/block.h"
#include "../blocks/blockTextures.h"
#include "../render.h"
#include "../camera.h"
#include "../chunk.h"

#define dist(x1, y1, x2, y2) (sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2)))
#define abs(x) (sqrt(x*x))


static int init();
static void loop();
static void cleanup();
static void perspective();
static void view(struct CameraData camera);
static void processInput();
static void endFrameScroll();
static void framebufferSizeCallback(GLFWwindow *window, int width, int height);
static void mouseCallback(GLFWwindow *window, double xpos, double ypos);
static void printVec3f(vec3 vector);
static float rad(float val);

unsigned int shaderProgram;
CameraData camera;
mat4 viewMatrix;
mat4 projectionMatrix;
// shaderMatrix is the projection matrix multiplied by the view matrix
// which is then sent to the vertex shader
mat4 shaderMatrix;
float fov = 45.0f;
int windowWidth;
int windowHeight;

vec3 craftingTableLocation = {0.0f, 0.0f, 0.0f};

GLFWwindow* window;

ChunkManager chunkManager;

void runTestScene(GLFWwindow *glfwWindow) {
	window = glfwWindow;
	if(init()) {
		loop();
	}
	else{
		printf("Failed to initialize testScene\n");
	}
	cleanup();
}
static int init() {
	printf("Size: %zu\n", sizeof(Chunk*));
	printf("Initializing testScene\n");
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	glfwSetCursorPosCallback(window, mouseCallback);
	framebufferSizeCallback(window, 960, 540);
	setClearColour(48, 117, 186, 255);
#ifdef linux
	shaderProgram = compileShaders("../res/shaders/defaultVertexShader.glsl",
									"../res/shaders/defaultFragShader.glsl");
#else
	shaderProgram = compileShaders("C:/C-Game/res/shaders/defaultVertexShader.glsl",
								   "C:/C-Game/res/shaders/defaultFragShader.glsl");
#endif
	if(!shaderProgram) {
		printf("Error compiling default shader\n");
		return 0;
	}

	chunkManager.chunks = calloc(500, sizeof(Chunk*));
	printf("%p\n", chunkManager.chunks);
	chunkManager.size = 500;
	chunkManager.index = 0;
	printf("\tGenerating starting chunks\n");
	for(int x=0; x<20; x++){
		for(int y=0; y<20; y++){
			//printf("Generating Chunk %i %i %i\n", chunkIndex, x, y);
			generateChunk(&chunkManager, x, y);
			if (chunkManager.chunks[chunkManager.index-1] == NULL) {
				printf("Error generating chunk %i %i\n", x, y);
			}
		}
	}
	printf("\tPreparing Meshes\n");
	int size = chunkManager.index;
	for (int i=0; i < size; i++) {
		Chunk* chunk = chunkManager.chunks[i];
		createChunkBuffers(chunk);
		checkChunkVisible(&chunkManager, chunk);
		prepareChunkMesh(chunk);
	}
	printf("\tPreparing camera\n");
	camera = cameraInit();
	camera.cameraPos[2] = 0.0f;
	camera.cameraPos[1] = 120.0f;
	camera.cameraPos[0] = 0.0f;
	camera.useFront = true;
	view(camera);
	perspective();

	rendererInit();
	blockTexturesInit();
	chunkGenInit();

	glUseProgram(shaderProgram);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glDisable(GL_CULL_FACE);
	//glCullFace(GL_FRONT);
	//glFrontFace(GL_CCW);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	return 1;
}

float startTime = 0.0f;
float endTime = 0.0f;
float dt = 0.0f;
float mult = 60.0f;
float shiftMult = 2.0f;
float shiftMultCache = 0.0f;
bool sceneShouldClose;
bool cull = false;


float left = 0.0f;
float right = 10.0f;
float bottom = 0.0f;
float top = 10.0f;
float near = 0.0f;
float far = 200.0f;
Chunk* activeChunks[500];
int renderDistance = 5;

int POO;
static void loop() {
	printf("Loop start\n");
	sceneShouldClose = false;
	glUseProgram(shaderProgram);
	prepareCubeRender();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	float elapsedTime = 0.0f;
	while (!glfwWindowShouldClose(window) && !sceneShouldClose) {
		dt = endTime - startTime;
		startTime = (float)glfwGetTime();
		//printf("%f, %f, %f\n", camera.cameraPos[0], camera.cameraPos[1], camera.cameraPos[2]);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		updateCameraFront(&camera);
		view(camera);
		perspective();
		glm_mat4_mul(projectionMatrix, viewMatrix, shaderMatrix);
		setShaderMat4("projection", projectionMatrix, shaderProgram);
		setShaderMat4("projectionTimesView", shaderMatrix, shaderProgram);
		//printf("Rending block\n");
		//prepareCubeRender();
		//renderBlock(CRAFTING_TABLE_BLOCK, craftingTableLocation, 1.0f, shaderProgram);
		vec3 loc = {0.0f, 0.0f, 0.0f};

		float playerx = camera.cameraPos[0];
		float playerz = camera.cameraPos[2];
		int currentChunkx = playerx / (float)CHUNKX;
		int currentChunkz = playerz / (float)CHUNKZ;
		if (elapsedTime > 0.5f) {
			printf("%i %i\n", currentChunkx, currentChunkz);
			elapsedTime = 0.0f;
		}

		int i = 0;
		for(int x = currentChunkx-renderDistance; x < currentChunkx+renderDistance; x++) {
			for(int z = currentChunkz-renderDistance; z < currentChunkz+renderDistance; z++) {
				Chunk* temp = getChunk(&chunkManager, x, z);
				if (temp != NULL) {
					if(!temp->hasBuffers) {
						createChunkBuffers(temp);
						temp->hasBuffers = 1;
					}
					if(!temp->hasMesh) {
						checkChunkVisible(&chunkManager, temp);
						prepareChunkMesh(temp);
						temp->hasMesh = 1;
					}
					activeChunks[i++] = temp;
				}
				else {
					printf("NULL Chunk Error\n");
				}
			}
		}
		for(int i=0; i<500; i++) {
			if(activeChunks[i] != NULL) {
				renderChunkMesh(activeChunks[i], shaderProgram, shaderMatrix);
			}
		}
		if (isKeyPressed(GLFW_KEY_I)) {
			printf("Regenerating chunks\n");
			for (int c = 0; c < 500; c++) {
				Chunk* chunk = activeChunks[c];
				if (chunk != NULL) {
					//regenerateChunkTerrain(chunk);
					//createChunkBuffers(chunk);
					freeChunkMesh(chunk);
					createChunkBuffers(chunk);
					checkChunkVisible(&chunkManager, chunk);
					prepareChunkMesh(chunk);
				}
			}
			printf("Done\n");
		}
		if (isKeyPressed(GLFW_KEY_O)) {
			printf("Deleting Meshes\n");
			for (int c = 0; c < chunkManager.index - 1; c++) {
				Chunk* chunk = chunkManager.chunks[c];
				if (chunk != NULL && !chunk->hasBuffers && !chunk->hasMesh) {
					freeChunkMesh(chunkManager.chunks[c]);
				}
			}
		}
		for (int i = 0; i < 500; i++) {
			activeChunks[i] = NULL;
		}
		for(int i = 0; i <chunkManager.index; i++) {
			Chunk* chunk = chunkManager.chunks[i];
			if(dist(currentChunkx, currentChunkz, chunk->x, chunk->z) > (float)(renderDistance + 20)) {
				//printf("Freeing %i %i\n", chunk->x, chunk->z);
				if ((chunk->hasMesh || chunk->hasBuffers) && chunk != NULL) {
					freeChunkMesh(chunk);
					chunk->hasBuffers = 0;
					chunk->hasMesh = 0;
				}
			}
		}
		processInput();
		glfwSwapBuffers(window);
		endFrameScroll();
		glfwPollEvents();
		endTime = (float)glfwGetTime();
		elapsedTime += dt;
	}
}

static void cleanup() {
	printf("Cleanup\n");
	freeChunkManager(chunkManager);
	cleanupTextures();
	printf("Cleanup complete\n");
}

static void perspective() {
	glm_mat4_identity(projectionMatrix);
	glm_perspective(rad(fov), (float)windowWidth / (float)windowHeight, 0.1f, 500.0f, projectionMatrix);
}

static void view(struct CameraData camera) {
	glm_mat4_identity(viewMatrix);
	createViewMatrix(camera, &viewMatrix);
}

static void processInput() {
	if(isKeyPressed(GLFW_KEY_ESCAPE)) {
		sceneShouldClose = true;
	}
	if(isKeyPressed(GLFW_KEY_E)) {			
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	if(isKeyPressed(GLFW_KEY_F)) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	if(isKeyPressed(GLFW_KEY_T)) {
		glfwWaitEvents();
		camera.cameraPos[0] += 1.0f;
	}
	if(isKeyPressed(GLFW_KEY_Y)) {
		camera.cameraPos[2] += 1.0f;
		glfwWaitEvents();
	}
	if(isKeyPressed(GLFW_KEY_W)) {
		moveCameraForwards(&camera, dt * mult);
	}
	if(isKeyPressed(GLFW_KEY_S)) {
		moveCameraBackwards(&camera, dt * mult);
	}
	if(isKeyPressed(GLFW_KEY_A)) {
		strafeCameraLeft(&camera, dt * mult);
	}
	if(isKeyPressed(GLFW_KEY_D)) {
		strafeCameraRight(&camera, dt * mult);
	}
	if(isKeyPressed(GLFW_KEY_UP)) {
		POO += 1;
		//printf("%i\n", POO);
	}
	if(isKeyPressed(GLFW_KEY_DOWN)) {
		far -= 1;
	}
	if(isKeyPressed(GLFW_KEY_SPACE)) {
		camera.cameraPos[1] += 50.0f * dt;
	}
	if(scrollYOffset) {
		fov += (float)scrollYOffset;
		perspective();
	}
}

static void endFrameScroll() {
	scrollXOffset = 0.0;
	scrollYOffset = 0.0;
}

static void framebufferSizeCallback(GLFWwindow *window, int width, int height) {
	windowWidth = width;
	windowHeight = height;
	perspective();
	glViewport(0, 0, width, height);
}

int firstMouse = true;
static void mouseCallback(GLFWwindow *window, double xpos, double ypos) {
	float xMult = 0.5f;
	float yMult = 0.5f;
	if(firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	xoffset = xpos - lastX;
	yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;
	mousePosX = xpos;
	mousePosY = ypos;

	camera.pitch += (float)yoffset * yMult;
	camera.yaw += (float)xoffset * xMult;
	if(camera.pitch > 89.0f) {
		camera.pitch = 89.0f;
	}
	if(camera.pitch < -89.0f) {
		camera.pitch = -89.0f;
	}
}

static void printVec3f(vec3 vector) {
	printf("X: %f Y: %f Z: %f\n", vector[0], vector[1], vector[2]);
}

static float rad(float val) {
	return (val * (float)(M_PI / 180));
}

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
	chunkManager.size = 500;
	chunkManager.index = 0;
	if (chunkManager.chunks == NULL) {
		printf("In init(): allocating memory for ChunkManager->grid failed\n");
		return 0;
	}
	printf("\tGenerating starting chunks\n");
	//int chunkIndex = 0;
	for(int x=0; x<20; x++){
		for(int y=0; y<20; y++){
			//printf("Generating Chunk %i %i %i\n", chunkManager.index, x, y);
			generateChunk(&chunkManager, x, y);
			if (chunkManager.chunks[chunkManager.index-1] == NULL) {
				printf("Error generating chunk %i %i\n", x, y);
			}
			if (chunkManager.index == chunkManager.size) {
				chunkManager.chunks = realloc(chunkManager.chunks, (chunkManager.index * sizeof(Chunk*)) + sizeof(Chunk*) * 500);
				if (chunkManager.chunks == NULL) {
					printf("Error reallocating %zu bytes of memory for chunkManager.chunks\n", ((chunkManager.size * sizeof(Chunk*)) + sizeof(Chunk*) * 500));
				}
				else {
					chunkManager.size += 500;
				}
			}
		}
	}
	printf("\tPreparing Meshes\n");
	for (int i=0; i < 100; i++) {
		prepareChunkMesh(&chunkManager, i);
	}
	//printf("Preparing chunk\n");
	//prepareChunkMesh(chunkManager.chunks[1]);
	//printf("Vertices: %i\n", chunkManager.chunks[1]->vertices);
	//printArrayFloat(chunkManager.chunks[1]->mesh, 5, chunkManager.chunks[1]->vertices * 5);
	//printArrayInt(chunkManager.chunks[1]->indices, 3, chunkManager.chunks[1]->indiceCount);
	//printf("%i\n", chunkManager.chunks[1]->indiceCount);
	printf("\tPreparing camera\n");
	camera = cameraInit();
	camera.cameraPos[2] = 0.0f;
	camera.cameraPos[1] = 60.0f;
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
	//glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CW);
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
int activeChunks[100];
int renderDistance = 10;

int POO;
static void loop() {
	printf("Loop start\n");
	POO = 0;
	sceneShouldClose = false;
	glUseProgram(shaderProgram);
	prepareCubeRender();
	while (!glfwWindowShouldClose(window) && !sceneShouldClose) {
		dt = endTime - startTime;
		startTime = (float)glfwGetTime();
		printf("%f, %f, %f\n", camera.cameraPos[0], camera.cameraPos[1], camera.cameraPos[2]);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		updateCameraFront(&camera);
		view(camera);
		perspective();
		glm_mat4_mul(projectionMatrix, viewMatrix, shaderMatrix);
		setShaderMat4("projection", projectionMatrix, shaderProgram);
		setShaderMat4("projectionTimesView", shaderMatrix, shaderProgram);
		//printf("Rending block\n");
		prepareCubeRender();
		renderBlock(CRAFTING_TABLE_BLOCK, craftingTableLocation, 1.0f, shaderProgram);
		mat4 frustum;
		glm_frustum(0.0f, 10, 0.0f, 10, near, far, frustum);
		vec3 loc = {0.0f, 0.0f, 0.0f};

		for(int x = -camera.cameraPos[0]; x < camera.cameraPos[0]; x++) {
			for(int y = -camera.cameraPos[2]; y < camera.cameraPos[2]; y++) {
				
			}
		}
		
		for(int i=0; i<chunkManager.index; i++) {
			renderChunkMesh(chunkManager.chunks[i], shaderProgram);
		}

		processInput();
		glfwSwapBuffers(window);
		endFrameScroll();
		glfwPollEvents();
		endTime = (float)glfwGetTime();
	}
}
	
// get rid of entities and everything
static void cleanup() {
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
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
	if(isKeyPressed(GLFW_KEY_E)) {			
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	if(isKeyPressed(GLFW_KEY_F)) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	if(isKeyPressed(GLFW_KEY_T)) {
		camera.cameraPos[0] += 1.0f;
		glfwWaitEvents();
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
		printf("%i\n", POO);
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

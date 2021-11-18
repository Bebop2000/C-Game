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


static int init(GLFWwindow *window);
static void loop(GLFWwindow *window);
static void cleanup();
static void perspective();
static void view(struct CameraData camera);
static void processInput();
static void blockSetLocation(Block *block, float in[3]);
static void blockSetRotation(Block *block, float in[3]);
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
vec3 floorLoc = {0.0, -1.0, 0.0};
vec3 floorRot = {M_PI / 4.0f, 0.0f, 0.0f};
Chunk testChunk;

void runTestScene(GLFWwindow *window) {
	if(init(window)) {
		loop(window);
	}
	else{
		printf("Failed to initialize testScene\n");
	}
	cleanup();
}

static int init(GLFWwindow *window) {
	printf("Initializing testScene\n");
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	glfwSetCursorPosCallback(window, mouseCallback);
	framebufferSizeCallback(window, 960, 540);
	setClearColour(48, 117, 186, 255);
	shaderProgram = compileShaders("../res/shaders/defaultVertexShader.glsl",
								   "../res/shaders/defaultFragShader.glsl");
	if(!shaderProgram) {
		printf("Error compiling default shader\n");
		return 0;
	}

	testChunk = generateChunk();

	camera = cameraInit();
	camera.cameraPos[2] = -4.0f;
	camera.cameraPos[0] = 0.0f;
	camera.useFront = true;
	view(camera);
	perspective();

	rendererInit();
	blockTexturesInit();

	glUseProgram(shaderProgram);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CCW);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	return 1;
}

float startTime = 0.0f;
float endTime = 0.0f;
float dt = 0.0f;
float mult = 10.0f;
float shiftMult = 2.0f;
float shiftMultCache = 0.0f;
bool sceneShouldClose;
bool cull = false;


static void loop(GLFWwindow *window) {
	sceneShouldClose = false;
	glUseProgram(shaderProgram);
	while (!glfwWindowShouldClose(window) && !sceneShouldClose) {
		dt = endTime - startTime;
		startTime = (float)glfwGetTime();
		processInput();
		printf("FPS: %f\n", 1.0f/dt);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		updateCameraFront(&camera);
		view(camera);
		perspective();
		glm_mat4_mul(projectionMatrix, viewMatrix, shaderMatrix);
		setShaderMat4("projection", projectionMatrix, shaderProgram);
		setShaderMat4("projectionTimesView", shaderMatrix, shaderProgram);
		setShaderInt("instanced", 0, shaderProgram);
		renderBlock(CRAFTING_TABLE_BLOCK, craftingTableLocation, 1.0f, shaderProgram);
		renderQuad(FLOOR, floorLoc, 100.0f, shaderProgram);
		prepareCubeRender();
		for(int x=0; x<16; x++){
			for(int z=0; z<16; z++){
				for(int y=0; y<255; y++){
					vec3 tmpLoc = {x*2, y*2, z*2};
					if(y+1 < 255){
						if(testChunk.grid[y+1] == AIR){
							renderBlock(testChunk.grid[x][z][y], tmpLoc, 1.0f, shaderProgram);
						}
					}
				}
			}
		}


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
	glm_perspective(rad(fov), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f, projectionMatrix);
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
	if(isKeyPressed(GLFW_KEY_1)) {
		glEnable(GL_CULL_FACE);
	}
	if(isKeyPressed(GLFW_KEY_2)) {
		glDisable(GL_CULL_FACE);
	}
	if(isKeyPressed(GLFW_KEY_T)) {
		camera.pitch = 0.0f;
		camera.yaw = 0.0f;
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
		mult += dt * 10;
	}
	if(isKeyPressed(GLFW_KEY_DOWN)) {
		mult -= dt * 10;
	}
	if(isKeyPressed(GLFW_KEY_SPACE)) {
		camera.cameraPos[1] += mult / 2.0f;
	}
	if(scrollYOffset) {
		fov += (float)scrollYOffset;
		perspective();
	}
	if(isKeyPressed(GLFW_KEY_C)) {
		if(cull == false) {
			cull = true;
		}
		else{
			cull = false;
		}
		if(cull) {
			glEnable(GL_CULL_FACE);
		}
		else{
			glDisable(GL_CULL_FACE);
		}
	}
}

static void blockSetLocation(Block *block, float in[3]) {
	for(int i = 0; i < 3; i++) {
		(*block).location[i] = in[i];
	}
}

static void blockSetRotation(Block *block, float in[3]) {
	for(int i = 0; i < 3; i++) {
		(*block).rotation[i] = in[i];
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

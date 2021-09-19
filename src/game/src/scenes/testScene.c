#include "core.h"
#include "testScene.h"
#include "input.h"
#include "window.h"
#include "shaderProgram.h"
#include "texture.h"
#include "blocks/block.h"
#include "blocks/blockTextures.h"
#include "render.h"
#include "camera.h"
#include <math.h>

static int init(GLFWwindow* window);
static void loop(GLFWwindow* window);
static void cleanup();
static void perspective();
static void view(struct CameraData camera);
static void blockSetLocation(Block* block, float in[3]);
static void blockSetRotation(Block* block, float in[3]);
static void endFrameScroll();
static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
static void printVec3f(vec3 vector);
static float rad(float val);

unsigned int shaderProgram;

Block craftingTable;
Block roseBlock;

CameraData camera;
mat4 viewMatrix;
mat4 projectionMatrix;
mat4 shaderMatrix;		// shaderMatrix is the projection matrix multiplied by the view matrix, which is then sent to the vertex shader
float pitch = 0.0f;
float yaw = -90.0f;
float fov = 45.0f;

vec3 craftingTableLocation = { 0.0f, -0.0f, 0.0f };
vec3 roseLocation = { 0.0f, 2.0f, 0.0f };

int windowWidth;
int windowHeight;

void runTestScene(GLFWwindow* window)
{
	if(init(window))
	{
		loop(window);
	}
	else
	{
		printf("Failed to initialize testScene\n");
	}
	cleanup();
}

static int init(GLFWwindow* window)
{
	printf("Initializing testScene\n");
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	glfwSetCursorPosCallback(window, mouseCallback);

	framebufferSizeCallback(window, 960, 540);
	setClearColour(48, 117, 186, 255);	

	shaderProgram = compileShaders("C:/projects/C version/C version/engine/shaders/defaultVertexShader.glsl", "C:/projects/C version/C version/engine/shaders/defaultFragShader.glsl");
	if (!shaderProgram)
	{
		printf("Error compiling shader\n");
		return 0;
	}
	glUseProgram(shaderProgram);
	glEnable(GL_DEPTH_TEST);

	camera = cameraInit();
	camera.cameraPos[2] = -5.0f;
	camera.useFront = false;
	view(camera);
	perspective();

	rendererInit();
	blockTexturesInit();

	craftingTable = craftingTableBlockInit();
	roseBlock = roseBlockInit();

	blockSetLocation(&craftingTable, craftingTableLocation);
	blockSetLocation(&roseBlock, roseLocation);
	return 1;
}

static void loop(GLFWwindow* window)
{
	bool sceneShouldClose = false;
	bool viewChanged = 0;

	glUseProgram(shaderProgram);

	while (!glfwWindowShouldClose(window) && !sceneShouldClose)
	{
		if (isKeyPressed(GLFW_KEY_ESCAPE))
		{
			sceneShouldClose = true;
		}
		if (isKeyPressed(GLFW_KEY_E))
		{
			camera.useFront = true;
		}
		if (isKeyPressed(GLFW_KEY_F))
		{
			camera.useFront = false;
		}
		if (isKeyPressed(GLFW_KEY_T))
		{
			camera.pitch = 0.0f;
			camera.yaw = 0.0f;
		}
		if (isKeyPressed(GLFW_KEY_W))
		{
			moveCameraForwards(&camera, 0.1f);
		}
		if (scrollYOffset)
		{
			fov += (float)scrollYOffset;
			perspective();
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		updateCameraFront(&camera);
		view(camera);
		glm_mat4_mul(projectionMatrix, viewMatrix, shaderMatrix);
		setShaderMat4("projectionTimesView", shaderMatrix, shaderProgram);

		renderBlock(craftingTable, shaderProgram);
		renderFlower(roseBlock, shaderProgram);

		glfwSwapBuffers(window);
		endFrameScroll();
		glfwPollEvents();
	}
}

// get rid of entities and everything
static void cleanup()
{

}

static void perspective()
{
	glm_mat4_identity(projectionMatrix);
	glm_perspective(rad(fov), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f, projectionMatrix);
}

static void view(struct CameraData camera)
{
	glm_mat4_identity(viewMatrix);
	createViewMatrix(camera, &viewMatrix);
}


static void blockSetLocation(Block* block, float in[3])
{
	for (int i = 0; i < 3; i++)
	{
		(*block).location[i] = in[i];
	}
}

static void blockSetRotation(Block* block, float in[3])
{
	for (int i = 0; i < 3; i++)
	{
		(*block).rotation[i] = in[i];
	}
}

static void endFrameScroll()
{
	scrollXOffset = 0.0;
	scrollYOffset = 0.0;
}

static void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	windowWidth = width;
	windowHeight = height;
	perspective();
	glViewport(0, 0, width, height);
}

int firstMouse = true;
static void mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	float xMult = 0.5f;
	float yMult = 0.5f;
	if (firstMouse)
	{
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
	if (camera.pitch > 89.0f)
	{
		camera.pitch = 89.0f;
	}
	if (camera.pitch < -89.0f)
	{
		camera.pitch = -89.0f;
	}
}

static void printVec3f(vec3 vector)
{
	printf("X: %f Y: %f Z: %f\n", vector[0], vector[1], vector[2]);
}

static float rad(float val)
{

	return (val * (float)(M_PI / 180));
}

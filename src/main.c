#include "core.h"
#include "input.h"
#include "window.h"
#include "scenes/testScene.h"
#include "noise.h"

Scene nextScene;
void framebufferSizeCallbackM(GLFWwindow* window, int width, int height);
int main() {

	GLFWwindow* window = makeWindow(960, 540, "beans");
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glfwSetKeyCallback(window, keyCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetCursorPosCallback(window, mousePosCallback);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallbackM);
	glfwSetScrollCallback(window, mouseScrollCallback);
	glfwSetWindowAspectRatio(window, 16, 9);

	double const TARGET_FPS = 60.0;

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if(isKeyPressed(GLFW_KEY_ESCAPE)) {
			glfwSetWindowShouldClose(window, GLFW_TRUE);
		}
		if(nextScene == testScene) {
			runTestScene(window);
		}
		nextScene = menuScene;
		if (isKeyPressed(GLFW_KEY_P)) {
			nextScene = testScene;
		}
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}


void framebufferSizeCallbackM(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}
#include "core.h"
#include "input.h"


bool keysPressed[360];
bool mouseButtonsPressed[10];
double mousePosX;
double mousePosY;
double scrollXOffset;
double scrollYOffset;
double lastX = 0.0;
double lastY = 0.0;
double xoffset;
double yoffset;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	keysPressed[key] = (action == GLFW_PRESS) || (action == GLFW_REPEAT);
}

void mousePosCallback(GLFWwindow* window, double xpos, double ypos) {
	mousePosX = xpos;
	mousePosY = ypos;

}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
	mouseButtonsPressed[button] = (action == GLFW_PRESS) || (action == GLFW_REPEAT);
}

void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
	scrollXOffset = xoffset;
	scrollYOffset = yoffset;
}

bool isKeyPressed(int key) {
	return keysPressed[key];
}

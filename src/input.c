#include "core.h"
#include "input.h"


bool keysPressed[360];

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	keysPressed[key] = (action == GLFW_PRESS) || (action == GLFW_REPEAT);
}

bool isKeyPressed(int key) {
	return keysPressed[key];
}

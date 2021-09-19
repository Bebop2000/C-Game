#pragma once

extern bool keysPressed[360];
extern bool mouseButtonsPressed[10];
extern double mousePosX;
extern double mousePosY;
extern double scrollXOffset;
extern double scrollYOffset;
double lastX;
double lastY;
extern double xoffset;
extern double yoffset;

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mousePosCallback(GLFWwindow* window, double xpos, double ypos);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
bool isKeyPressed(int key);


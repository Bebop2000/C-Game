#pragma once
#include "core.h"

extern int windowWidth;
extern int windowHeight;

GLFWwindow* makeWindow(int width, int height, const char* title);
void setClearColour(float r, float g, float b, float a);


#ifndef CORE_H
#define CORE_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../vendor/glad/glad/glad.h"
#include <GLFW/glfw3.h>

#include "../vendor/stb_image.h"
#include "../vendor/cglm/mat4.h"
#include "../vendor/cglm/vec3.h"
#include "../vendor/cglm/vec2.h"
#include "../vendor/cglm/affine.h"
#include "../vendor/cglm/cam.h"

typedef enum{
	testScene, menuScene
} Scene;



//extern Scene nextScene;

#endif
#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "stb_image.h"
#include "cglm/mat4.h"
#include "cglm/vec3.h"
#include "cglm/vec2.h"
#include "cglm/affine.h"
#include "cglm/cam.h"

typedef enum
{
	testScene, menuScene
} Scene;



//extern Scene nextScene;
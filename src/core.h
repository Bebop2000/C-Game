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

typedef unsigned char byte;

// right to left
#define BIT8 0x80	//10000000
#define BIT7 0x40	//01000000
#define BIT6 0x20	//00100000
#define BIT5 0x10	//00010000
#define BIT4 0x08	//00001000
#define BIT3 0x04	//00000100
#define BIT2 0x02	//00000010
#define BIT1 0x01	//00000001

//extern Scene nextScene;

#endif
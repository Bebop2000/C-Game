#pragma once

#include "core.h"
#include "cglm/mat4.h"
#include "cglm/vec3.h"




unsigned int compileShaders(const char* vertexPath, const char* fragPath);
void setShaderInt(const char* name, int value, GLuint shaderProgram);
void setShaderMat4(const char* name, mat4 mat, GLuint shaderProgram);
void setShaderMat3(const char* name, mat3 mat, GLuint shaderProgram);
void setShaderVec3(const char* name, vec3 vec, GLuint shaderProgram);
void setShaderVec2(const char* name, vec2 vec, GLuint shaderProgram);
void setShaderFloat(const char* name, float value, GLuint shaderProgram);
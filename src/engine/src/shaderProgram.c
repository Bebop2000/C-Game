#include "core.h"
#include "shaderProgram.h"

#include <unistd.h>

static char* readFile(const char* filepath)
{
	char* buffer;
	long numbytes;
	FILE* file = fopen(filepath, "r");
	if (file == NULL)
	{
		printf("Error: Couldn't open shader file\n");
		return NULL;
	}
	else
	{
		fseek(file, 0L, SEEK_END);
		numbytes = ftell(file);
		fseek(file, 0L, SEEK_SET);
		buffer = (char*)calloc(numbytes, sizeof(char));
		if (buffer == NULL)
		{
			return "";
		}
		fread(buffer, sizeof(char), numbytes, file);
		fclose(file);
		return buffer;
	}
}
unsigned int compileShaders(const char* vertexPath, const char* fragPath)
{
	const char* vertexSource = readFile(vertexPath);
	const char* fragSource = readFile(fragPath);
	int success;
	char infoLog[512];

	//compile vertex shader
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderID, 1, &vertexSource, NULL);
	glCompileShader(vertexShaderID);
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShaderID, 512, NULL, infoLog);
		printf("Error compiling vertex shader:\n%s\n", infoLog);
	}
	else
	{
		printf("Vertex shader compiled successfully\n");
	}

	//compile fragment shader
	unsigned int fragmentShaderID;
	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderID, 1, &fragSource, NULL);
	glCompileShader(fragmentShaderID);
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShaderID, 512, NULL, infoLog);
		printf("Error compiling vertex shader:\n%s\n", infoLog);
	}
	else
	{
		printf("Fragment shader compiled successfully\n");
	}

	// attach shaders to shader program and compile
	GLuint shaderProgramID = glCreateProgram();
	glAttachShader(shaderProgramID, vertexShaderID);
	glAttachShader(shaderProgramID, fragmentShaderID);
	glLinkProgram(shaderProgramID);
	glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgramID, 512, NULL, infoLog);
		printf("Error linking shaders:\n%s\n", infoLog);
	}
	else
	{
		printf("Shaders linked successfully\n");
	}

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	return shaderProgramID;
}


void setShaderInt(const char* name, int value, GLuint shaderProgram)
{
	glUniform1i(glGetUniformLocation(shaderProgram, name), value);
}
void setShaderMat4(const char* name, mat4 mat, GLuint shaderProgram)
{
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, name), 1, GL_FALSE, (float*)(mat));
}
void setShaderMat3(const char* name, mat3 mat, GLuint shaderProgram)
{
	glUniformMatrix3fv(glGetUniformLocation(shaderProgram, name), 1, GL_FALSE, (float*)mat);
}
void setShaderVec2(const char* name, vec2 vec, GLuint shaderProgram)
{
	glUniform2fv(glGetUniformLocation(shaderProgram, name), 1, vec);
}
void setShaderVec3(const char* name, vec3 vec, GLuint shaderProgram)
{
	glUniform3fv(glGetUniformLocation(shaderProgram, name), 1, vec);
}
void setShaderFloat(const char* name, float value, GLuint shaderProgram)
{
	glUniform1f(glGetUniformLocation(shaderProgram, name), value);
}
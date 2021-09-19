#include "core.h"
#include "window.h"

int windowWidth;
int windowHeight;

GLFWwindow* makeWindow(int width, int height, const char* title)
{
	if (!glfwInit())
	{
		printf("Failed to create GLFW window\n");
		glfwTerminate();
	}
	GLFWwindow* window;
	window = glfwCreateWindow(width, height, title, 0, 0);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialize GLAD\n");
	}

	glfwShowWindow(window);

	return window;
}

void setClearColour(float r, float g, float b, float a)
{
	glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
}



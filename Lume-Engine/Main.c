#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "Main.h"
#include "Renderer.h"

int main()
{
	// Check if GLFW FUnctions Correctly
	if (!glfwInit()) {
		printf("MAIN.C::GLFW_INITIATION::ERROR");
		return-1;
	}

	// Initiate GLFW and specify which version we are using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow* WindowInstance = glfwCreateWindow(900, 900, "Lume-Egnine", NULL, NULL);
	if (!WindowInstance) {
		printf("MAIN.C::WINDOW_CREATION:ERROR %s\n", WindowInstance ? "true" : "false");
		return -2;
	}
	glfwMakeContextCurrent(WindowInstance);
	glfwSetFramebufferSizeCallback(WindowInstance, GLFWFrameBufferSizeCallBack); //for screen sizing

	// Initalize Glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("MAIN.C::GLAD_INITIATION:ERROR");
		return -1;
	}

	// Game Loop shit
	while (!glfwWindowShouldClose(WindowInstance)) {
		RenderFrame(WindowInstance);
	}
	
	glfwTerminate();

	return 0;
}

// Get Called when the screen size Changes
// ALso applies that screen size to the viewport
/*-----------------------------------------------------------------------------------------------------------*/
void GLFWFrameBufferSizeCallBack(GLFWwindow* WindowInstance, int WindowWidth, int WindowHeight) {
	glViewport(0, 0, WindowWidth, WindowHeight);
	return;
}
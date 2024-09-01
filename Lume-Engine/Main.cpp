#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Main.hpp"
#include "Renderer.hpp"

// Main Stuff
/*-----------------------------------------------------------------------------------------------------------*/
int main()
{
	// Check if GLFW FUnctions Correctly
	if (!glfwInit()) {
		std::cout << "MAIN.CPP::GLFW_INITIATION::ERROR" << std::endl;
		return-1;
	}

	// Initiate GLFW and specify which version we are using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* WindowInstance = glfwCreateWindow(900, 900, "Lume-Egnine", NULL, NULL);
	if (!WindowInstance) {
		std::cout << "MAIN.CPP::WINDOW_CREATION:ERROR" << WindowInstance << std::endl;
		return -2;
	}
	glfwMakeContextCurrent(WindowInstance);
	glfwSetFramebufferSizeCallback(WindowInstance, FrameBufferSizeCallback); //  for screen sizing

	// Initalize Glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "MAIN.CPP::GLAD_INITIATION:ERROR" << std::endl;
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
void FrameBufferSizeCallback(GLFWwindow* WindowInstance, int WindowWidth, int WindowHeight) {
	glViewport(0, 0, WindowWidth, WindowHeight);
	return;
}
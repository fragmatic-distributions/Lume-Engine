#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Main.hpp"
#include "Core/Renderer.hpp"
#include "game/Scene.hpp"

bool WireFrameState = false;
bool WireFramePressed = false;
void ProcessInput(GLFWwindow* WindowInstnace);

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

	unsigned int WindowWidth = 900;
	unsigned int WindowHeight = 900;

	GLFWwindow* WindowInstance = glfwCreateWindow(WindowWidth, WindowHeight, "Lume-Egnine", NULL, NULL);
	Renderer::ScreenUpdateCallback(&WindowWidth, &WindowHeight);
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

	glEnable(GL_DEPTH_TEST);

	Scene GameScene;
	GameScene.Load();
	// Game Loop shit
	while (!glfwWindowShouldClose(WindowInstance)) {
		ProcessInput(WindowInstance);
		Renderer::RenderFrame(WindowInstance);
		GameScene.Tick(WindowInstance);
	}

	glfwTerminate();

	return 0;
}

// Input Handling
void ProcessInput(GLFWwindow* WindowInstnace) {
	if (glfwGetKey(WindowInstnace, GLFW_KEY_F1) == GLFW_PRESS && !WireFramePressed) {
		WireFramePressed = true;
		if (!WireFrameState) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			WireFrameState = true;
		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			WireFrameState = false;
		}
	}
	else if (glfwGetKey(WindowInstnace, GLFW_KEY_F1) == GLFW_RELEASE) {
		WireFramePressed = false;
	}
}

// Get Called when the screen size Changes
// ALso applies that screen size to the viewport
/*-----------------------------------------------------------------------------------------------------------*/
void FrameBufferSizeCallback(GLFWwindow* WindowInstance, int WindowWidth, int WindowHeight) {
	unsigned int Width = unsigned(WindowWidth);
	unsigned int Height = unsigned(WindowHeight);
	Renderer::ScreenUpdateCallback(&Width, &Height);

	glViewport(0, 0, WindowWidth, WindowHeight);
	return;
}
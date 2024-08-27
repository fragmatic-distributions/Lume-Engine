#include <GLFW/glfw3.h>
#include <stdio.h>

#include "Main.h"

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
		printf("MAIN.C::WINDOW_CREATION:ERROR %d\n", WindowInstance);
		return -2;
	}

	glfwMakeContextCurrent(WindowInstance);
	glfwSetFramebufferSizeCallback(WindowInstance, GLFWFrameBufferSizeCallBack); //for screen sizing

	// Game Loop shit
	while (!glfwWindowShouldClose(WindowInstance)) {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(WindowInstance);
		glfwPollEvents();
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
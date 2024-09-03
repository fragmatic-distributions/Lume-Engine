#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <STBI/stbi.h>
#include <filesystem>

#include "Renderer.hpp"
#include "../game/Scene.hpp"


// Draws a frame to the screen
/*-----------------------------------------------------------------------------------------------------------*/
void RenderFrame(GLFWwindow* WindowInstance) {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// Draw Quads
	std::vector<Quad*> QuadCollection = Scene::Quads;
	for (int i = 0; i < QuadCollection.size(); i++) {
		QuadCollection[i]->Draw();
	}

	glfwSwapBuffers(WindowInstance);
	glfwPollEvents();
}
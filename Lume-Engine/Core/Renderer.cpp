#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <STBI/stbi.h>
#include <filesystem>

#include "Renderer.hpp"
#include "../game/Scene.hpp"

void Renderer::ScreenUpdateCallback(unsigned int* WindowWidth, unsigned int* WindowHeight) {
	Renderer::SCRheight = *WindowHeight;
	Renderer::SCRwidth = *WindowWidth;
}

// Draws a frame to the screen
/*-----------------------------------------------------------------------------------------------------------*/
void Renderer::RenderFrame(GLFWwindow* WindowInstance) {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw Quads
	std::vector<Quad*> QuadCollection = Scene::Quads;
	for (int i = 0; i < QuadCollection.size(); i++) {
		QuadCollection[i]->Draw();
	}

	std::vector<Cube*> CubeCollection = Scene::Cubes;
	for (int i = 0; i < CubeCollection.size(); i++) {
		CubeCollection[i]->Draw();
	}

	glfwSwapBuffers(WindowInstance);
	glfwPollEvents();
}
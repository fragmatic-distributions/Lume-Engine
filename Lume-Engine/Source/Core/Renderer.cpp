#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <map>
#include <filesystem>
#include "Renderer.hpp"
#include "../game/Scene.hpp"
#include "../game/Camera.hpp"

void Renderer::ScreenUpdateCallback(unsigned int* WindowWidth, unsigned int* WindowHeight) {
	Renderer::SCRheight = *WindowHeight;
	Renderer::SCRwidth = *WindowWidth;

	Camera::SetPrespectiveMatrix(&Renderer::SCRwidth, &Renderer::SCRheight, &Renderer::FOV);
}

// Draws a frame to the screen
void Renderer::RenderFrame(GLFWwindow* WindowInstance) {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw Quads
	std::map<std::string, Quad*> QuadCollection = Scene::Quads;
	std::map<std::string, Quad*>::iterator it;

	for (it = QuadCollection.begin(); it != QuadCollection.end(); it++) {
		it->second->Draw();
	}

	// Draws Cubes
	std::map<std::string, Cube*> CubeCollection = Scene::Cubes;
	std::map<std::string, Cube*>::iterator CubeIt;

	for (CubeIt = CubeCollection.begin(); CubeIt != CubeCollection.end(); CubeIt++) {
		CubeIt->second->Draw();
	}

	// Draws Meshes
	std::map<std::string, Mesh*> MeshCollection = Scene::Meshes;
	std::map<std::string, Mesh*>::iterator MeshIt;

	for (MeshIt = MeshCollection.begin(); MeshIt != MeshCollection.end(); MeshIt++) {
		MeshIt->second->Draw();
	}

	glfwSwapBuffers(WindowInstance);
	glfwPollEvents();
}
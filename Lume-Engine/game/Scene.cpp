#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Scene.hpp"
#include "Camera.hpp"

std::map<std::string, Quad*> Scene::Quads;
std::map<std::string, Cube*> Scene::Cubes;

// just a fyi, shit gets instatiated on the heap here, so please for the love of god, clean after your ass
// Thank you very much

void Scene::Load() {
	Quad* Quad01 = new Quad();
	Scene::Quads["Quad"] = Quad01;

	glm::mat4 QuadMat = glm::mat4(1.0f);
	QuadMat = glm::translate(QuadMat, glm::vec3(0.5, 0, 0));
	//QuadMat = glm::rotate(QuadMat, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	Quad01->SetTexture("../Graphics/Tex/Test2.png", LumeTexture::RGBA);
	Quad01->SetTransform(QuadMat);


	Cube* Cube02 = new Cube();
	Scene::Cubes["Cube01"] = Cube02;

	glm::mat4 CubeMat2 = glm::mat4(1.0f);
	CubeMat2 = glm::rotate(CubeMat2, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, -2.0f));

	Cube02->SetTexture("../Graphics/Tex/Test.png", LumeTexture::RGBA);
	Cube02->SetTransform(CubeMat2);
}

void Scene::Tick(GLFWwindow* WindowInstance) {
	glm::mat4 CubeMat2 = glm::mat4(1.0f);
	CubeMat2 = glm::rotate(CubeMat2, (float)glfwGetTime(), glm::vec3(1.0f, 0.0f, -2.0f));

	Scene::Cubes["Cube01"]->SetTransform(CubeMat2);
}

// Memory Clean up smh
void Scene::Destroy() {
	std::map<std::string, Quad*>::iterator QuadIt;
	for (QuadIt = Scene::Quads.begin(); QuadIt != Scene::Quads.end(); QuadIt++) {
		delete QuadIt->second;
	}

	std::map<std::string, Cube*>::iterator CubeIt;
	for (CubeIt = Scene::Cubes.begin(); CubeIt != Scene::Cubes.end(); CubeIt++) {
		delete CubeIt->second;
	}
}
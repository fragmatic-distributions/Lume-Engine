#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Scene.hpp"

std::vector<Quad*> Scene::Quads;
std::vector<Cube*> Scene::Cubes;

void Scene::Load() {
	glm::vec3 cubePositions[] = {
		glm::vec3(0.5f,  0.0f,  -2.0f),
		glm::vec3( -1.5f,  0.0f,  -2.0f),
		glm::vec3(-2.5f,  0.0f,  -2.0f),
		glm::vec3(-3.5f,  0.0f,  -2.0f),
	};

	Quad* Quad01 = new Quad();
	Scene::Quads.push_back(Quad01);

	glm::mat4 QuadMat = glm::mat4(1.0f);
	QuadMat = glm::translate(QuadMat, glm::vec3(0.5, 0, 0));
	QuadMat = glm::rotate(QuadMat, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));

	Quad01->SetTexture("../Graphics/Tex/Test2.png", LumeTexture::RGBA);
	Quad01->SetTransform(QuadMat);


	Cube* Cube02 = new Cube();
	Scene::Cubes.push_back(Cube02);

	glm::mat4 CubeMat2 = glm::mat4(1.0f);
	//CubeMat2 = glm::translate(CubeMat2, glm::vec3(-0.5f, 0.0f, -2.0f));
	CubeMat2 = glm::rotate(CubeMat2, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, -2.0f));

	Cube02->SetTexture("../Graphics/Tex/Test.png", LumeTexture::RGBA);
	Cube02->SetTransform(CubeMat2);
}
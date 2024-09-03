#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Scene.hpp"

std::vector<Quad*> Scene::Quads;

void Scene::Load() {
	Quad* Quad01 = new Quad();
	Scene::Quads.push_back(Quad01);

	glm::mat4 QuadMat = glm::mat4(1.0f);
	QuadMat = glm::translate(QuadMat, glm::vec3(0.5, 0, 0));

	Quad01->SetTexture("../Graphics/Tex/Test2.png");
	Quad01->SetTransform(QuadMat);


	Quad* Quad02 = new Quad();
	Scene::Quads.push_back(Quad02);

	glm::mat4 QuadMat2 = glm::mat4(1.0f);
	QuadMat2 = glm::translate(QuadMat2, glm::vec3(-0.5, 0, 0));

	Quad02->SetTransform(QuadMat2);
}
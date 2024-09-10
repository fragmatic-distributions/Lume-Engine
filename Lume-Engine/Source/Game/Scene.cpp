#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <map>
#include <GLFW/glfw3.h>
#include "GameObjects.hpp"
#include "Scene.hpp"
#include "Camera.hpp"
#include "../Graphics/Model.hpp"

std::map<std::string, Quad*> Scene::Quads;
std::map<std::string, Cube*> Scene::Cubes;
std::map<std::string, Mesh*> Scene::Meshes;

// just a fyi, shit gets instatiated on the heap here, so please for the love of god, clean after your ass
// Thank you very much

void Scene::Load() {
	//Mesh* Test = new Mesh("Graphics/Gltf/concrete_cat_statue.gltf");
	//Scene::Meshes["Test"] = Test;

	//glm::mat4 TestMat = glm::mat4(1.0f);
	//Test->SetTexture("Graphics/Tex/Concrete_Cat_Diff.png", LumeTexture::RGB);
	//Test->SetTransform(TestMat);

	Mesh* MeshInstance = new Mesh();
	Scene::Meshes["Rat"] = MeshInstance;
	MeshInstance->SetShader("Source/Shaders/Default.vert", "Source/Shaders/Default.frag");
	MeshInstance->BufferMesh("Graphics/Gltf/wooden_picnic_table.gltf");
	MeshInstance->SetTransform(glm::mat4(1.0f));
}

void Scene::Tick(GLFWwindow* WindowInstance) {

}

// Memory Clean up smh
void Scene::Destroy() {
	std::map<std::string, Quad*>::iterator QuadIt;
	for (QuadIt = Scene::Quads.begin(); QuadIt != Scene::Quads.end(); QuadIt++) {
		QuadIt->second->Destroy();
		delete QuadIt->second;
	}

	std::map<std::string, Cube*>::iterator CubeIt;
	for (CubeIt = Scene::Cubes.begin(); CubeIt != Scene::Cubes.end(); CubeIt++) {
		CubeIt->second->Destroy();
		delete CubeIt->second;
	}

	std::map<std::string, Mesh*>::iterator MeshIt;
	for (MeshIt = Scene::Meshes.begin(); MeshIt != Scene::Meshes.end(); MeshIt++) {
		MeshIt->second->Destroy();
		delete MeshIt->second;
	}
}
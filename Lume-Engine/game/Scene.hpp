#include <iostream>
#include <map>
#include <GLFW/glfw3.h>
#include "GameObjects.hpp"

class Scene {
public:
	static std::map<std::string, Quad*> Quads;
	static std::map<std::string,Cube*> Cubes;

	void Load();
	void Tick(GLFWwindow* WindowInstance);
};
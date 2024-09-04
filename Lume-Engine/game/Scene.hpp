#include <iostream>
#include <vector>

#include "GameObjects.hpp"

class Scene {
public:
	static std::vector<Quad*> Quads;
	static std::vector<Cube*> Cubes;

	void Load();
};
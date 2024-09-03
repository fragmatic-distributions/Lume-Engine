#include <iostream>
#include <vector>

#include "GameObjects.hpp"

class Scene {
public:
	static std::vector<Quad*> Quads;

	void Load();
};
#ifndef UTIL_H
#define UTIL_H
#include <iostream>
#include <glm/glm.hpp>

struct SpatialVectors {
	glm::vec3 FrontVector;
	glm::vec3 UpVector;
	glm::vec3 RightVector;
};

namespace Util {
	std::string GetFileExtension(const char* File);

	SpatialVectors GetSpatialVectors(glm::mat4* Matrix);
}

#endif
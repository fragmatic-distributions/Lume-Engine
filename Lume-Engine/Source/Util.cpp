#include <iostream>
#include <glm/glm.hpp>
#include "Util.hpp"

std::string Util::GetFileExtension(const char* File) {
	std::string StringFile = File;
	std::size_t found = StringFile.find_last_of(".");
	std::string FileExtension = StringFile.substr(found + 1);

	return FileExtension;
}

SpatialVectors Util::GetSpatialVectors(glm::mat4* Matrix) {
	struct SpatialVectors SpatVec;

	SpatVec.FrontVector = glm::vec3((*Matrix)[0][2]
								   ,(*Matrix)[1][2]
								   ,(*Matrix)[2][2]);
	SpatVec.RightVector = glm::vec3((*Matrix)[0][0]
							       ,(*Matrix)[1][0]
							       ,(*Matrix)[2][0]);
	SpatVec.UpVector = glm::vec3((*Matrix)[0][1]
							    ,(*Matrix)[1][1]
							    ,(*Matrix)[2][1]);
	return SpatVec;
}

#pragma once

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Camera {
public:
	static void SetViewMatrix(glm::mat4* CameraMatrix);
	static void SetPrespectiveMatrix(unsigned int* WindowWidth, unsigned int* WindowHeight, float* FOV);

	static glm::mat4* GetViewMatrix();
	static glm::mat4* GetPrespectiveMatrix();
private:

	static glm::mat4 ViewMatrix;
	static glm::mat4 PrespectiveMatrix;
};

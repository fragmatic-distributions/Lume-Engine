#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "../Util.hpp"
#include "Camera.hpp"

glm::mat4 Camera::ViewMatrix = glm::mat4(1.0f);
glm::mat4 Camera::PrespectiveMatrix = glm::mat4(1.0f);

void Camera::SetViewMatrix(glm::mat4* CameraMatrix) {
	Camera::ViewMatrix = *CameraMatrix;
}

void Camera::SetPrespectiveMatrix(unsigned int* WindowWidth, unsigned int* WindowHeight, float* FOV) {
	glm::mat4 PrespectiveMatrix = glm::perspective(glm::radians(*FOV), (float)*WindowWidth / (float)*WindowHeight, 0.1f, 100.0f);

	Camera::PrespectiveMatrix = PrespectiveMatrix;
}

glm::mat4* Camera::GetViewMatrix() {
	return &Camera::ViewMatrix;
}

glm::mat4* Camera::GetPrespectiveMatrix() {
	return &Camera::PrespectiveMatrix;
}

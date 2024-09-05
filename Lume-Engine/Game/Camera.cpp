#include <glm/gtc/matrix_transform.hpp>

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

// Temporary Freeroam camera for beta renderer
// Might have a use for it later...
void Camera::UpdateCameraController(GLFWwindow* WindowInstance) {
	SpatialVectors CameraLookVector = Util::GetSpatialVectors(Camera::GetViewMatrix());
	glm::mat4 CameraDir = glm::mat4(1.0f);

	float CameraSpeed = 0.01f;
	if (glfwGetKey(WindowInstance, GLFW_KEY_W) == GLFW_PRESS) {
		CameraDir = glm::translate(CameraDir, glm::vec3(CameraLookVector.FrontVector * CameraSpeed));
	}
	if (glfwGetKey(WindowInstance, GLFW_KEY_S) == GLFW_PRESS) {
		CameraDir = glm::translate(CameraDir, glm::vec3(-CameraLookVector.FrontVector * CameraSpeed));
	}
	if (glfwGetKey(WindowInstance, GLFW_KEY_D) == GLFW_PRESS) {
		CameraDir = glm::translate(CameraDir, glm::vec3(-CameraLookVector.RightVector * CameraSpeed));
	}
	if (glfwGetKey(WindowInstance, GLFW_KEY_A) == GLFW_PRESS) {
		CameraDir = glm::translate(CameraDir, glm::vec3(CameraLookVector.RightVector * CameraSpeed));
	}

	glm::mat4 ViewMatrix = *Camera::GetViewMatrix();
	ViewMatrix *= CameraDir;

	Camera::SetViewMatrix(&ViewMatrix);
}
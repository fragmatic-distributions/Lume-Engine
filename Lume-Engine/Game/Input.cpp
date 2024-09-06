#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Input.hpp"
#include "../Util.hpp"
#include "Camera.hpp"

bool WireFrameState = false;
bool WireFramePressed = false;

void Input::setGLFWwindow(GLFWwindow* WindowInstance) {
	Input::WindowInstance = WindowInstance;
}

void Input::ProcessInput(GLFWwindow* WindowInstance) {
	Input::UpdateCameraController();

	// Wireframe toggle
	if (glfwGetKey(Input::WindowInstance, GLFW_KEY_1) == GLFW_PRESS && !WireFramePressed) {
		WireFramePressed = true;
		if (!WireFrameState) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			WireFrameState = true;
		}
		else {
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			WireFrameState = false;
		}
	}
	else if (glfwGetKey(Input::WindowInstance, GLFW_KEY_1) == GLFW_RELEASE) {
		WireFramePressed = false;
	}
	// Window Destroying
	if (glfwGetKey(Input::WindowInstance, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwDestroyWindow(Input::WindowInstance);
	}
}

void Input::CursorPosCallback(GLFWwindow* WindowInstance, double Xpos, double Ypos) {

}

// Temporary Freeroam camera for beta renderer
// Might have a use for it later...
void Input::UpdateCameraController() {
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
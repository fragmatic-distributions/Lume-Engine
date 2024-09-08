#include <glm/glm.hpp>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>

#include "Input.hpp"
#include "Camera.hpp"
#include "../Util.hpp"

bool WireFrameState = false;
bool WireFramePressed = false;

glm::vec2 PrevMousePosition = glm::vec2(0.0f);
glm::vec2 SumMouseDeltaPosition = glm::vec2(0.0f);
glm::vec3 CameraPosition = glm::vec3(0.0f);
glm::vec3 RotationVector = glm::vec3(0.0f);

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
	float Fxpos = static_cast<float>(Xpos);
	float Fypos = static_cast<float>(Ypos);

	glm::vec2 MouseDelta = glm::vec2(Fxpos - PrevMousePosition.x, 
								     Fypos - PrevMousePosition.y);
	PrevMousePosition = glm::vec2(Fxpos, Fypos);

	SumMouseDeltaPosition += MouseDelta;
	SumMouseDeltaPosition = glm::vec2(SumMouseDeltaPosition.x, std::clamp(SumMouseDeltaPosition.y, -1000.0f, 1000.0f));

	std::cout << SumMouseDeltaPosition.y << std::endl;

	RotationVector = glm::vec3(SumMouseDeltaPosition.y * 0.1f, SumMouseDeltaPosition.x * 0.1f, 0.0f);
}

// Temporary Freeroam camera for beta renderer
// Might have a use for it later...
void Input::UpdateCameraController() {
	SpatialVectors CameraLookVector = Util::GetSpatialVectors(Camera::GetViewMatrix());

	glm::vec3 SumVectorDir = glm::vec3(0);
	float CameraSpeed = 0.01f;
	if (glfwGetKey(WindowInstance, GLFW_KEY_W) == GLFW_PRESS) {
		SumVectorDir += CameraLookVector.FrontVector * CameraSpeed;
	}
	if (glfwGetKey(WindowInstance, GLFW_KEY_S) == GLFW_PRESS) {
		SumVectorDir += -CameraLookVector.FrontVector * CameraSpeed;
	}
	if (glfwGetKey(WindowInstance, GLFW_KEY_D) == GLFW_PRESS) {
		SumVectorDir += -CameraLookVector.RightVector * CameraSpeed;
	}
	if (glfwGetKey(WindowInstance, GLFW_KEY_A) == GLFW_PRESS) {
		SumVectorDir += CameraLookVector.RightVector * CameraSpeed;
	}
	CameraPosition += SumVectorDir;

	std::cout << RotationVector.x << RotationVector.y << std::endl;

	glm::mat4 ViewMatrix = glm::mat4(1.0f);
	ViewMatrix = glm::rotate(ViewMatrix, glm::radians(RotationVector.x), glm::vec3(1.0f, 0.0f, 0.0f));
	ViewMatrix = glm::rotate(ViewMatrix, glm::radians(RotationVector.y), glm::vec3(0.0f, 1.0f, 0.0f));
	ViewMatrix = glm::translate(ViewMatrix, CameraPosition);

	Camera::SetViewMatrix(&ViewMatrix);
}
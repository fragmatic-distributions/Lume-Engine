#include <glm/glm.hpp>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>
#include <GLFW/glfw3.h>
#include "Input.hpp"
#include "Camera.hpp"
#include "../Util.hpp"

#define CAMERA_SPEED 0.01f

bool WireFrameState = false;
bool WireFramePressed = false;

float PrevMouseX = 0.0f;
float PrevMouseY = 0.0f;

float SumMouseX = 0.0f;
float SumMouseY = 0.0f;

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

	// Set def pos
	if (PrevMouseX + PrevMouseY == 0.0f) {
		PrevMouseX = Fxpos;
		PrevMouseY = Fypos;
		return;
	}

	float MouseDeltaX = Fxpos - PrevMouseX;
	float MouseDeltaY = Fypos - PrevMouseY;

	PrevMouseX = Fxpos;
	PrevMouseY = Fypos;

	SumMouseX += MouseDeltaX;
	SumMouseY += MouseDeltaY;

	SumMouseY = std::clamp(SumMouseY, -600.0f, 600.0f);

	RotationVector = glm::vec3(SumMouseY * 0.1f, SumMouseX * 0.1f, 0.0f);
}

// Temporary Freeroam camera for beta renderer
// Might have a use for it later...
void Input::UpdateCameraController() {
	SpatialVectors CameraLookVector = Util::GetSpatialVectors(Camera::GetViewMatrix());

	glm::vec3 SumVectorDir = glm::vec3(0);
	if (glfwGetKey(WindowInstance, GLFW_KEY_W) == GLFW_PRESS) {
		SumVectorDir += CameraLookVector.FrontVector * CAMERA_SPEED;
	}
	if (glfwGetKey(WindowInstance, GLFW_KEY_S) == GLFW_PRESS) {
		SumVectorDir += -CameraLookVector.FrontVector * CAMERA_SPEED;
	}
	if (glfwGetKey(WindowInstance, GLFW_KEY_D) == GLFW_PRESS) {
		SumVectorDir += -CameraLookVector.RightVector * CAMERA_SPEED;
	}
	if (glfwGetKey(WindowInstance, GLFW_KEY_A) == GLFW_PRESS) {
		SumVectorDir += CameraLookVector.RightVector * CAMERA_SPEED;
	}
	CameraPosition += SumVectorDir;

	glm::mat4 ViewMatrix = glm::mat4(1.0f);
	ViewMatrix = glm::rotate(ViewMatrix, glm::radians(RotationVector.x), glm::vec3(1.0f, 0.0f, 0.0f));
	ViewMatrix = glm::rotate(ViewMatrix, glm::radians(RotationVector.y), glm::vec3(0.0f, 1.0f, 0.0f));
	ViewMatrix = glm::translate(ViewMatrix, CameraPosition);

	Camera::SetViewMatrix(&ViewMatrix);
}
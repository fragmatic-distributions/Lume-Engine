#pragma once

#include <GLFW/glfw3.h>

namespace Input {
	inline GLFWwindow* WindowInstance;

	void setGLFWwindow(GLFWwindow* WindowInstance);

	void ProcessInput(GLFWwindow* WindowInstance);
	void CursorPosCallback(GLFWwindow* WindowInstance, double Xpos, double Ypos);

	void UpdateCameraController();
}
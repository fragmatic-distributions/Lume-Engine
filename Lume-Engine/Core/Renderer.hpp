#pragma once

#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

namespace Renderer {
	inline unsigned int SCRwidth;
	inline unsigned int SCRheight;
	inline unsigned int FOV;

	void ScreenUpdateCallback(unsigned int* WindowWidth, unsigned int* WindowHeight);
	void RenderFrame(GLFWwindow* WindowInstance);
}

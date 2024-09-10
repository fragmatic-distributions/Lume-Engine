#ifndef RENDERER_H
#define RENDERER_H
#include <GLFW/glfw3.h>

namespace Renderer {
	inline unsigned int SCRwidth;
	inline unsigned int SCRheight;
	inline float FOV = 45.0f;

	void ScreenUpdateCallback(unsigned int* WindowWidth, unsigned int* WindowHeight);
	void RenderFrame(GLFWwindow* WindowInstance);
}

#endif
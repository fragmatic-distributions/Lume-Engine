#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <STBI/stbi.h>
#include <filesystem>

#include "Renderer.hpp"
#include "Util.hpp"
#include "Shader.hpp"
#include "texture.hpp"
#include "VertexArray.hpp"

// Test Triangle
void RenderTriangle() {
	float vertices[] = {
		 0.5f,  0.5f, 0.0f,  1.0f, 1.0f,  // top right
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f,  0.0f, 1.0f// top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};


	// Shader Crap
	LumeShader ShaderInstance(LumeShader::VERTEX, LumeShader::FRAGMENT);
	ShaderInstance.CreateShader("Default.vert", "Default.frag");
	ShaderInstance.BindProgram();
	ShaderInstance.SetUniformInt("TextureInstance", 0);

	LumeTexture TextureInstance(LumeTexture::RGBA);
	TextureInstance.LoadTexture("../Graphics/Tex/Test.png");
	TextureInstance.BindTexture(0);

	VertexArray VertexArrayBuffer;
	VertexArrayBuffer.Buffer(VertexArrayBuffer.ARRAY_BUFFER, sizeof(vertices), &vertices, VertexArrayBuffer.STATIC_DRAW);
	VertexArrayBuffer.Buffer(VertexArrayBuffer.ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, VertexArrayBuffer.STATIC_DRAW);
	VertexArrayBuffer.Array(0, 3, 5, 0);
	VertexArrayBuffer.Array(1, 2, 5, 3);

	VertexArrayBuffer.BindArray();
	VertexArrayBuffer.BindBuffer(VertexArrayBuffer.ARRAY_BUFFER);
	VertexArrayBuffer.BindBuffer(VertexArrayBuffer.ELEMENT_ARRAY_BUFFER);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	VertexArrayBuffer.Destroy();
	ShaderInstance.DestroyProgram();
}

// Draws a frame to the screen
/*-----------------------------------------------------------------------------------------------------------*/
void RenderFrame(GLFWwindow* WindowInstance) {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

    RenderTriangle();

	glfwSwapBuffers(WindowInstance);
	glfwPollEvents();
}
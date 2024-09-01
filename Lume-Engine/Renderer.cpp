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

//▒█░░▒█ █▀▀ █▀▀█ ▀▀█▀▀ █▀▀ █░█ 　 ░█▀▀█ █▀▀█ █▀▀█ █▀▀█ █░░█ 　 ▒█▀▀█ █░░█ █▀▀ █▀▀ █▀▀ █▀▀█
//░▒█▒█░ █▀▀ █▄▄▀ ░░█░░ █▀▀ ▄▀▄ 　 ▒█▄▄█ █▄▄▀ █▄▄▀ █▄▄█ █▄▄█ 　 ▒█▀▀▄ █░░█ █▀▀ █▀▀ █▀▀ █▄▄▀
//░░▀▄▀░ ▀▀▀ ▀░▀▀ ░░▀░░ ▀▀▀ ▀░▀ 　 ▒█░▒█ ▀░▀▀ ▀░▀▀ ▀░░▀ ▄▄▄█ 　 ▒█▄▄█ ░▀▀▀ ▀░░ ▀░░ ▀▀▀ ▀░▀▀

/*-----------------------------------------------------------------------------------------------------------*/
unsigned int VertexBufferArray::VertexBuffer(const VertexBufferType VertexBuffer, const size_t VertexByteSize, const void* Vertices, const DrawMode BufferDrawType) {
	GLuint VertexBufferObject;
	glGenBuffers(1, &VertexBufferObject);
	glBindBuffer(VertexBuffer, VertexBufferObject);
	glBufferData(VertexBuffer, VertexByteSize, Vertices, BufferDrawType);

	this->VertexBufferObjects.push_back(VertexBufferObject);

	return VertexBufferObject;
}

// Creates a vertex Array Object
/*-----------------------------------------------------------------------------------------------------------*/
unsigned int VertexBufferArray::VertexArray(const int Index, const int ArraySize, const int Stride, const void* Data) {
	if (!this->VertexArrayObject) {
		glGenVertexArrays(1, &(this->VertexArrayObject));
		glBindVertexArray(this->VertexArrayObject);
	}

	// We can add color to our strides
	// But i opted not to since most of our assets are gonna texture wise
	// This will just hog up uneeded memory, slowing us down in the long run
	glVertexAttribPointer(Index, ArraySize, GL_FLOAT, GL_FALSE, Stride, Data);
	glEnableVertexAttribArray(Index);

	return this->VertexArrayObject;
}

// Binds the vertex array
/*-----------------------------------------------------------------------------------------------------------*/
void VertexBufferArray::BindVertexArray() {
	glBindVertexArray(this->VertexArrayObject);
}

// Call this before doing draw call otherwise shit goes on fire
// Draws the index Buffer
/*-----------------------------------------------------------------------------------------------------------*/
void VertexBufferArray::BindVertexBuffer(const VertexBufferType VertexBuffer, unsigned int* BufferInstance) {
	glBindBuffer(VertexBuffer, *BufferInstance);
}

// Destory a Instance
/*-----------------------------------------------------------------------------------------------------------*/
void VertexBufferArray::Destroy() {
	for (int BufferIncrement = 0; BufferIncrement < this->VertexBufferObjects.size(); BufferIncrement++) {
		glDeleteBuffers(1, &(this->VertexBufferObjects[BufferIncrement]));
	}
	glDeleteVertexArrays(1, &(this->VertexArrayObject));
}


//▒█▀▀█ █▀▀ █▀▀▄ █▀▀▄ █▀▀ █▀▀█ █▀▀ █▀▀█
//▒█▄▄▀ █▀▀ █░░█ █░░█ █▀▀ █▄▄▀ █▀▀ █▄▄▀
//▒█░▒█ ▀▀▀ ▀░░▀ ▀▀▀░ ▀▀▀ ▀░▀▀ ▀▀▀ ▀░▀▀

// Test Triangle
/*-----------------------------------------------------------------------------------------------------------*/
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

	Texture TextureInstance("Test.png", Texture::RGBA);
	TextureInstance.BindTexture();

	VertexBufferArray VertexArrayBuffer;
	unsigned int VertexBufferObject = VertexArrayBuffer.VertexBuffer(VertexArrayBuffer.ARRAY_BUFFER, sizeof(vertices), &vertices, VertexArrayBuffer.STATIC_DRAW);
	unsigned int IndexBufferObject = VertexArrayBuffer.VertexBuffer(VertexArrayBuffer.ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, VertexArrayBuffer.STATIC_DRAW);
	VertexArrayBuffer.VertexArray(0, 3, 5 * sizeof(float), (void*)0);
	VertexArrayBuffer.VertexArray(1, 2, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	VertexArrayBuffer.BindVertexArray();
	VertexArrayBuffer.BindVertexBuffer(VertexArrayBuffer.ARRAY_BUFFER, &VertexBufferObject);
	VertexArrayBuffer.BindVertexBuffer(VertexArrayBuffer.ELEMENT_ARRAY_BUFFER, &IndexBufferObject);

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
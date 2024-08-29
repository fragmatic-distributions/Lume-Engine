#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>

#include "Renderer.hpp"
#include "Util.hpp"
#include "Shader.hpp"
#include "texture.hpp"

//▒█░░▒█ █▀▀ █▀▀█ ▀▀█▀▀ █▀▀ █░█ 　 ░█▀▀█ █▀▀█ █▀▀█ █▀▀█ █░░█ 　 ▒█▀▀█ █░░█ █▀▀ █▀▀ █▀▀ █▀▀█
//░▒█▒█░ █▀▀ █▄▄▀ ░░█░░ █▀▀ ▄▀▄ 　 ▒█▄▄█ █▄▄▀ █▄▄▀ █▄▄█ █▄▄█ 　 ▒█▀▀▄ █░░█ █▀▀ █▀▀ █▀▀ █▄▄▀
//░░▀▄▀░ ▀▀▀ ▀░▀▀ ░░▀░░ ▀▀▀ ▀░▀ 　 ▒█░▒█ ▀░▀▀ ▀░▀▀ ▀░░▀ ▄▄▄█ 　 ▒█▄▄█ ░▀▀▀ ▀░░ ▀░░ ▀▀▀ ▀░▀▀

// Creates a vertex Buffer Instance
/*-----------------------------------------------------------------------------------------------------------*/
void VertexBufferArray::VertexBuffer(const VertexBufferType VertexBuffer, const size_t VertexByteSize, const float Vertices[], const DrawMode BufferDrawType) {
	glGenBuffers(1, &(this->VertexBufferObject));
	glBindBuffer(VertexBuffer, this->VertexBufferObject);
	glBufferData(VertexBuffer, VertexByteSize, Vertices, BufferDrawType);
}

// Creates a vertex Array Object
/*-----------------------------------------------------------------------------------------------------------*/
void VertexBufferArray::VertexArray(const int Index, const int ArraySize, const int Stride, const void* Data) {
	glGenVertexArrays(1, &(this->VertexArrayObject));
	glBindVertexArray(this->VertexArrayObject);

	// We can add color to our strides
	// But i opted not to since most of our assets are gonna texture wise
	// This will just hog up uneeded memory, slowing us down in the long run
	glVertexAttribPointer(Index, ArraySize, GL_FLOAT, GL_FALSE, Stride, Data);

	glEnableVertexAttribArray(0);
}

// Binds the vertex array
/*-----------------------------------------------------------------------------------------------------------*/
void VertexBufferArray::BindVertexArray() {
	glBindVertexArray(this->VertexArrayObject);
}

// Destory a Instance
/*-----------------------------------------------------------------------------------------------------------*/
void VertexBufferArray::Destroy() {
	glDeleteBuffers(1, &(this->VertexBufferObject));
	glDeleteVertexArrays(1, &(this->VertexBufferObject));
}


//▒█▀▀█ █▀▀ █▀▀▄ █▀▀▄ █▀▀ █▀▀█ █▀▀ █▀▀█
//▒█▄▄▀ █▀▀ █░░█ █░░█ █▀▀ █▄▄▀ █▀▀ █▄▄▀
//▒█░▒█ ▀▀▀ ▀░░▀ ▀▀▀░ ▀▀▀ ▀░▀▀ ▀▀▀ ▀░▀▀

// Test Triangle
/*-----------------------------------------------------------------------------------------------------------*/
void RenderTriangle() {
	float vertices[] = {
		-0.5f, -0.5f, 0.0f, // left  
		 0.5f, -0.5f, 0.0f, // right 
		 0.0f,  0.5f, 0.0f  // top   
	};
	float texCoords[] = {
		0.0f, 0.0f,  // lower-left corner  
		1.0f, 0.0f,  // lower-right corner
		0.5f, 1.0f   // top-center corner
	};

	// Shader Crap
	Shader ShaderInstance("Default.vert", "Default.frag");
	Texture TextureInstance("Test.png", Texture::NEAREST_FILTERING);

	VertexBufferArray VertexArrayBuffer;
	VertexArrayBuffer.VertexBuffer(VertexArrayBuffer.ARRAY_BUFFER, sizeof(vertices), vertices, VertexArrayBuffer.STATIC_DRAW);
	VertexArrayBuffer.VertexArray(0, 3, 3 * sizeof(float), (void*)0);
	VertexArrayBuffer.BindVertexArray();

	ShaderInstance.UseShaderProgram();
	ShaderInstance.SetUniformFloat("color", 1.0);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	VertexArrayBuffer.Destroy();
	ShaderInstance.Destroy();
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
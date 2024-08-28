#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Renderer.hpp"
#include "Util.hpp"
#include "Shader.hpp"

void RenderTriangle() {
	float vertices[] = {
	-0.5f, -0.5f, 0.0f, // left  
	 0.5f, -0.5f, 0.0f, // right 
	 0.0f,  0.5f, 0.0f  // top   
	};

	// Shader Crap
	Shader ShaderInstance("Default.vert", "Default.frag");

	//std::string VertexShaderFile = OpenShaderFile("Default.vert");
 //   std::string FragmentShaderFile = OpenShaderFile("Default.frag");
 //   const char* VertexCode = VertexShaderFile.c_str();
 //   const char* FragmentCode = FragmentShaderFile.c_str();

	//unsigned int VertexShader;
	//VertexShader = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(VertexShader, 1, &VertexCode, NULL);
	//glCompileShader(VertexShader);

	//unsigned int FragmentShader;
	//FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(FragmentShader, 1, &FragmentCode, NULL);
	//glCompileShader(FragmentShader);

	//unsigned int ShaderProgram;
	//ShaderProgram = glCreateProgram();
	//glAttachShader(ShaderProgram, VertexShader);
	//glAttachShader(ShaderProgram, FragmentShader);

	//glLinkProgram(ShaderProgram);

	unsigned int VertexBufferObject;
	glGenBuffers(1, &VertexBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int VertexArrayObject;
	glGenVertexArrays(1, &VertexArrayObject);
	glBindVertexArray(VertexArrayObject);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	//glDeleteShader(FragmentShader);
	//glDeleteShader(VertexShader);

	//glUseProgram(ShaderProgram);

	ShaderInstance.UseShaderProgram();
	glBindVertexArray(VertexArrayObject);
	glDrawArrays(GL_TRIANGLES, 0, 3);

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
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>

class VertexBufferArray{
public:
	enum VertexBufferType : int {
		ARRAY_BUFFER = GL_ARRAY_BUFFER,
		ELEMENT_ARRAY_BUFFER = GL_ELEMENT_ARRAY_BUFFER,
	};

	enum DrawMode : int {
		STATIC_DRAW = GL_STATIC_DRAW,
		DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
		STREAM_DRAW = GL_STREAM_DRAW,
	};

	unsigned int VertexBuffer(const VertexBufferType VertexBuffer, const size_t VertexByteSize, const void* Vertices, const DrawMode BufferDrawType);
	unsigned int VertexArray(const int Index, const int ArraySize, const int Stride, const void* Data);

	void BindVertexBuffer(const VertexBufferType VertexBuffer, unsigned int* BufferInstance);
	void BindVertexArray();
	void Destroy();
private:
	std::vector<unsigned int> VertexBufferObjects;
	unsigned int VertexArrayObject;
};

void RenderFrame(GLFWwindow* WindowInstance);
void RenderTriangle();
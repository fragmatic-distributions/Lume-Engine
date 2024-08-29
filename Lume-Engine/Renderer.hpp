#include <glad/glad.h>
#include <GLFW/glfw3.h>


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

	void VertexBuffer(const VertexBufferType VertexBuffer, const size_t VertexByteSize, const float Vertices[], const DrawMode BufferDrawType);
	void VertexArray(const int Index, const int ArraySize, const int Stride, const void* Data);
	void BindVertexArray();
	void Destroy();
private:
	unsigned int VertexBufferObject;
	unsigned int VertexArrayObject;
};

void RenderFrame(GLFWwindow* WindowInstance);
void RenderTriangle();
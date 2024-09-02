#include <glad/glad.h>
#include <iostream>
#include <vector>

class VertexArray {
public:
	enum BufferType : int {
		ARRAY_BUFFER =							GL_ARRAY_BUFFER,
		ELEMENT_ARRAY_BUFFER =					GL_ELEMENT_ARRAY_BUFFER,
	};

	enum DrawMode : int {
		STATIC_DRAW =							GL_STATIC_DRAW,
		DYNAMIC_DRAW =							GL_DYNAMIC_DRAW,
		STREAM_DRAW =							GL_STREAM_DRAW,
	};

	void Buffer(const BufferType VertexBuffer, const size_t VertexByteSize, const void* Vertices, const DrawMode BufferDrawType);
	void Array(const int Index, const int DataSize, const int StrideSize, const int Data);

	void BindBuffer(const BufferType BufferType);
	void BindArray();
	void Destroy();
private:
	std::vector<unsigned int> IdfkWhythishastobehere; // if i delete this variable, shit just breaks... it has no use
	unsigned int VBO;
	unsigned int EBO;
	unsigned int VAO;
};
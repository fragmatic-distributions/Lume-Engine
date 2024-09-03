#include <iostream>

#include "VertexArray.hpp"

void VertexArray::Buffer(VertexArray::BufferType BufferType, const size_t VertexByteSize, const void* Vertices, const DrawMode BufferDrawType) {
	unsigned int Buffer;
	glGenBuffers(1, &Buffer);
	glBindBuffer(BufferType, Buffer);
	glBufferData(BufferType, VertexByteSize, Vertices, BufferDrawType);

	if (BufferType == VertexArray::ARRAY_BUFFER) {
		this->VBO = Buffer;
	}
	else if (BufferType == VertexArray::ELEMENT_ARRAY_BUFFER) {
		this->EBO = Buffer;
	}
}

void VertexArray::Array(const int Index, const int DataSize, const int StrideSize, const int Data) {
	if (!this->VAO) {
		unsigned int Array;
		glGenVertexArrays(1, &Array);
		glBindVertexArray(Array);
		this->VAO = Array;
	}

	// We can add color to our strides
	// But i opted not to since most of our assets are gonna texture wise
	// This will just hog up uneeded memory, slowing us down in the long run
	glVertexAttribPointer(Index, DataSize, GL_FLOAT, GL_FALSE, StrideSize * sizeof(float), (void*)(Data * sizeof(float)));
	glEnableVertexAttribArray(Index);
}

void VertexArray::BindBuffer(const BufferType BufferType) {
	if (BufferType == VertexArray::ARRAY_BUFFER) {
		glBindBuffer(BufferType, this->VBO);
	}
	else if (BufferType == VertexArray::ELEMENT_ARRAY_BUFFER) {
		glBindBuffer(BufferType, this->EBO);
	}
}

void VertexArray::BindArray() {
	glBindVertexArray(this->VBO);
}

void VertexArray::Destroy() {
	if (this->EBO) {
		glDeleteBuffers(1, &this->EBO);
	}
	glDeleteBuffers(1, &this->VBO);
	glDeleteVertexArrays(1, &this->VAO);
}
#include "GameObjects.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Quad::Quad() :
	ShaderInstance(LumeShader::VERTEX, LumeShader::FRAGMENT),
	TextureInstance(LumeTexture::RGBA)
{
	float vertices[] = {
		 0.5f,  0.5f, 0.0f,  1.0f, 1.0f,  // top right
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f,  0.0f, 1.0f   // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	this->ShaderInstance.CreateShader("Shaders/Default.vert", "Shaders/Default.frag");
	this->TextureInstance.LoadTexture("../Graphics/Tex/Test.png");

	this->VertexArrayInstance.Buffer(VertexArray::ARRAY_BUFFER, sizeof(vertices), &vertices, VertexArray::STATIC_DRAW);
	this->VertexArrayInstance.Buffer(VertexArray::ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, VertexArray::STATIC_DRAW);
	this->VertexArrayInstance.Array(0, 3, 5, 0);
	this->VertexArrayInstance.Array(1, 2, 5, 3);
}

void Quad::Destroy() {
	this->ShaderInstance.DestroyProgram();
	this->TextureInstance.Destroy();
	this->VertexArrayInstance.Destroy();
}

void Quad::Draw() {
	this->ShaderInstance.BindProgram();
	this->ShaderInstance.SetUniformInt("TextureInstance", 0);
	this->ShaderInstance.SetUniformMat4("Transform", &this->Transform);

	this->TextureInstance.BindTexture(0);

	this->VertexArrayInstance.BindArray();
	this->VertexArrayInstance.BindBuffer(VertexArray::ELEMENT_ARRAY_BUFFER);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

// Props

void Quad::SetTransform(glm::mat4 Transform) {
	this->Transform = Transform;
}

void Quad::SetTexture(const char* Texture) {
	this->TextureInstance.Destroy();

	LumeTexture TextureInstance(LumeTexture::RGBA);
	TextureInstance.LoadTexture(Texture);
	this->TextureInstance = TextureInstance;
}
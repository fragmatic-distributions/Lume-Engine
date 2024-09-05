#include "GameObjects.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Core/Renderer.hpp"
#include "Camera.hpp"

// Quad Instacne

Quad::Quad() :
	ShaderInstance(LumeShader::VERTEX, LumeShader::FRAGMENT),
	TextureInstance(LumeTexture::RGB)
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
	this->TextureInstance.LoadTexture("../Graphics/Tex/Missing_Texture.png");

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
	this->ShaderInstance.SetUniformMat4("Projection", Camera::GetPrespectiveMatrix());
	this->ShaderInstance.SetUniformMat4("View", Camera::GetViewMatrix());

	this->TextureInstance.BindTexture(0);

	this->VertexArrayInstance.BindArray();
	this->VertexArrayInstance.BindBuffer(VertexArray::ARRAY_BUFFER);
	this->VertexArrayInstance.BindBuffer(VertexArray::ELEMENT_ARRAY_BUFFER);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

// Props

void Quad::SetTransform(glm::mat4 Transform) {
	this->Transform = Transform;
}

void Quad::SetTexture(const char* Texture, LumeTexture::ColorChannels ColorChannels) {
	this->TextureInstance.Destroy();

	LumeTexture TextureInstance(ColorChannels);
	TextureInstance.LoadTexture(Texture);
	this->TextureInstance = TextureInstance;
}


// Cube Instacnem


Cube::Cube() :
	ShaderInstance(LumeShader::VERTEX, LumeShader::FRAGMENT),
	TextureInstance(LumeTexture::RGB)
{

	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // A 0
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  // B 1
		0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  // C 2
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,  // D 3
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  // E 4
		0.5f, -0.5f,  0.5f,  1.0f, 0.0f,   // F 5
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,   // G 6
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,   // H 7

		-0.5f,  0.5f, -0.5f,  0.0f, 0.0f,  // D 8
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  // A 9
		-0.5f, -0.5f,  0.5f,  1.0f, 1.0f,  // E 10
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,  // H 11
		0.5f, -0.5f, -0.5f,  0.0f, 0.0f,   // B 12
		0.5f,  0.5f, -0.5f,  1.0f, 0.0f,   // C 13
		0.5f,  0.5f,  0.5f,  1.0f, 1.0f,   // G 14
		0.5f, -0.5f,  0.5f,  0.0f, 1.0f,   // F 15

		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  // A 16
		0.5f, -0.5f, -0.5f,  1.0f, 0.0f,   // B 17
		0.5f, -0.5f,  0.5f,  1.0f, 1.0f,   // F 18
		-0.5f, -0.5f,  0.5f,  0.0f, 1.0f,  // E 19
		0.5f,  0.5f, -0.5f,   0.0f, 0.0f,  // C 20
		-0.5f,  0.5f, -0.5f,  1.0f, 0.0f,  // D 21
		-0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  // H 22
		0.5f,  0.5f,  0.5f,   0.0f, 1.0f,  // G 23
	};
	unsigned int indices[] = {  // note that we start from 0!
		// front and back
		0, 3, 2,
		2, 1, 0,
		4, 5, 6,
		6, 7 ,4,
		// left and right
		11, 8, 9,
		9, 10, 11,
		12, 13, 14,
		14, 15, 12,
		// bottom and top
		16, 17, 18,
		18, 19, 16,
		20, 21, 22,
		22, 23, 20
	};

	this->ShaderInstance.CreateShader("Shaders/Default.vert", "Shaders/Default.frag");
	this->TextureInstance.LoadTexture("../Graphics/Tex/Missing_Texture.png");

	this->VertexArrayInstance.Buffer(VertexArray::ARRAY_BUFFER, sizeof(vertices), &vertices, VertexArray::STATIC_DRAW);
	this->VertexArrayInstance.Buffer(VertexArray::ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, VertexArray::STATIC_DRAW);
	this->VertexArrayInstance.Array(0, 3, 5, 0);
	this->VertexArrayInstance.Array(1, 2, 5, 3);
}


void Cube::Destroy() {
	this->ShaderInstance.DestroyProgram();
	this->TextureInstance.Destroy();
	this->VertexArrayInstance.Destroy();
}

void Cube::Draw() {
	this->ShaderInstance.BindProgram();
	this->ShaderInstance.SetUniformInt("TextureInstance", 0);

	this->ShaderInstance.SetUniformMat4("Transform", &this->Transform);
	this->ShaderInstance.SetUniformMat4("Projection", Camera::GetPrespectiveMatrix());
	this->ShaderInstance.SetUniformMat4("View", Camera::GetViewMatrix());

	this->TextureInstance.BindTexture(0);
	this->VertexArrayInstance.BindArray();
	this->VertexArrayInstance.BindBuffer(VertexArray::ELEMENT_ARRAY_BUFFER);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

// Props

void Cube::SetTransform(glm::mat4 Transform) {
	this->Transform = Transform;
}

void Cube::SetTexture(const char* Texture, LumeTexture::ColorChannels ColorChannels) {
	this->TextureInstance.Destroy();

	LumeTexture TextureInstance(ColorChannels);
	TextureInstance.LoadTexture(Texture);
	this->TextureInstance = TextureInstance;
}
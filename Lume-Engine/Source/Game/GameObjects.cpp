#include "GameObjects.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <filesystem>
#include "../Graphics/Shader.hpp"
#include "../Graphics/Texture.hpp"
#include "../Graphics/VertexArray.hpp"
#include "../Core/Renderer.hpp"
#include "../Graphics/Model.hpp"
#include "Camera.hpp"

//-------------------------------------------------//
// Quad	
//-------------------------------------------------//

Quad::Quad() :
	ShaderInstance(LumeShader::VERTEX, LumeShader::FRAGMENT),
	TextureInstance(LumeTexture::RGB)
{
	float vertices[] = {
		 0.5f,  0.5f, 0.0f,  1.0f, 1.0f, 
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 
		-0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 
		-0.5f,  0.5f, 0.0f,  0.0f, 1.0f  
	};
	unsigned int indices[] = {  
		0, 1, 3, 
		1, 2, 3  
	};

	this->ShaderInstance.CreateShader("Source/Shaders/Default.vert", "Source/Shaders/Default.frag");
	this->TextureInstance.LoadTexture("Graphics/Tex/Missing_Texture.png");

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

void Quad::SetTransform(glm::mat4 Transform) {
	this->Transform = Transform;
}

void Quad::SetTexture(const char* Texture, LumeTexture::ColorChannels ColorChannels) {
	this->TextureInstance.Destroy();

	LumeTexture TextureInstance(ColorChannels);
	TextureInstance.LoadTexture(Texture);
	this->TextureInstance = TextureInstance;
}


//-------------------------------------------------//
// Cube	
//-------------------------------------------------//

Cube::Cube() :
	ShaderInstance(LumeShader::VERTEX, LumeShader::FRAGMENT),
	TextureInstance(LumeTexture::RGB)
{

	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,  
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 
		-0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 
		-0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 
		-0.5f, -0.5f,  0.5f,  1.0f, 1.0f, 
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 
		 0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  
		 0.5f,  0.5f, -0.5f,  1.0f, 0.0f,  
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,  
		 0.5f, -0.5f,  0.5f,  0.0f, 1.0f,  
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,  
		 0.5f, -0.5f,  0.5f,  1.0f, 1.0f,  
		-0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 
		 0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 
		-0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 
		-0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 
		 0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 
	};
	unsigned int indices[] = {
		0, 3, 2,
		2, 1, 0,
		4, 5, 6,
		6, 7 ,4,
		11, 8, 9,
		9, 10, 11,
		12, 13, 14,
		14, 15, 12,
		16, 17, 18,
		18, 19, 16,
		20, 21, 22,
		22, 23, 20
	};

	this->ShaderInstance.CreateShader("Source/Shaders/Default.vert", "Source/Shaders/Default.frag");
	this->TextureInstance.LoadTexture("Graphics/Tex/Missing_Texture.png");

	this->VertexArrayInstance.Buffer(VertexArray::ARRAY_BUFFER, sizeof(vertices), &vertices, VertexArray::STATIC_DRAW);
	this->VertexArrayInstance.Buffer(VertexArray::ELEMENT_ARRAY_BUFFER, sizeof(indices), &indices, VertexArray::STATIC_DRAW);
	this->VertexArrayInstance.Array(0, 3, 5, 0);
	this->VertexArrayInstance.Array(1, 2, 5, 3);
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

void Cube::SetTransform(glm::mat4 Transform) {
	this->Transform = Transform;
}

void Cube::SetTexture(const char* Texture, LumeTexture::ColorChannels ColorChannels) {
	this->TextureInstance.Destroy();

	LumeTexture TextureInstance(ColorChannels);
	TextureInstance.LoadTexture(Texture);
	this->TextureInstance = TextureInstance;
}

void Cube::Destroy() {
	this->ShaderInstance.DestroyProgram();
	this->TextureInstance.Destroy();
	this->VertexArrayInstance.Destroy();
}

//-------------------------------------------------//
// Mesh	
//-------------------------------------------------//

// Has no use but to be used so that i can run it on heap instead of stack
Mesh::Mesh() {
	return;
}

void Mesh::SetShader(const char* VertexShader, const char* FragmentShader) {
	this->ShaderInstance = new LumeShader(LumeShader::VERTEX, LumeShader::FRAGMENT);
	this->ShaderInstance->CreateShader(VertexShader, FragmentShader);
	this->ShaderDefined = true;
}

void Mesh::BufferMesh(const char* MeshFile) {
	if (!this->ShaderDefined) {
		std::cout << "Mesh init failed, missing shaders, " << MeshFile << std::endl;
		return;
	}

	Model ModelInstance(MeshFile);
	std::vector<BufferInfo> BufferInformation = ModelInstance.GetBuffers();

	for (uint8_t i = 0; i < BufferInformation.size(); i++) {
		BufferInfo Buffer = BufferInformation[i];

		struct MeshInstance MeshData;
		MeshData.TextureInstance = new LumeTexture(LumeTexture::RGB);
		MeshData.TextureInstance->LoadTexture(Buffer.AlbedoTexture.c_str());
		MeshData.Buffer = Buffer;

		float* Vertexdata = new float[Buffer.Vertices.size()];
		std::copy(Buffer.Vertices.begin(), Buffer.Vertices.end(), Vertexdata);

		int* IndexData = new int[Buffer.Indices.size()];
		std::copy(Buffer.Indices.begin(), Buffer.Indices.end(), IndexData);

		MeshData.VertexArrayInstance = new VertexArray();
		MeshData.VertexArrayInstance->Buffer(VertexArray::ARRAY_BUFFER
			, Buffer.VertexBufferSize
			, Vertexdata
			, VertexArray::STATIC_DRAW);

		MeshData.VertexArrayInstance->Buffer(VertexArray::ELEMENT_ARRAY_BUFFER
			, Buffer.IndexBufferSize
			, IndexData
			, VertexArray::STATIC_DRAW);

		MeshData.VertexArrayInstance->Array(0, 3, 8, 0);
		MeshData.VertexArrayInstance->Array(1, 2, 8, 3);
		MeshData.VertexArrayInstance->Array(2, 3, 8, 5);

		delete[] Vertexdata;
		delete[] IndexData;

		this->Buffers.push_back(MeshData);
	}
}

void Mesh::SetTransform(glm::mat4 Transform) {
	this->Transform = Transform;
}

void Mesh::MeshInstance::SetTexture(const char* TexturePath, LumeTexture::ColorChannels ColorChannels) {
	this->TextureInstance->Destroy();
	delete this->TextureInstance;

	this->TextureInstance = new LumeTexture(ColorChannels);
	this->TextureInstance->LoadTexture(TexturePath);
}

void Mesh::Draw() {
	this->ShaderInstance->BindProgram();
	this->ShaderInstance->SetUniformInt("TextureInstance", 0);

	this->ShaderInstance->SetUniformMat4("Transform", &this->Transform);
	this->ShaderInstance->SetUniformMat4("Projection", Camera::GetPrespectiveMatrix());
	this->ShaderInstance->SetUniformMat4("View", Camera::GetViewMatrix());

	for (uint8_t i = 0; i < this->Buffers.size(); i++) {
		MeshInstance MeshInstance = this->Buffers[i];
		MeshInstance.TextureInstance->BindTexture(0);
		MeshInstance.VertexArrayInstance->BindArray();
		MeshInstance.VertexArrayInstance->BindBuffer(VertexArray::ELEMENT_ARRAY_BUFFER);

		glDrawElements(GL_TRIANGLES, MeshInstance.Buffer.Vertices.size() + MeshInstance.Buffer.Indices.size(), GL_UNSIGNED_INT, 0);
	}
}

void Mesh::Destroy() {
	this->ShaderInstance->DestroyProgram();
	delete this->ShaderInstance;

	for (uint8_t i = 0; i < this->Buffers.size(); i++) {
		this->Buffers[i].TextureInstance->Destroy();
		this->Buffers[i].VertexArrayInstance->Destroy();

		delete this->Buffers[i].VertexArrayInstance;
		delete this->Buffers[i].TextureInstance;
	}
}
//Mesh::Mesh(const char* GltfPath) :
//	ShaderInstance(LumeShader::VERTEX, LumeShader::FRAGMENT),
//	TextureInstance(LumeTexture::RGB),
//	Model(GltfPath)
//{
//
//	this->ShaderInstance.CreateShader("Source/Shaders/Default.vert", "Source/Shaders/Default.frag");
//	this->TextureInstance.LoadTexture("Graphics/Tex/Missing_Texture.png");
//
//	float* Vertexdata = new float[this->Model.Buffer.Vertices.size()];
//	std::copy(this->Model.Buffer.Vertices.begin(), this->Model.Buffer.Vertices.end(), Vertexdata);
//
//	int* IndexData = new int[this->Model.Buffer.Indices.size()];
//	std::copy(this->Model.Buffer.Indices.begin(), this->Model.Buffer.Indices.end(), IndexData);
//
//	this->VertexArrayInstance.Buffer(VertexArray::ARRAY_BUFFER
//		, sizeof(float) * this->Model.Buffer.Vertices.size()
//		, Vertexdata
//		, VertexArray::STATIC_DRAW);
//
//	this->VertexArrayInstance.Buffer(VertexArray::ELEMENT_ARRAY_BUFFER
//		, sizeof(int) * this->Model.Buffer.Indices.size()
//		, IndexData
//		, VertexArray::STATIC_DRAW);
//
//	this->VertexArrayInstance.Array(0, 3, 8, 0);
//	this->VertexArrayInstance.Array(1, 2, 8, 3);
//	this->VertexArrayInstance.Array(2, 3, 8, 5);
//
//	delete[] Vertexdata;
//	delete[] IndexData;
//}
//
//void Mesh::Draw() {
//	this->ShaderInstance.BindProgram();
//	this->ShaderInstance.SetUniformInt("TextureInstance", 0);
//
//	this->ShaderInstance.SetUniformMat4("Transform", &this->Transform);
//	this->ShaderInstance.SetUniformMat4("Projection", Camera::GetPrespectiveMatrix());
//	this->ShaderInstance.SetUniformMat4("View", Camera::GetViewMatrix());
//
//	this->TextureInstance.BindTexture(0);
//	this->VertexArrayInstance.BindArray();
//	this->VertexArrayInstance.BindBuffer(VertexArray::ELEMENT_ARRAY_BUFFER);
//
//	glDrawElements(GL_TRIANGLES, this->Model.Buffer.Vertices.size() + this->Model.Buffer.Indices.size(), GL_UNSIGNED_INT, 0);
//}
//
//void Mesh::SetTransform(glm::mat4 Transform) {
//	this->Transform = Transform;
//}
//
//void Mesh::Destroy() {
//
//}

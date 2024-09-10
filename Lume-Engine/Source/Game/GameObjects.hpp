#ifndef GAME_OBJECTS_H
#define GAME_OBJECTS_H
#include <glm/glm.hpp>
#include "../Graphics/Model.hpp"
#include "../Graphics/Shader.hpp"
#include "../Graphics/Texture.hpp"
#include "../Graphics/VertexArray.hpp"

class Quad {
public:
	Quad();

	void SetTransform(glm::mat4 Transform);
	void SetTexture(const char* Texture, LumeTexture::ColorChannels ColorChannels);

	void Destroy();

	void Draw();
private:
	glm::mat4 Transform;

	LumeShader ShaderInstance;
	LumeTexture TextureInstance;
	VertexArray VertexArrayInstance;
};

class Cube {
public:
	Cube();

	void SetTransform(glm::mat4 Transform);
	void SetTexture(const char* Texture, LumeTexture::ColorChannels ColorChannels);

	void Destroy();

	void Draw();
private:
	glm::mat4 Transform;

	LumeShader ShaderInstance;
	LumeTexture TextureInstance;
	VertexArray VertexArrayInstance;
};

//-------------------------------------------------//
// Mesh	
//-------------------------------------------------//

class Mesh {
public:
	struct MeshInstance {
		LumeTexture* TextureInstance;
		VertexArray* VertexArrayInstance;
		BufferInfo Buffer;

		void SetTexture(const char* TexturePath, LumeTexture::ColorChannels ColorChannels);
	};

	void SetShader(const char* VertexShader, const char* FragmentShader);
	void SetTransform(glm::mat4 Transform);
	void BufferMesh(const char* MeshFile);
	Mesh();

	void Draw();
	void Destroy();
	std::vector<MeshInstance> Buffers;
private:

	bool ShaderDefined = false;
	glm::mat4 Transform;

	LumeShader* ShaderInstance;
};

#endif 
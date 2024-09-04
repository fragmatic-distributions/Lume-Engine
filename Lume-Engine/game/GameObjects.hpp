#include<glm/glm.hpp>

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
	glm::mat4 Projection;
	glm::mat4 View;

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
	glm::mat4 Projection;
	glm::mat4 View;

	LumeShader ShaderInstance;
	LumeTexture TextureInstance;
	VertexArray VertexArrayInstance;
};
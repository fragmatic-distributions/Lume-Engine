#include<glm/glm.hpp>

#include "../Graphics/Shader.hpp"
#include "../Graphics/Texture.hpp"
#include "../Graphics/VertexArray.hpp"

class Quad {
public:
	Quad();

	void SetTransform(glm::mat4 Transform);
	void SetTexture(const char* Texture);

	void Destroy();

	void Draw();
private:
	glm::mat4 Transform;

	LumeShader ShaderInstance;
	LumeTexture TextureInstance;
	VertexArray VertexArrayInstance;
};
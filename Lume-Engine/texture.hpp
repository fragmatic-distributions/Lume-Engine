#include <glad/glad.h>

class Texture {
public:
	enum TextureFiltering : int {
		LINEAR_FILTERING = GL_LINEAR,
		NEAREST_FILTERING = GL_NEAREST,
	};

	Texture(const char* TextureLocation, TextureFiltering TextureFilterMethod);

	void BindTexture();
	void Destroy();
private:
	struct Image {
		int ImageWidth;
		int ImageHeight;
		int ChannelNumbers;
		unsigned char* ImageData;
	};

	unsigned int TextureInstance;
};
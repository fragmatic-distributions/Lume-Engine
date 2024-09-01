#include <glad/glad.h>

class Texture {
public:
	enum TextureColorChannel : int {
		RGB = GL_RGB, 
		RGBA = GL_RGBA,
	};

	Texture(const char* TextureLocation, TextureColorChannel ColorChannels);
	~Texture();

	unsigned int TextureInstance;

	void BindTexture();
	void Destroy();
private:
	struct Image {
		int ImageWidth;
		int ImageHeight;
		int ChannelNumbers;
		unsigned char* ImageData;
	};

	//std::string FetchImageFile(const char* FolderFileNamePath);
};
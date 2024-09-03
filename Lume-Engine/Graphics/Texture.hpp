#include <glad/glad.h>

class LumeTexture {
public:
	static enum ColorChannels : int {
		R =					GL_R,
		RG =				GL_RG,
		RGB =				GL_RGB,
		RGBA =				GL_RGBA,
	};

	LumeTexture(LumeTexture::ColorChannels ColorChannels);
	//~LumeTexture();

	void LoadTexture(const char* TexturePath);
	void BindTexture(unsigned int TextureSlot);
	void Destroy();

	unsigned int Texture;
private:
	ColorChannels ColorFormat;

	struct ImageStruct {
		int ImageWidth;
		int ImageHeight;
		int ChannelNumbers;
		unsigned char* ImageData;
	};

	bool ValidateTexture(const char* TexturePath);
};
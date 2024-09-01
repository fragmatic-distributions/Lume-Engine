#define STB_IMAGE_IMPLEMENTATION
#include <STBI/stbi.h>
#include <filesystem>
#include <iostream>

#include "texture.hpp"

// Creates a new texture instance
/*-----------------------------------------------------------------------------------------------------------*/
Texture::Texture(const char* TextureLocation, TextureColorChannel ColorChannels) {
	const char* TexFolderPath = "../Graphics/Tex/";

	std::string TextureFolderPath = TexFolderPath;
	std::string TextureLocationString = TextureLocation;
	std::string ConcatenatedString = TexFolderPath + TextureLocationString;

	glGenTextures(1, &(this->TextureInstance));
	glBindTexture(GL_TEXTURE_2D, this->TextureInstance);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int TextureParameterIv;
	glTexParameterIiv(this->TextureInstance, GL_LINK_STATUS, &TextureParameterIv);
	if (TextureParameterIv == -1) {
		std::cout << "TEXTURE.CPP::TEXTURE_DEFINING::ERROR" << std::endl;
		this->Destroy();
		return;
	}

	const char* ConcatenatedPath = ConcatenatedString.c_str();
	if (!std::filesystem::exists(TexFolderPath)) {
		std::cout << "TEXTURE.CPP::TEXTURE_FOLDER_PATH_INVALID::ERROR, GOT : " << TexFolderPath << std::endl;
		this->Destroy();
		return;
	}

	struct Texture::Image TextureStruct;
	stbi_set_flip_vertically_on_load(true);
	TextureStruct.ImageData = stbi_load(ConcatenatedPath, &TextureStruct.ImageWidth, &TextureStruct.ImageHeight, &TextureStruct.ChannelNumbers, 0);

	if (TextureStruct.ImageData) {
		glTexImage2D(GL_TEXTURE_2D, 0, ColorChannels, TextureStruct.ImageWidth, TextureStruct.ImageHeight, 0, ColorChannels, GL_UNSIGNED_BYTE, TextureStruct.ImageData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "TEXTURE.CPP::TEXTURE_LOADING_INVALID::ERROR, GOT : " << TextureLocation << std::endl;
		this->Destroy();
		return;
	}

	stbi_image_free(TextureStruct.ImageData);
}

Texture::~Texture() {
	glDeleteTextures(1, &(this->TextureInstance));
}

void Texture::BindTexture() {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, this->TextureInstance);
};

void Texture::Destroy() {
	glDeleteTextures(1, &(this->TextureInstance));
};
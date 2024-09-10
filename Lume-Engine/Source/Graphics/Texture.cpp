#define STB_IMAGE_IMPLEMENTATION
#include <filesystem>
#include <iostream>
#include <STBI/stbi.h>
#include <glad/glad.h>
#include "Texture.hpp"
#include "../Util.hpp"

// Checks if path exists
bool LumeTexture::ValidateTexture(const char* TexturePath) {
	if (!std::filesystem::exists(TexturePath)) {
		std::cout << "texture path invalid : " << TexturePath << std::endl;
		return false;
	}
	
	return true;
}

// Constructa and Deconstructa

LumeTexture::LumeTexture(LumeTexture::ColorChannels ColorChannels) {
	this->ColorFormat = ColorChannels;
	 glGenTextures(1, &this->Texture);
}

//LumeTexture::~LumeTexture() {
//	glDeleteTextures(1, &this->Texture);
//}

// Useable crap

void LumeTexture::Destroy() {
	if (this->Texture) {
		glDeleteTextures(1, &this->Texture);
	}
}

void LumeTexture::BindTexture(unsigned int TextureSlot) {
	glActiveTexture(GL_TEXTURE0 + TextureSlot); // Grabs the enum number and adds the amount of texture slots giving a new enum
	glBindTexture(GL_TEXTURE_2D, this->Texture);
}

void LumeTexture::LoadTexture(const char* TexturePath) {
	if (!this->ValidateTexture(TexturePath)) {
		return;
	}

	glBindTexture(GL_TEXTURE_2D, this->Texture);

	// might want to tweak this later
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	struct LumeTexture::ImageStruct TextureStruct;
	stbi_set_flip_vertically_on_load(true);
	TextureStruct.ImageData = stbi_load(TexturePath, &TextureStruct.ImageWidth, &TextureStruct.ImageHeight, &TextureStruct.ChannelNumbers, 0);

	if (TextureStruct.ImageData) {
		glTexImage2D(GL_TEXTURE_2D, 0, this->ColorFormat, TextureStruct.ImageWidth, TextureStruct.ImageHeight, 0, this->ColorFormat, GL_UNSIGNED_BYTE, TextureStruct.ImageData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Texture init failed : " << TexturePath << std::endl;
		this->Destroy();
	}
	stbi_image_free(TextureStruct.ImageData);
	return;
}
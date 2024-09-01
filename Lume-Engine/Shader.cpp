#include <glad/glad.h>
#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <filesystem>

#include "Shader.hpp"
#include "Util.hpp"

//█░█ █▀▀ █░░ █▀█ █▀▀ █▀█
//█▀█ ██▄ █▄▄ █▀▀ ██▄ █▀▄

// Checks if Shits setup right
int ShaderHelper::ValidateCompiler(unsigned int* CompilerID, ShaderHelper::CompilerType CompilerType) {
	if (CompilerType == ShaderHelper::SHADER) {
		int CompilerState;
		glGetShaderiv(*CompilerID, GL_COMPILE_STATUS, &CompilerState);

		if (!CompilerState) {
			char InfoLog[512];
			glGetShaderInfoLog(*CompilerID, 512, NULL, InfoLog);

			std::cout << "SHADER_COMPILATION_ERROR | " << InfoLog << std::endl;
			return -1;
		}
	}
	else if (CompilerType == ShaderHelper::PROGRAM) {
		int CompilerState;
		glGetProgramiv(*CompilerID, GL_LINK_STATUS, &CompilerState);

		if (!CompilerState) {
			char InfoLog[512];
			glGetProgramInfoLog(*CompilerID, 512, NULL, InfoLog);

			std::cout << "PROGRAM_COMPILATION_ERROR | " << InfoLog << std::endl;
			return -1;
		}
	}

	return 1;
}

//void ShaderHelper::DebugFileContents(std::map<LumeShader::LumeShaderConfig, std::string> FileContents) {
//	std::map<LumeShader::LumeShaderConfig, std::string>::iterator it;
//
//	for (it = FileContents.begin(); it != FileContents.end(); it++) {
//		std::cout << "DEBUG | ShaderFile Contents -> " << it->second << std::endl;
//	}
//}

// Opens the shaders files and reads the crap
std::map<LumeShader::LumeShaderConfig, std::string> ShaderHelper::FetchShaderFileContent(std::map<int, LumeShader::LumeShaderConfig>* ShaderTypeBindings,
																					     std::map<LumeShader::LumeShaderConfig, const char*> ShaderFiles) {
	std::map<int, LumeShader::LumeShaderConfig>::iterator it;
	std::map<LumeShader::LumeShaderConfig, std::string> ShaderFileContents;

	for (it = (*ShaderTypeBindings).begin(); it != (*ShaderTypeBindings).end(); it++) {
		const LumeShader::LumeShaderConfig LumeShaderType = it->second;
		const char* ShaderDirectory = ShaderFiles[LumeShaderType];


		std::string FileContents;
		std::ifstream ShaderFileInstance;

		if (!std::filesystem::exists(ShaderDirectory)) {
			std::cout << "Shader File Does not Exist | " << ShaderDirectory << std::endl;
			
			ShaderFileContents[LumeShaderType] = "";
			continue;
		}

		ShaderFileInstance.open(ShaderDirectory);
		// Check if there are any failed or bad bites to prevent GL from fucking up the compiler and breaking shit
		if (ShaderFileInstance.fail()) {
			std::cout << "Shader File Reading failed, got failbit | " << ShaderDirectory << std::endl;
			
			ShaderFileContents[LumeShaderType] = "";
			continue;
		}
		else if (ShaderFileInstance.bad()) {
			std::cout << "Shader File Reading failed, got Badbit" << ShaderDirectory << std::endl;
			
			ShaderFileContents[LumeShaderType] = "";
			continue;
		}

		std::stringstream ShaderContentInstance;
		ShaderContentInstance << ShaderFileInstance.rdbuf();

		ShaderFileInstance.close();
		FileContents = ShaderContentInstance.str();
		
		ShaderFileContents[LumeShaderType] = FileContents;
	}

	return ShaderFileContents;
}

// constructor shit and what not
// Shader Creation And Declaration

LumeShader::LumeShader(LumeShaderConfig ShaderType01) {
	this->ShaderTypeBindings[0] = ShaderType01;

	this->ShaderProgram = glCreateProgram();
}

LumeShader::LumeShader(LumeShaderConfig ShaderType01, LumeShaderConfig ShaderType02) {
	this->ShaderTypeBindings[0] = ShaderType01;
	this->ShaderTypeBindings[1] = ShaderType02;

	this->ShaderProgram = glCreateProgram();
}

LumeShader::LumeShader(LumeShaderConfig ShaderType01, LumeShaderConfig ShaderType02, LumeShaderConfig ShaderType03) {
	this->ShaderTypeBindings[0] = ShaderType01;
	this->ShaderTypeBindings[1] = ShaderType02;
	this->ShaderTypeBindings[2] = ShaderType03;

	this->ShaderProgram = glCreateProgram();
}

LumeShader::~LumeShader() {
	if (this->ShaderProgram) {
		glDeleteProgram(this->ShaderProgram);
	}
}

// creation Function Overloaders

void LumeShader::CreateShader(const char* ShaderFile01) {
	std::map<LumeShader::LumeShaderConfig, const char*> FileBindings;
	FileBindings[this->ShaderTypeBindings[0]] = ShaderFile01;

	std::map<LumeShader::LumeShaderConfig, std::string> ShaderFileContents = ShaderHelper::FetchShaderFileContent(&(this->ShaderTypeBindings), FileBindings);

	const LumeShader::LumeShaderConfig ShaderType01 = this->ShaderTypeBindings[0];

	const char* ShaderSourceFile01 = ShaderFileContents[ShaderType01].c_str();

	unsigned int ShaderID01;
	ShaderID01 = glCreateShader(ShaderType01);
	glShaderSource(ShaderID01, 1, &ShaderSourceFile01, NULL);
	glCompileShader(ShaderID01);
	ShaderHelper::ValidateCompiler(&ShaderID01, ShaderHelper::SHADER);

	glAttachShader(this->ShaderProgram, ShaderID01);

	glCompileShader(this->ShaderProgram);
	glLinkProgram(this->ShaderProgram);

	int ShaderStatus = ShaderHelper::ValidateCompiler(&this->ShaderProgram, ShaderHelper::CompilerType::PROGRAM);
	if (ShaderStatus == -1) {
		this->DestroyProgram();
		return;
	}
}

void LumeShader::CreateShader(const char* ShaderFile01, const char* ShaderFile02) {
	std::map<LumeShader::LumeShaderConfig, const char*> FileBindings;
	FileBindings[this->ShaderTypeBindings[0]] = ShaderFile01;
	FileBindings[this->ShaderTypeBindings[1]] = ShaderFile02;

	std::map<LumeShader::LumeShaderConfig, std::string> ShaderFileContents = ShaderHelper::FetchShaderFileContent(&(this->ShaderTypeBindings), FileBindings);

	const LumeShader::LumeShaderConfig ShaderType01 = this->ShaderTypeBindings[0];
	const LumeShader::LumeShaderConfig ShaderType02 = this->ShaderTypeBindings[1];

	const char* ShaderSourceFile01 = ShaderFileContents[ShaderType01].c_str();
	const char* ShaderSourceFile02 = ShaderFileContents[ShaderType02].c_str();

	unsigned int ShaderID01;
	ShaderID01 = glCreateShader(ShaderType01);
	glShaderSource(ShaderID01, 1, &ShaderSourceFile01, NULL);
	glCompileShader(ShaderID01);
	ShaderHelper::ValidateCompiler(&ShaderID01, ShaderHelper::SHADER);

	unsigned int ShaderID02;
	ShaderID02 = glCreateShader(ShaderType02);
	glShaderSource(ShaderID02, 1, &ShaderSourceFile02, NULL);
	glCompileShader(ShaderID02);
	ShaderHelper::ValidateCompiler(&ShaderID02, ShaderHelper::SHADER);

	glAttachShader(this->ShaderProgram, ShaderID01);
	glAttachShader(this->ShaderProgram, ShaderID02);

	glCompileShader(this->ShaderProgram);
	glLinkProgram(this->ShaderProgram);

	int ShaderStatus = ShaderHelper::ValidateCompiler(&this->ShaderProgram, ShaderHelper::CompilerType::PROGRAM);
	if (ShaderStatus == -1) {
		this->DestroyProgram();
		return;
	}
}


void LumeShader::CreateShader(const char* ShaderFile01, const char* ShaderFile02, const char* ShaderFile03) {
	std::map<LumeShader::LumeShaderConfig, const char*> FileBindings;
	FileBindings[this->ShaderTypeBindings[0]] = ShaderFile01;
	FileBindings[this->ShaderTypeBindings[1]] = ShaderFile02;
	FileBindings[this->ShaderTypeBindings[2]] = ShaderFile03;

	std::map<LumeShader::LumeShaderConfig, std::string> ShaderFileContents = ShaderHelper::FetchShaderFileContent(&(this->ShaderTypeBindings), FileBindings);

	const LumeShader::LumeShaderConfig ShaderType01 = this->ShaderTypeBindings[0];
	const LumeShader::LumeShaderConfig ShaderType02 = this->ShaderTypeBindings[1];
	const LumeShader::LumeShaderConfig ShaderType03 = this->ShaderTypeBindings[2];

	const char* ShaderSourceFile01 = ShaderFileContents[ShaderType01].c_str();
	const char* ShaderSourceFile02 = ShaderFileContents[ShaderType02].c_str();
	const char* ShaderSourceFile03 = ShaderFileContents[ShaderType03].c_str();

	unsigned int ShaderID01;
	ShaderID01 = glCreateShader(ShaderType01);
	glShaderSource(ShaderID01, 1, &ShaderSourceFile01, NULL);
	glCompileShader(ShaderID01);
	ShaderHelper::ValidateCompiler(&ShaderID01, ShaderHelper::SHADER);

	unsigned int ShaderID02;
	ShaderID02 = glCreateShader(ShaderType02);
	glShaderSource(ShaderID02, 1, &ShaderSourceFile02, NULL);
	glCompileShader(ShaderID02);
	ShaderHelper::ValidateCompiler(&ShaderID02, ShaderHelper::SHADER);

	unsigned int ShaderID03;
	ShaderID03 = glCreateShader(ShaderType03);
	glShaderSource(ShaderID03, 1, &ShaderSourceFile03, NULL);
	glCompileShader(ShaderID03);
	ShaderHelper::ValidateCompiler(&ShaderID03, ShaderHelper::SHADER);

	glAttachShader(this->ShaderProgram, ShaderID01);
	glAttachShader(this->ShaderProgram, ShaderID02);
	glAttachShader(this->ShaderProgram, ShaderID03);

	glCompileShader(this->ShaderProgram);
	glLinkProgram(this->ShaderProgram);

	int ShaderStatus = ShaderHelper::ValidateCompiler(&this->ShaderProgram, ShaderHelper::CompilerType::PROGRAM);
	if (ShaderStatus == -1) {
		this->DestroyProgram();
		return;
	}
}

void LumeShader::BindProgram() {
	if (!this->ShaderProgram) {
		std::cout << "Shader Program is not defined or invalid" << std::endl;
	}
	glUseProgram(this->ShaderProgram);
}

void LumeShader::UnbindProgram() {
	glUseProgram(0);
}

void LumeShader::DestroyProgram() {
	glDeleteProgram(this->ShaderProgram);
}

// GlUniform Settings

// Checks if uniform exists
void ShaderHelper::UniformValidation(int* UniformLocation, const char* UniformName) {
	if (*UniformLocation == -1) {
		std::cout << "SHADER_UNIFORM_UNDEFINED | " << __FILE__ << " | " << __LINE__ << " | " << UniformName << std::endl;
	}
}

void LumeShader::SetUniformInt(const char* UniformName, const int UniformValue) {
	int UniformLocation = glGetUniformLocation(this->ShaderProgram, UniformName);
	ShaderHelper::UniformValidation(&UniformLocation, UniformName);
	glUniform1i(UniformLocation, UniformValue);
}
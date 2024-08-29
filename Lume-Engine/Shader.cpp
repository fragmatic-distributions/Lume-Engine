#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <map>

#include "Util.hpp"
#include "Shader.hpp"

// Creates a new shader to use
/*-----------------------------------------------------------------------------------------------------------*/
Shader::Shader(const char* VertexShaderPath, const char* FragmentShaderPath) {
	std::string VertexShaderCharacterArray = Util::OpenShaderFile(VertexShaderPath);
	std::string FragmentShaderCharatcerArray = Util::OpenShaderFile(FragmentShaderPath);

	const char* VertexShaderSource = VertexShaderCharacterArray.c_str();
	const char* FragmentShaderSource = FragmentShaderCharatcerArray.c_str();
	this->ShaderProgramInstance = glCreateProgram();

	// Check if file format is valid
	if (VertexShaderPath == NULL || VertexShaderPath == "") {
		this->Destroy();
		std::cout << "SHADER.CPP::INVALID_VERTEX_SHADER_FILE::ERROR, GOT : " << VertexShaderPath << std::endl;
		return;
	}
	else if (FragmentShaderPath == NULL || FragmentShaderPath == "") {
		this->Destroy();
		std::cout << "SHADER.CPP::INVALID_FRAGMENT_SHADER_FILE::ERROR, GOT : " << VertexShaderPath << std::endl;
		return;
	}

	unsigned int VertexShader, FragmentShader;

	VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShader, 1, &VertexShaderSource, NULL);
	glCompileShader(VertexShader);

	FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShader, 1, &FragmentShaderSource, NULL);
	glCompileShader(FragmentShader);

	// Check if shaders are valid
	GLint VertexShaderIvSucces;
	glGetShaderiv(VertexShader, GL_LINK_STATUS, &VertexShaderIvSucces);
	if (!VertexShaderIvSucces) {
		GLchar ShaderIvInfoLog;
		glGetShaderInfoLog(VertexShader, 512, NULL, &ShaderIvInfoLog);

		std::cout << "SHADER.CPP::VERTEX_SHADER::ERROR : " << ShaderIvInfoLog << std::endl;
		this->Destroy();
	}

	GLint FragShaderIvSucces;
	glGetShaderiv(FragmentShader, GL_LINK_STATUS, &FragShaderIvSucces);
	if (!FragShaderIvSucces) {
		GLchar ShaderIvInfoLog;
		glGetShaderInfoLog(FragmentShader, 512, NULL, &ShaderIvInfoLog);

		std::cout << "SHADER.CPP::FRAGMENT_SHADER::ERROR : " << ShaderIvInfoLog << std::endl;
		this->Destroy();
	}
	
	glAttachShader(this->ShaderProgramInstance, VertexShader);
	glAttachShader(this->ShaderProgramInstance, FragmentShader);
	glLinkProgram(this->ShaderProgramInstance);

	// Check If Program is Valid
	GLint ShaderProgramIsSucces;
	glGetProgramiv(this->ShaderProgramInstance, GL_LINK_STATUS, &ShaderProgramIsSucces);
	if (!ShaderProgramIsSucces) {
		GLchar ProgramIvInfoLog;
		glGetProgramInfoLog(this->ShaderProgramInstance, 512, NULL, &ProgramIvInfoLog);
		
		std::cout << "SHADER.CPP::PROGRAM::ERROR : " << ProgramIvInfoLog << std::endl;
		this->Destroy();
	}

	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);
}

// Uses the current set program on a instance
/*-----------------------------------------------------------------------------------------------------------*/
void Shader::UseShaderProgram() {
	if (this->ShaderProgramInstance == NULL) {
		std::cout << "SHADER.CPP::PROGRAM_UNDEFINED::ERROR, GOT : " << this->ShaderProgramInstance << std::endl;
		return;
	}
	glUseProgram(this->ShaderProgramInstance);
}

// Clears the program that is currently being used
/*-----------------------------------------------------------------------------------------------------------*/
void Shader::Destroy() {
	if (this->ShaderProgramInstance == NULL) {
		std::cout << "SHADER.CPP::DESTROY_PROGRAM_UNDEFINED::ERROR, GOT : " << this->ShaderProgramInstance << std::endl;
		return;
	}
	glDeleteProgram(this->ShaderProgramInstance);
}

// Gets all the uniforms
/*-----------------------------------------------------------------------------------------------------------*/
//void Shader::GetShaderUniforms() {
//	GLint ShaderUniforms = -1;
//	glGetProgramiv(this->ShaderProgramInstance, GL_ACTIVE_UNIFORMS, &ShaderUniforms);
//
//	for (int Increment = 0; Increment < ShaderUniforms; Increment++) {
//		int UniformSize = 0;
//		int UniformLength = 0;
//		GLenum UniformEnum = GL_ZERO;
//		char UniformName[100];
//
//		glGetActiveUniform(this->ShaderProgramInstance, Increment, sizeof(UniformName), &UniformLength, &UniformSize, &UniformEnum, UniformName);
//		int ShaderUniformLocation = glGetUniformLocation(this->ShaderProgramInstance, UniformName);
//
//		this->ShaderUniforms[UniformName] = ShaderUniformLocation;
//	}
//}

//█░░█ █▀▀▄ ░▀░ █▀▀ █▀▀█ █▀▀█ █▀▄▀█ █▀▀
//█░░█ █░░█ ▀█▀ █▀▀ █░░█ █▄▄▀ █░▀░█ ▀▀█
//░▀▀▀ ▀░░▀ ▀▀▀ ▀░░ ▀▀▀▀ ▀░▀▀ ▀░░░▀ ▀▀▀

// TODO: find a better fuckign way of doing this
// Cuz its a actual method of torture

// Returns a shader uniform
/*-----------------------------------------------------------------------------------------------------------*/
int Shader::GetShaderUniform(const char* UniformName, Shader::UniformType UniformType) {
	int ShaderUniformLocation = glGetUniformLocation(this->ShaderProgramInstance, UniformName);
	if (ShaderUniformLocation == -1) {
		std::cout << "SHADER.CPP::SET_SHADER_UNIFORM_ " << UniformType << "::UNIFORM_INVALID::ERROR, GOT : " << UniformName << std::endl;
		return -1;
	}
	return ShaderUniformLocation;
}
	
 //Sets shader float
void Shader::SetUniformFloat(const char* UniformName, const float UniformValue) {
	int ShaderUniformLocation = this->GetShaderUniform(UniformName, this->SHADER_UNIFORM_FLOAT);
	glUniform1f(ShaderUniformLocation, UniformValue);
}

// Set Shader Integer
void Shader::SetUniformInt(const char* UniformName, const int UniformValue) {
	int ShaderUniformLocation = this->GetShaderUniform(UniformName, this->SHADER_UNIFORM_INT);
	glUniform1i(ShaderUniformLocation, UniformValue);
}

// Set Shader Unsigned int
void Shader::SetUniformUint(const char* UniformName, const unsigned int UniformValue) {
	int ShaderUniformLocation = this->GetShaderUniform(UniformName, this->SHADER_UNIFORM_UINT);
	glUniform1ui(ShaderUniformLocation, UniformValue);
}

// Set Shader Integer Vector 1
void Shader::SetUniformIntVec(const char* UniformName, const glm::ivec1 UniformValue) {
	int ShaderUniformLocation = this->GetShaderUniform(UniformName, this->SHADER_UNIFORM_INTVEC1);
	GLint Int[1] = { UniformValue.x };
	glUniform1iv(ShaderUniformLocation, 1, Int);
}

// Set Shader For Unsigned Interger Vector 1
void Shader::SetUniformUintVec(const char* UniformName, const glm::uvec1 UniformValue) {
	int ShaderUniformLocation = this->GetShaderUniform(UniformName, this->SHADER_UNIFORM_UINTVEC1);
	GLint Int[1] = { UniformValue.x };
	glUniform1iv(ShaderUniformLocation, 1, Int);
}

// Sets a float vector 1
void Shader::SetUniformFloatVec(const char* UniformName, const glm::fvec1 UniformValue) {
	int ShaderUniformLocation = this->GetShaderUniform(UniformName, this->SHADER_UNIFORM_FLOATVEC1);
	GLfloat Float[1] = { UniformValue.x };
	glUniform1fv(ShaderUniformLocation, 1, Float);
}

// Set Shader For Bool
void Shader::SetUniformBool(const char* UniformName, const bool UniformValue) {
	int ShaderUniformLocation = this->GetShaderUniform(UniformName, this->SHADER_UNIFORM_BOOL);
	glUniform1i(ShaderUniformLocation, (int)UniformValue);
}
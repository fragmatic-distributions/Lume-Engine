#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <typeinfo>

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

//█░░█ █▀▀▄ ░▀░ █▀▀ █▀▀█ █▀▀█ █▀▄▀█ █▀▀
//█░░█ █░░█ ▀█▀ █▀▀ █░░█ █▄▄▀ █░▀░█ ▀▀█
//░▀▀▀ ▀░░▀ ▀▀▀ ▀░░ ▀▀▀▀ ▀░▀▀ ▀░░░▀ ▀▀▀

// Sets shader integer
/*-----------------------------------------------------------------------------------------------------------*/
void Shader::SetShaderUniform(const char* UniformName, Shader::Uniform Uniformtype, glm::vec4 UniformValue) {
	int ShaderUniformLocation = glGetUniformLocation(this->ShaderProgramInstance, UniformName);
	if (ShaderUniformLocation == -1) {
		std::cout << "SHADER.CPP::SET_SHADER_UNIFORM::UNIFORM_INVALID::ERROR, GOT : " << UniformName << std::endl;
		return;
	}

	std::cout << ShaderUniformLocation << std::endl;
	switch (Uniformtype) {
		case SHADER_UNIFORM_INT:
			glUniform1i(ShaderUniformLocation, UniformValue.x);
			break;
	//	case SHADER_UNIFORM_FLOAT:
	//		glUniform1f(ShaderUniformLocation, UniformValue);
	//		break;
	//	case SHADER_UNIFORM_UINT:
	//		glUniform1ui(ShaderUniformLocation, UniformValue);
	//		break;
	//	case SHADER_UNIFORM_VEC1:
	//		glUniform1fv(ShaderUniformLocation, UniformValue);
	//		break;
		case SHADER_UNIFORM_VEC4:
			std::cout << typeid(UniformValue).name() << std::endl;
			glUniform4i(ShaderUniformLocation, UniformValue.x, UniformValue.y, UniformValue.z, UniformValue.w);
			break;
	}
}



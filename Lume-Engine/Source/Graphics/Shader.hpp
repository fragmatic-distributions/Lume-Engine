#ifndef SHADER_H
#define SHADER_H
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <iostream>
#include <map>

class LumeShader {
public:
	static enum LumeShaderConfig : int {
		VERTEX =					GL_VERTEX_SHADER,
		FRAGMENT =					GL_FRAGMENT_SHADER,
		COMPUTE =					GL_COMPUTE_SHADER,
		GEOMETRY =					GL_GEOMETRY_SHADER,
	};

	unsigned int ShaderProgram;

	LumeShader(LumeShaderConfig ShaderType01);
	LumeShader(LumeShaderConfig ShaderType01, LumeShaderConfig ShaderType02);
	LumeShader(LumeShaderConfig ShaderType01, LumeShaderConfig ShaderType02, LumeShaderConfig ShaderType03);
	//~LumeShader();

	void CreateShader(const char* ShaderFile01);
	void CreateShader(const char* ShaderFile01, const char* ShaderFile02);
	void CreateShader(const char* ShaderFile01, const char* ShaderFile02, const char* ShaderFile03);

	void BindProgram();
	void UnbindProgram();
	void DestroyProgram();

	void SetUniformInt(const char* UniformName, const int UniformValue);
	void SetUniformMat4(const char* UniformName, const glm::mat4* UniformValue);
private:
	std::map <int, LumeShaderConfig> ShaderTypeBindings;
};

class ShaderHelper {
public:
	static enum CompilerType : int {
		SHADER =					1,
		PROGRAM =					2,
	};

	//static void DebugFileContents(std::map<LumeShader::LumeShaderConfig, std::string> FileContents);
	static std::map<LumeShader::LumeShaderConfig, std::string> FetchShaderFileContent(std::map<int, LumeShader::LumeShaderConfig>* ShaderTypeBindings,
																				   	  std::map<LumeShader::LumeShaderConfig, const char*> ShaderFiles);

	static int ValidateCompiler(unsigned int* CompilerID, CompilerType CompilerType);
	static void UniformValidation(int* UniformLocation, const char* UniformName);
};

#endif
//class Shader {
//public:
//	Shader(const char* VertexShaderPath, const char* FragmentShaderPath);
//	~Shader();
//
//	struct ShaderStruct {
//		unsigned int VertexShader;
//		unsigned int FragmentShader;
//		unsigned int ShaderProgram;
//
//		int VertexShaderIV;
//		int FragmentShaderIV;
//		int ShaderProgramIV;
//	};
//
//	void UseShaderProgram();
//	void Destroy();
//
//	// Uniform
//	void SetUniformInt(const char* UniformName, int UniformValue);
//
//	unsigned int ShaderObject;
//private:
//	bool ProgramIsActive;
//
//	void UniformValidation(int UniformLocation, const char* UniformName);
//};

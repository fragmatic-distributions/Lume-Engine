#include <iostream>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <map>

#include "Util.hpp"

class Shader {
public:
	Shader(const char* VertexShaderPath, const char* FragmentShaderPath);
	void UseShaderProgram();
	void Destroy();

	enum UniformType : int {
		SHADER_UNIFORM_FLOAT = 1,
		SHADER_UNIFORM_INT = 2,
		SHADER_UNIFORM_UINT = 3,
		SHADER_UNIFORM_BOOL = 4,
		SHADER_UNIFORM_INTVEC1 = 5,
		SHADER_UNIFORM_UINTVEC1 = 6,
		SHADER_UNIFORM_FLOATVEC1 = 7,
	};

	// Shader Contact
	void SetUniformFloat(const char* UniformName, const float UniformValue);
	void SetUniformInt(const char* UniformName, const int UniformValue);
	void SetUniformUint(const char* UniformName, const unsigned int UniformValue);
	void SetUniformIntVec(const char* UniformName, const glm::ivec1 UniformValue);
	void SetUniformBool(const char* UniformName, const bool UniformValue);
	void SetUniformUintVec(const char* UniformName, const glm::uvec1 UniformValue);
	void SetUniformFloatVec(const char* UniformName, const glm::fvec1 UniformValue);
private:	
	//std::map<std::string, int> ShaderUniforms = {}; // Dk what limit i should put
	int GetShaderUniform(const char* UniformName, UniformType UniformType);
	
	unsigned int ShaderProgramInstance = 0;
};
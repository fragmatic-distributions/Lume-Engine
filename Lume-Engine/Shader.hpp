#include <iostream>
#include <glm/glm.hpp>
#include <glad/glad.h>

#include "Util.hpp"

class Shader {
public:
	Shader(const char* VertexShaderPath, const char* FragmentShaderPath);
	void UseShaderProgram();
	void Destroy();

	enum Uniform {
		SHADER_UNIFORM_INT = 1,
		SHADER_UNIFORM_FLOAT = 2,
		SHADER_UNIFORM_UINT = 3,
		SHADER_UNIFORM_VEC1 = 4,

		SHADER_UNIFORM_VEC4 = 100,
	};

	// Shader Contact
	void SetShaderUniform(const char* UniformName, Shader::Uniform Uniformtype, glm::vec4 UniformValue);
private:
	unsigned int ShaderProgramInstance;
};
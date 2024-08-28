#include <iostream>
#include <glad/glad.h>
#include "Util.hpp"

class Shader {
public:
	Shader(const char* VertexShaderPath, const char* FragmentShaderPath);
	void UseShaderProgram();
	void Destroy();

private:
	unsigned int ShaderProgramInstance;
};
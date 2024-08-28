#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

namespace Util {
    // Opens a shader file
    /*-----------------------------------------------------------------------------------------------------------*/
    std::string OpenShaderFile(const char* ShaderName) {
        std::string FileContents;
        std::ifstream ShaderFileInstance;

        ShaderFileInstance.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try {
            ShaderFileInstance.open(ShaderName);

            std::stringstream ShaderContentInstance;
            ShaderContentInstance << ShaderFileInstance.rdbuf();

            ShaderFileInstance.close();
            FileContents = ShaderContentInstance.str();
        }
        catch (std::ifstream::failure ErrorInstance) {
            std::cout << "UTIL.CPP::OPEN_SHADER_FILE::FILE_READING::ERROR";
            return "";
        }
        return FileContents;
    }
}
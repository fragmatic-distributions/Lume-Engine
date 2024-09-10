#ifndef MODEL_H
#define MODEL_H
#include <iostream>
#include <map>
#include <assimp/Importer.hpp>
#include <assimp/mesh.h>
#include <glad/glad.h>

struct BufferInfo {
	std::vector<float> Vertices;
	std::vector<int> Indices;

	size_t VertexBufferSize;
	size_t IndexBufferSize;

	std::string AlbedoTexture;
};

class Model {
public:
	Model(const char* GltfPath);
	std::vector<BufferInfo> GetBuffers();
private:
	std::vector<BufferInfo> Buffers;

	void ProcessModel(const aiScene* ModelScene);
	void ProcessMesh(const aiMesh* Mesh, const aiScene* ModelData);
};

#endif 

//#ifndef MODEL_H
//#define MODEL_H
//#include <tiny_gltf/tiny_gltf.h>
//#include <iostream>
//#include <map>
//#include <glm/glm.hpp>
//#include <glad/glad.h>
//
//struct BufferInfo {
//	GLenum BufferType = 0; //  GL_BUFFER_ARRAY or GL_ELEMENT_BUFFER_ARRAY
//	size_t BufferSize = 0;
//	const float* BufferData = 0; // vertices or indices
//};
//
//struct IndexBufferInfo {
//	GLenum BufferType = 0; //  GL_BUFFER_ARRAY or GL_ELEMENT_BUFFER_ARRAY
//	size_t BufferSize = 0;
//	const unsigned char* BufferData = 0; // vertices or indices
//};
//
//struct ArrayInfo {
//	int AttributeIndex = 0;
//	int Size = 0;
//	int StrideSize = 0;
//	int SectionSize = 0;
//};
//
//struct ModelData {
//	std::map<std::string, BufferInfo> Buffers;
//	std::map<std::string, IndexBufferInfo> IndexBuffer;
//	std::map<std::string, ArrayInfo> Arrays;
//};
//
//class Model {
//public:
//	Model(const char* GltfPath);
//
//	struct ModelData ModelDataInstance;
//private:
//	glm::mat4 GetNodeMatrix(tinygltf::Node* Node);
//	void ProcessMesh(tinygltf::Model* Model, tinygltf::Mesh* Mesh);
//	BufferInfo FetchBufferData(tinygltf::Accessor* Accessor, tinygltf::Model* Model);
//	void ProcessData(tinygltf::Model* Model);
//};
//
//#endif
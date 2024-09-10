#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/mesh.h>
#include <assimp/material.h>
#include <glm\glm.hpp>
#include <iostream>
#include <vector>
#include "Model.hpp"

std::vector<BufferInfo> Model::GetBuffers() {
	return this->Buffers;
}

Model::Model(const char* GltfPath) {
	Assimp::Importer Importer;
	const aiScene* Scene = Importer.ReadFile(GltfPath, aiProcess_Triangulate);
	
	if (!Scene || Scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !Scene->mRootNode) {
		std::cout << "assimp failed, file : " << GltfPath << " | " << Importer.GetErrorString() << std::endl;
		return;
	}

	this->ProcessModel(Scene);
}

void Model::ProcessModel(const aiScene* ModelScene) {
	const aiNode* RootNode = ModelScene->mRootNode;

	std::cout << RootNode->mNumMeshes << std::endl;
	for (unsigned int i = 0; i < RootNode->mNumMeshes; i++) {
		const aiMesh* Mesh = ModelScene->mMeshes[RootNode->mMeshes[i]];
		ProcessMesh(Mesh, ModelScene);
		// prob apply some transform here
	}

	//struct BufferInfo BufferInfo;
	//std::vector<float> Vertices;
	//std::vector<int> Indices;
	//for (unsigned int i = 0; i < RootNode->mNumMeshes; i++) {
	//	Mesh MeshInformation = this->MeshData[i];

	//	for (unsigned int v = 0; v < MeshInformation.Vertices.size(); v++) {
	//		Vertices.push_back(MeshInformation.Vertices[v]);
	//	}

	//	for (unsigned int in = 0; in < MeshInformation.Indices.size(); in++) {
	//		Indices.push_back(MeshInformation.Indices[in]);
	//	}
	//}

	//BufferInfo.Vertices = Vertices;
	//BufferInfo.Indices = Indices;
	//BufferInfo.VertexBufferSize = sizeof(Vertices);
	//BufferInfo.IndexBufferSize = sizeof(Indices);
	//this->Buffer = BufferInfo;
}

void Model::ProcessMesh(const aiMesh* Mesh, const aiScene* ModelData) {
	std::vector<float> Vertices;
	std::vector<int> Indices;

	std::vector<std::string> Test;

	for (unsigned int i = 0; i < Mesh->mNumVertices; i++) {
		glm::vec2 texCoorData = glm::vec2(0.0f);
		if (Mesh->mTextureCoords[0]) {
			texCoorData = glm::vec2(Mesh->mTextureCoords[0][i].x, Mesh->mTextureCoords[0][i].y);
		}

		// TODO : remove vec3 components
		Vertices.push_back(Mesh->mVertices[i].x);
		Vertices.push_back(Mesh->mVertices[i].y);
		Vertices.push_back(Mesh->mVertices[i].z);

		Vertices.push_back(texCoorData.x);
		Vertices.push_back(texCoorData.y);

		Vertices.push_back(Mesh->mNormals[i].x);
		Vertices.push_back(Mesh->mNormals[i].y);
		Vertices.push_back(Mesh->mNormals[i].z);
	}

	for (unsigned int i = 0; i < Mesh->mNumFaces; i++) {
		aiFace Face = Mesh->mFaces[i];
		for (unsigned int f = 0; f < Face.mNumIndices; f++) {
			Indices.push_back(Face.mIndices[f]);
		}
	}

	struct BufferInfo MeshInformation;
	MeshInformation.Vertices = Vertices;
	MeshInformation.VertexBufferSize = sizeof(float) * Vertices.size();
	MeshInformation.Indices = Indices;
	MeshInformation.IndexBufferSize = sizeof(int) * Indices.size();
	MeshInformation.AlbedoTexture = "";

	if (Mesh->mMaterialIndex >= 0) {
		aiMaterial* Material = ModelData->mMaterials[Mesh->mMaterialIndex];

		aiString AlbedoInfo;
		Material->GetTexture(aiTextureType_DIFFUSE, 0, &AlbedoInfo);
		MeshInformation.AlbedoTexture = static_cast<std::string>(AlbedoInfo.C_Str());
	}

	this->Buffers.push_back(MeshInformation);
}

//#define GLM_ENABLE_EXPERIMENTAL
//#include <glad/glad.h>
//#include <iostream>
//#include <map>
//#include <glm/glm.hpp>
//#include <glm/gtx/quaternion.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include "Model.hpp"
//
//struct NodeInfo {
//	glm::vec3 Translation					= glm::vec3(0.0f);
//	glm::vec3 Scale							= glm::vec3(0.0f);
//	glm::vec4 Quat							= glm::vec4(0.0f);
//};
//
//glm::mat4 Model::GetNodeMatrix(tinygltf::Node* Node) {
//	struct NodeInfo NodeInformation;
//
//	if (Node->translation.size() != 0) {
//		NodeInformation.Translation = glm::vec3(Node->translation[0]
//			, Node->translation[1]
//			, Node->translation[2]);
//	}
//	if (Node->rotation.size() != 0) {
//		NodeInformation.Quat = glm::vec4(Node->rotation[0]
//			, Node->rotation[1]
//			, Node->rotation[2]
//			, Node->rotation[3]);
//	}
//	if (Node->scale.size() != 0) {
//		NodeInformation.Scale = glm::vec3(Node->scale[0]
//			, Node->scale[1]
//			, Node->scale[2]);
//	}
//
//	glm::quat Quaternion = glm::quat(NodeInformation.Quat);
//	glm::mat4 Transform = glm::toMat4(Quaternion);
//
//	Transform = glm::translate(Transform, NodeInformation.Translation);
//	Transform = glm::scale(Transform, NodeInformation.Scale);
//
//	return Transform;
//}
//
//IndexBufferInfo FetchIndexBufferData(tinygltf::Accessor* Accessor, tinygltf::Model* Model) {
//	struct IndexBufferInfo Buffer;
//
//	const tinygltf::BufferView& ModelViewBuffer = Model->bufferViews[Accessor->bufferView];
//	const tinygltf::Buffer& ModelBuffer = Model->buffers[ModelViewBuffer.buffer];
//
//	if (ModelViewBuffer.target == 0) {
//		return Buffer;
//	}
//	const unsigned char* data = (&ModelBuffer.data.at(0) + ModelViewBuffer.byteOffset);
//
//	Buffer.BufferType = ModelViewBuffer.target;
//	Buffer.BufferSize = ModelViewBuffer.byteLength;
//	Buffer.BufferData = data;
//
//	return Buffer;
//}
//
//BufferInfo Model::FetchBufferData(tinygltf::Accessor* Accessor, tinygltf::Model* Model) {
//	struct BufferInfo Buffer;
//
//	const tinygltf::BufferView& ModelViewBuffer = Model->bufferViews[Accessor->bufferView];
//	const tinygltf::Buffer& ModelBuffer = Model->buffers[ModelViewBuffer.buffer];
//
//	if (ModelViewBuffer.target == 0) {
//		return Buffer;
//	}
//	const float* positionsIndices = reinterpret_cast<const float*>(&ModelBuffer.data[ModelViewBuffer.byteOffset + Accessor->byteOffset]);
//
//	Buffer.BufferType = ModelViewBuffer.target;
//	Buffer.BufferSize = ModelViewBuffer.byteLength;
//	Buffer.BufferData = positionsIndices;
//
//	return Buffer;
//}
//
//void Model::ProcessMesh(tinygltf::Model* Model, tinygltf::Mesh* Mesh) {
//	/* In each Mesh contain 4 enums buffers
//		1 -> Vert Pos
//		2 -> Texturepos
//		3 -> Normals
//		4 -> indices
//	*/
//	//for (int i = 0; i < Model->bufferViews.size(); i++) {
//	//	tinygltf::BufferView BuffferView = Model->bufferViews[i];
//	//	if (BuffferView.target == 0) {
//	//		continue;
//	//	}
//
//	//	tinygltf::Buffer Buffer = Model->buffers[BuffferView.buffer];
//	//	struct BufferInfo VBO;
//
//	//	VBO.BufferType = BuffferView.target;
//	//	VBO.BufferSize = BuffferView.byteLength;
//	//	VBO.BufferData = &Buffer.data.at(0) + BuffferView.byteOffset;
//
//	//	if (i == 0) {
//	//		ModelDataInstance.Buffers["POSITION"] = VBO;
//	//	}
//	//	else if (i == 1) {
//	//		ModelDataInstance.Buffers["TEXCOORD_0"] = VBO;
//	//	}
//	//	else if (i == 2) {
//	//		ModelDataInstance.Buffers["NORMAL"] = VBO;
//	//	}
//	//	else if (i == 3) {
//	//		ModelDataInstance.Buffers["INDEX"] = VBO;
//	//	}
//	//}
//
//	for (int i = 0; i < Mesh->primitives.size(); i++) {
//		tinygltf::Primitive& Primitive = Mesh->primitives[i];
//
//		tinygltf::Accessor POSITION_Accessor = Model->accessors[Primitive.attributes["POSITION"]];
//		BufferInfo POSITION_BufferInfo = this->FetchBufferData(&POSITION_Accessor, Model);
//		ModelDataInstance.Buffers["POSITION"] = POSITION_BufferInfo;
//
//		tinygltf::Accessor TEXCOORD_Accessor = Model->accessors[Primitive.attributes["TEXCOORD_0"]];
//		BufferInfo TEXCOORD_BufferInfo = this->FetchBufferData(&TEXCOORD_Accessor, Model);
//		ModelDataInstance.Buffers["TEXCOORD_0"] = TEXCOORD_BufferInfo;
//
//		tinygltf::Accessor NORMAL_Accessor = Model->accessors[Primitive.attributes["NORMAL"]];
//		BufferInfo NORMAL_BufferInfo = this->FetchBufferData(&NORMAL_Accessor, Model);
//		ModelDataInstance.Buffers["NORMAL"] = NORMAL_BufferInfo;
//
//		tinygltf::Accessor INDEX_accessor = Model->accessors[Primitive.indices];
//		IndexBufferInfo INDEX_BufferInfo = FetchIndexBufferData(&INDEX_accessor, Model);
//		ModelDataInstance.IndexBuffer["INDEX"] = INDEX_BufferInfo;
//
//		// Grabs the vao attribs
//		std::map<std::string, int>::iterator it;
//		for (it = Primitive.attributes.begin(); it != Primitive.attributes.end(); it++) {
//			const char* AttribType = it->first.c_str();
//			int AttribIndex = it->second;
//
//			tinygltf::Accessor AttribAccessor = Model->accessors[AttribIndex];
//			int StrideSize = AttribAccessor.ByteStride(Model->bufferViews[AttribAccessor.bufferView]);
//
//			int Size = 1;
//			if (AttribAccessor.type != TINYGLTF_TYPE_SCALAR) {
//				Size = AttribAccessor.type;
//			}
//
//			int Attribute = -1;
//			if (AttribType == "VERTEX");
//			Attribute = 0;
//			if (AttribType == "TEXCOORD_0");
//			Attribute = 1;
//			if (AttribType == "NORMAL");
//			Attribute = 2;
//
//			ArrayInfo VAO;
//			VAO.StrideSize = StrideSize;
//			VAO.Size = Size;
//			VAO.AttributeIndex = Attribute;
//			VAO.SectionSize = AttribAccessor.byteOffset;
//
//			ModelDataInstance.Arrays[AttribType] = VAO;
//		}
//	}
//}
//
//void Model::ProcessData(tinygltf::Model* Model) {
//	for (int i = 0; i < (*Model).nodes.size(); i++) {
//		tinygltf::Node Node = (*Model).nodes[i];
//		glm::mat4 NodeTransform = this->GetNodeMatrix(&Node);
//
//		tinygltf::Mesh Mesh = (*Model).meshes[Node.mesh];
//		this->ProcessMesh(Model, &Mesh);
//	}
//}
//
//
//Model::Model(const char* GltfPath) {
//	tinygltf::Model ModelInstance;
//	tinygltf::TinyGLTF Loader;
//	std::string Error;
//	std::string Warning;
//
//	bool Return = Loader.LoadASCIIFromFile(&ModelInstance, &Error, &Warning, GltfPath, 10);
//
//#ifdef  MODEL_DEBUG
//	if (!Error.empty()) {
//		std::cout << "Model Error : " << Error << std::endl;
//}
//
//	if (!Warning.empty()) {
//		std::cout << "Model Warning : " << Warning << std::endl;
//	}
//#endif //  MODEL_DEBUG
//
//	if (!Return) {
//		std::cout << "Mode Parse Error" << std::endl;
//		return;
//	}
//
//	this->ProcessData(&ModelInstance);
//}

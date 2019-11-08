#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "gltf_model.h"
#include "gltf_scene.h"

GltfModel::GltfModel(string_view filename):Model(nullptr,nullptr)
{
	//mesh = make(Mesh);
	TexturePtr t = make(Texture, "main/mesh/man2.png");
	material = make(BoneTextureMaterial,t);
	loadModel(filename.data());
	gpu_id= bindModel(gltf_model);
}

bool GltfModel::loadModel(const char* filename) {
	
	std::string err;
	std::string warn;

	bool res = tiny_gltf.LoadASCIIFromFile(&gltf_model, &err, &warn, filename);
	if (!warn.empty()) {
		std::cout << "WARN: " << warn << std::endl;
	}

	if (!err.empty()) {
		std::cout << "ERR: " << err << std::endl;
	}

	if (!res)
		std::cout << "Failed to load glTF: " << filename << std::endl;
	else
		std::cout << "Loaded glTF: " << filename << std::endl;

	return res;
}
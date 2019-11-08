// gltfLoader.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "gltf_header.h"

class VertexAttr
{
public:
	VertexAttrType type=-1;
	bool need_normalized = false;
	int data_type = GL_FLOAT;
	int component_num = 0;
	int size = 0;
};

struct GxoModelHeader{
	VertexAttr attr[20];
	int vertex_offset=0;
	int vertex_size=0;

	int index_offset=0;
	int index_size=0;


};

bool loadModel(tinygltf::Model& model, const char* filename) {
	tinygltf::TinyGLTF loader;
	std::string err;
	std::string warn;

	bool res = loader.LoadASCIIFromFile(&model, &err, &warn, filename);
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
int main()
{
    std::cout << "Hello World!\n";

	tinygltf::Model model;
	if (!loadModel(model, "main/mesh/AnimatedTriangle.gltf")) return 1;



	return 1;
}

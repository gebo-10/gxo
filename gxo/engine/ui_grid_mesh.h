#ifndef GXO_UI_MESH_H
#define GXO_UI_MESH_H
#include"mesh.h"
namespace gxo {
	class UiGridMesh :public Mesh
	{
	public:
		int segx;
		int segy;
		int width;
		int height;

		float* vertices=nullptr;
		unsigned short index[6] = { 0,1,2, 2,3,1 };
		UiGridMesh() {}
		~UiGridMesh() {}
		void build(int width, int height, int segx = 1, int segy = 1) {
			if (vertices != nullptr) {
				delete vertices;
				vertices = nullptr;
			}

			this->width = width;
			this->height = height;
			this->segx = segx;
			this->segy = segy;
			

			vertices=new float[20] {
				// Positions         // Colors
				0.0f, 0.0f,0.0f,							0.0f, 0.0f,
				(float)width,  0.0f,0.0f,				1.0f, 0.0f,
				0.0f, (float)height,0.0f,				0.0f, 1.0f,
				(float)width,  (float)height,0.0f,		1.0f, 1.0f,
			};
			
			
			vertex.data = (byte*)vertices;
			vertex.size = 20 *sizeof(float);

			indices.data = (byte*)index;
			indices.size = sizeof(index);
			size = 6;

			vertex_attr.push_back(GPU_VEC3);
			vertex_attr.push_back(GPU_VEC2);
		}

	private:

	};
	typedef std::shared_ptr<UiGridMesh> UiMeshPtr;
}
#endif
#ifndef GXO_MESH_H
#define GXO_MESH_H
#include"gpu_type.h"
#include"gxo_buffer.h"
#include"resource.h"
#include"gpu.h"

#include"gxo_name.h"
#include <vector>
#include"gpu_object.h"
namespace gxo {
	class Mesh:public Resource
	{
	public:
		//struct VertexAttr
		//{
		//	Name name;
		//	GPUDataType data_type;
		//};
		std::vector<GPUDataType> vertex_attr;
		Buffer vertex;
		Buffer indices;
		GPUObject gpu_object;

		uint primitive= GL_TRIANGLE_STRIP;
		uint size ;
		Mesh(){}
		~Mesh(){}
		
		void gpu_load() override {
			gpu_object.create(vertex_attr,vertex,indices);
		}

	private:

	};
	typedef std::shared_ptr<Mesh> MeshPtr;
}
#endif
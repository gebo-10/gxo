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
		struct VertexAttr
		{
			Name name;
			GPUDataType data_type;
		};
		std::vector<VertexAttr> vertex_attr;
		Buffer vertex;
		Buffer indices;
		GPUObject gpu_object;

		Mesh(){}
		~Mesh(){}

	private:

	};
	typedef std::shared_ptr<Mesh> MeshPtr;
}
#endif
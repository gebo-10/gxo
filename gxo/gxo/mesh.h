#ifndef _MESH_H
#define _MESH_H
#include"resource.h"
#include"gpu.h"
#include"name_manager.h"
#include <vector>
#include"base.h"
namespace gxo {
	class Mesh
	{
	public:
		struct VertexAttr
		{
			Name name;
			GPUDataType data_type;
		};
		std::vector<VertexAttr> vertex_attr;
		Buffer vertex;
		Buffer indices;  //如果大于65536 需要 用 uint32来索引
		GPUID gpu_object_id;
	public:
		Mesh()
		{
		}

		~Mesh()
		{
		}

	private:

	};
}
#endif
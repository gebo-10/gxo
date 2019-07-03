#ifndef GXO_GPU_OBJECT_H
#define GXO_GPU_OBJECT_H
#include <vector>
#include <cassert>
#include "gpu_api.h"
#include "gpu_type.h"
#include "gpu_buffer.h"
namespace gxo {
	class GPUObject
	{
	public:
		GPUID gpu_id;
		GPUBuffer vertex;
		GPUBuffer index;
		GPUObject():gpu_id(-1)
		{
		}

		~GPUObject()
		{
		}
		void create(std::vector<GPUDataType> &vertex_attr, Buffer & vertex_buffer, Buffer &index_buffer) {
			glGenVertexArrays(1, &gpu_id);
			glBindVertexArray(gpu_id);
			index.create(index_buffer, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
			vertex.create(vertex_buffer, GL_ARRAY_BUFFER, GL_STATIC_DRAW);

			int trip_size=0;
			for (auto type : vertex_attr) {
				trip_size += GPUDataTypeInfo::get_size();
			}

			for (int i = 0; i < vertex_attr.size(); i++)
			{
				GPUDataType type = vertex_attr[i];
				glEnableVertexAttribArray(i);
				switch (type) {
				case GPU_VEC3:
					glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, false, trip_size, 0);
				}
				
			}
			
		}
		void bind(void) {
			assert(gpu_id != -1);
			glBindVertexArray(gpu_id);
		}
		void unbind(void) {
			glBindVertexArray(0);
		}
	};

}
#endif
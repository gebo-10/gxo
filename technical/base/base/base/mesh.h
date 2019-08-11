#ifndef GXO_MESH_H
#define GXO_MESH_H
#include"core_base.h"
#include"buffer.h"
#include <vector>
#include "gpu_buffer.h"

enum VertexAttrType {
	VAT_POSITION,
	VAT_NORMAL,
	VAT_UV,
};
class VertexAttr
{
public:
	VertexAttrType type;
	bool need_normalized = false;
	int data_type=GL_FLOAT;
	int component_num=0;
	int size=0;
};

	class Mesh 
	{
	public:
		GPUID gpu_id = 0;
		std::vector<VertexAttr> vertex_attr;
		Buffer vertex;
		Buffer indices;

		uint primitive = GL_TRIANGLES;
		uint element_size;


		GPUBuffer gpu_vertex;
		GPUBuffer gpu_index;

		Mesh() {
			
		}

		~Mesh() {}

		void build() {
			create( vertex, indices);
		}
		void create( Buffer& vertex_buffer, Buffer& index_buffer) {
			glGenVertexArrays(1, &gpu_id);
			glBindVertexArray(gpu_id);

			gpu_vertex.create(vertex_buffer, GL_ARRAY_BUFFER, GL_STATIC_DRAW);

			int trip_size = 0;
			for (auto attr : vertex_attr) {
				trip_size += attr.size;
			}
			int offset = 0;
			for (auto attr : vertex_attr)
			{
				glEnableVertexAttribArray(attr.type);
				glVertexAttribPointer((GLuint)attr.type, attr.component_num, attr.data_type, attr.need_normalized, trip_size, (const GLvoid*)offset);
				offset += attr.size;
			}

			gpu_index.create(index_buffer, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
			glBindVertexArray(0);
		}
		void bind(void) {
			assert(gpu_id != 0);
			glBindVertexArray(gpu_id);
		}
		void unbind(void) {
			glBindVertexArray(0);
		}
		void destroy() {
			glDeleteVertexArrays(1, &gpu_id);
		}

		void add_attr(VertexAttr &va) {
			vertex_attr.push_back(va);
		}

		void add_default_attr(VertexAttrType type) {
			VertexAttr va;
			va.type = type;
			switch (type)
			{
			case VAT_POSITION:
				va.component_num = 3;
				va.data_type = GL_FLOAT;
				va.need_normalized = false;
				va.size = sizeof(float) * 3;
				break;
			case VAT_NORMAL:
				va.component_num = 3;
				va.data_type = GL_FLOAT;
				va.need_normalized = false;
				va.size = sizeof(float) * 3;
				break;
			case VAT_UV:
				va.component_num = 2;
				va.data_type = GL_FLOAT;
				va.need_normalized = false;
				va.size = sizeof(float) * 2;
				break;
			default:
				break;
			}
			add_attr(va);
		}

	private:

	};
	typedef std::shared_ptr<Mesh> MeshPtr;

#endif
#ifndef GXO_MESH_H
#define GXO_MESH_H
#include"core_base.h"
#include"buffer.h"
#include <vector>
#include "gpu_buffer.h"

enum VertexAttrType {
	VAT_POSITION,
	VAT_NORMAL,
	VAT_UV0,
	VAT_UV1,
	VAT_BONEIDS,
	VAT_WEIGHTS,
};

struct BoneAnimation
{
	int duration;
	int ticks_per_second;
	std::vector<Transform3d> keys;
};

#define MAX_BONE_NUM 50
struct VertexBoneData {
	int bone_id;
	float weight;
};

struct BoneNode
{
	string name;
	int bone_id;
	mat4 node_transform;
	mat4 offset_matrix;
	mat4 final_matrix;
	std::vector<BoneNode*> children;
	BoneAnimation animation;
	mat4 GlobalInverseTransform;
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

		int bone_num=0;
		mat4 bones[MAX_BONE_NUM];

		BoneNode *bone_tree;

		uint primitive = GL_TRIANGLES;
		uint element_size;


		GPUBuffer gpu_vertex;
		GPUBuffer gpu_index;

		Mesh() {
			//memset(bones, 0, sizeof(bones));
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
				if (attr.data_type==GL_FLOAT)
				{
					glVertexAttribPointer((GLuint)attr.type, attr.component_num, attr.data_type, attr.need_normalized, trip_size, (const GLvoid*)offset);
				}
				else if(attr.data_type == GL_INT){
					glVertexAttribIPointer((GLuint)attr.type, attr.component_num, attr.data_type, trip_size, (const GLvoid*)offset);
				}
				offset += attr.size;
			}

			gpu_index.create(index_buffer, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
			glBindVertexArray(0);
		}
		void bind() {
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
			case VAT_UV0:
				va.component_num = 2;
				va.data_type = GL_FLOAT;
				va.need_normalized = false;
				va.size = sizeof(float) * 2;
				break;
			case VAT_BONEIDS:
				va.component_num = 4;
				va.data_type = GL_FLOAT;
				va.need_normalized = false;
				va.size = sizeof(float) * 4;
				break;
			case VAT_WEIGHTS:
				va.component_num = 4;
				va.data_type = GL_FLOAT;
				va.need_normalized = false;
				va.size = sizeof(float) * 4;
				break;
			default:
				break;
			}
			add_attr(va);
		}


		void update_bone_node(int key, BoneNode* node, const mat4& parent) {

			//node->final_matrix = parent * node->animation.keys[key].matrix();

			node->final_matrix = parent *node->node_transform;
			//bones[node->bone_id] = glm::transpose(node->final_matrix * node->offset_matrix ) ;
			bones[node->bone_id] = glm::transpose(node->final_matrix*node->offset_matrix) ;
			Transform3d t;
			t.rotate = vec3(0, 0,0);
			bones[node->bone_id] = t.matrix();
			for (auto item : node->children)
			{
				update_bone_node(key, item, node->final_matrix);
			}
		}
		void update_bone(int key) {
			key = 0;
			update_bone_node(key,bone_tree,mat4(1.0));
		}

	};
	typedef std::shared_ptr<Mesh> MeshPtr;

#endif
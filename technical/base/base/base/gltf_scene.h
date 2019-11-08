
#pragma once

#include <stdlib.h>
#include <string>
#include <fstream>
#include <vector>
#include<iostream>

#include "gltf_model.h"


//#define GLM_FORCE_RADIANS
//#define GLM_FORCE_DEPTH_ZERO_TO_ONE
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <glm/gtx/string_cast.hpp>
//
//
//#define TINYGLTF_IMPLEMENTATION
//#define TINYGLTF_NO_STB_IMAGE_WRITE
//#define STB_IMAGE_IMPLEMENTATION
//#define STBI_MSC_SECURE_CRT
//#include "tiny_gltf.h"

// Changing this value here also requires changing it in the vertex shader
#define MAX_NUM_JOINTS 128u

#include "core_base.h"
#include "mesh.h"
namespace vkglTF
{
	struct Node;

	struct BoundingBox {
		glm::vec3 min;
		glm::vec3 max;
		bool valid = false;
		BoundingBox() {};
		BoundingBox(glm::vec3 min, glm::vec3 max) : min(min), max(max) {}
		BoundingBox getAABB(glm::mat4 m) {
			glm::vec3 min = glm::vec3(m[3]);
			glm::vec3 max = min;
			glm::vec3 v0, v1;

			glm::vec3 right = glm::vec3(m[0]);
			v0 = right * this->min.x;
			v1 = right * this->max.x;
			min += glm::min(v0, v1);
			max += glm::max(v0, v1);

			glm::vec3 up = glm::vec3(m[1]);
			v0 = up * this->min.y;
			v1 = up * this->max.y;
			min += glm::min(v0, v1);
			max += glm::max(v0, v1);

			glm::vec3 back = glm::vec3(m[2]);
			v0 = back * this->min.z;
			v1 = back * this->max.z;
			min += glm::min(v0, v1);
			max += glm::max(v0, v1);

			return BoundingBox(min, max);
		}
	};

	/*
		glTF material class
	*/
	struct Material {
		
	};

	/*
		glTF primitive
	*/
	struct Primitive {
		uint32_t type;
		uint32_t firstIndex;
		uint32_t indexCount;
		uint32_t vertexCount;
		//Material& material;
		bool hasIndices;

		BoundingBox bb;

		Primitive(uint32_t type,uint32_t firstIndex, uint32_t indexCount, uint32_t vertexCount) : type(type), firstIndex(firstIndex), indexCount(indexCount), vertexCount(vertexCount) {
			hasIndices = indexCount > 0;
		};

		void setBoundingBox(glm::vec3 min, glm::vec3 max) {
			bb.min = min;
			bb.max = max;
			bb.valid = true;
		}
	};

	/*
		glTF mesh
	*/
	struct Mesh {

		std::vector<Primitive*> primitives;

		BoundingBox bb;
		BoundingBox aabb;

		struct UniformBuffer {
			unsigned int ubo_id;
			unsigned int bind_point=0;
		} uniformBuffer;

		struct UniformBlock {
			glm::mat4 matrix;
			glm::mat4 jointMatrix[MAX_NUM_JOINTS]{};
			float jointcount{ 0 };
		} uniformBlock;

		Mesh(glm::mat4 matrix) {
			this->uniformBlock.matrix = matrix;
			init_ubo();
		};

		~Mesh() {
			for (Primitive* p : primitives)
				delete p;
		}

		void init_ubo() {
			GLuint buf;
			glGenBuffers(1, &buf); // 创建缓存，此时仅仅创建了缓存句柄（name、handle、id，就那个意思），对象并没有被创建。
	
			glBindBuffer(GL_UNIFORM_BUFFER, buf); // 在首次绑定时会通过句柄构造对象。
			glBufferData(GL_UNIFORM_BUFFER,sizeof(UniformBlock), nullptr, GL_STATIC_DRAW); // 注意显存中内容是未定义的，在指定数据前不可使用。
			

			glBindBufferBase(GL_UNIFORM_BUFFER, 1, buf); 
			glBindBuffer(GL_UNIFORM_BUFFER, 0); // 为了安全解除绑定。
			uniformBuffer.ubo_id = buf;
		}

		void update_ubo() {
			glBindBuffer(GL_UNIFORM_BUFFER, uniformBuffer.ubo_id);
			glBufferData(GL_UNIFORM_BUFFER, sizeof(UniformBlock), &uniformBlock, GL_STATIC_DRAW); // 注意显存中内容是未定义的，在指定数据前不可使用。
		}

		void render() {
			//glBindBufferBase(GL_UNIFORM_BUFFER, 0, uniformBuffer.ubo_id);
			//??
			glDrawElements(primitives[0]->type, primitives[0]->indexCount, GL_UNSIGNED_INT, 0);
		}



		void setBoundingBox(glm::vec3 min, glm::vec3 max) {
			bb.min = min;
			bb.max = max;
			bb.valid = true;
		}
	};

	/*
		glTF skin
	*/
	struct Skin {
		std::string name;
		Node* skeletonRoot = nullptr;
		std::vector<glm::mat4> inverseBindMatrices;
		std::vector<Node*> joints;
	};

	/*
		glTF node
	*/
	struct Node {
		Node* parent;
		uint32_t index;
		std::vector<Node*> children;
		glm::mat4 matrix;
		std::string name;
		Mesh* mesh;
		Skin* skin;
		int32_t skinIndex = -1;
		glm::vec3 translation{};
		glm::vec3 scale{ 1.0f };
		glm::quat rotation{};
		BoundingBox bvh;
		BoundingBox aabb;

		glm::mat4 localMatrix() {
			return glm::translate(glm::mat4(1.0f), translation) * glm::mat4(rotation) * glm::scale(glm::mat4(1.0f), scale) * matrix;
		}

		glm::mat4 getMatrix() {
			glm::mat4 m = localMatrix();
			vkglTF::Node* p = parent;
			while (p) {
				m = p->localMatrix() * m;
				p = p->parent;
			}
			return m;
		}

		void update() {
			if (mesh) {
				glm::mat4 m = getMatrix();
				if (skin) {
					mesh->uniformBlock.matrix = m;
					// Update join matrices
					glm::mat4 inverseTransform = glm::inverse(m);
					size_t numJoints = std::min((uint32_t)skin->joints.size(), MAX_NUM_JOINTS);
					for (size_t i = 0; i < numJoints; i++) {
						vkglTF::Node* jointNode = skin->joints[i];
						glm::mat4 jointMat = jointNode->getMatrix() * skin->inverseBindMatrices[i];
						jointMat = inverseTransform * jointMat;
						mesh->uniformBlock.jointMatrix[i] = jointMat;
					}
					mesh->uniformBlock.jointcount = (float)numJoints;
					//memcpy(mesh->uniformBuffer.mapped, &mesh->uniformBlock, sizeof(mesh->uniformBlock));
				}
				else {
					//memcpy(mesh->uniformBuffer.mapped, &m, sizeof(glm::mat4));
				}
				mesh->update_ubo();
			}

			for (auto& child : children) {
				child->update();
			}
		}

		~Node() {
			if (mesh) {
				delete mesh;
			}
			for (auto& child : children) {
				delete child;
			}
		}
	};

	/*
		glTF animation channel
	*/
	struct AnimationChannel {
		enum PathType { TRANSLATION, ROTATION, SCALE };
		PathType path;
		Node* node;
		uint32_t samplerIndex;
	};

	/*
		glTF animation sampler
	*/
	struct AnimationSampler {
		enum InterpolationType { LINEAR, STEP, CUBICSPLINE };
		InterpolationType interpolation;
		std::vector<float> inputs;
		std::vector<glm::vec4> outputsVec4;
	};

	/*
		glTF animation
	*/
	struct Animation {
		std::string name;
		std::vector<AnimationSampler> samplers;
		std::vector<AnimationChannel> channels;
		float start = std::numeric_limits<float>::max();
		float end = std::numeric_limits<float>::min();
	};


	/*
		glTF model loading and rendering class
	*/
	struct Model {

		struct Vertex {
			glm::vec3 pos;
			glm::vec3 normal;
			glm::vec2 uv0;
			glm::vec2 uv1;
			glm::vec4 joint0;
			glm::vec4 weight0;
		};

		std::vector<VertexAttr> vertex_attr;
		unsigned int vao_id;
		BoneTextureMaterialPtr material;
		Transform3d transform;



		glm::mat4 aabb;

		std::vector<Node*> nodes;
		std::vector<Node*> linearNodes;

		std::vector<Skin*> skins;


		std::vector<Material> materials;
		std::vector<Animation> animations;
		std::vector<std::string> extensions;

		struct Dimensions {
			glm::vec3 min = glm::vec3(FLT_MAX);
			glm::vec3 max = glm::vec3(-FLT_MAX);
		} dimensions;

		Model() {
			TexturePtr t = make(Texture, "main/mesh/man2.png");
			material = make(BoneTextureMaterial, t);
		}


		void create_buffer(void *data,int size, int type, int hint) {
			unsigned int gpu_id;
			type = type;
			glGenBuffers(1, &gpu_id);
			glBindBuffer(type, gpu_id);
			glBufferData(type, size, data, hint);
		}
		void add_attr(VertexAttr& va) {
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
			case VAT_UV1:
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

		void init_vao(std::vector<uint32_t>& indexBuffer, std::vector<Vertex>& vertexBuffer) {
			add_default_attr(VAT_POSITION);
			add_default_attr(VAT_NORMAL);
			add_default_attr(VAT_UV0);
			add_default_attr(VAT_UV1);
			add_default_attr(VAT_BONEIDS);
			add_default_attr(VAT_WEIGHTS);

			glGenVertexArrays(1, &vao_id);
			glBindVertexArray(vao_id);

			create_buffer(vertexBuffer.data(), vertexBuffer.size()*sizeof(Vertex), GL_ARRAY_BUFFER, GL_STATIC_DRAW);

			int trip_size = 0;
			for (auto attr : vertex_attr) {
				trip_size += attr.size;
			}
			int offset = 0;
			for (auto attr : vertex_attr)
			{
				glEnableVertexAttribArray(attr.type);
				if (attr.data_type == GL_FLOAT)
				{
					glVertexAttribPointer((GLuint)attr.type, attr.component_num, attr.data_type, attr.need_normalized, trip_size, (const GLvoid*)offset);
				}
				else if (attr.data_type == GL_INT) {
					glVertexAttribIPointer((GLuint)attr.type, attr.component_num, attr.data_type, trip_size, (const GLvoid*)offset);
				}
				offset += attr.size;
			}

			create_buffer(indexBuffer.data(), indexBuffer.size()*sizeof(unsigned int), GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
			glBindVertexArray(0);

		}

		void destroy()
		{
			for (auto node : nodes) {
				delete node;
			}
			materials.resize(0);
			animations.resize(0);
			nodes.resize(0);
			linearNodes.resize(0);
			extensions.resize(0);
			skins.resize(0);
		};

		void loadNode(vkglTF::Node* parent, const tinygltf::Node& node, uint32_t nodeIndex, const tinygltf::Model& model, std::vector<uint32_t>& indexBuffer, std::vector<Vertex>& vertexBuffer, float globalscale)
		{
			vkglTF::Node* newNode = new Node{};
			newNode->index = nodeIndex;
			newNode->parent = parent;
			newNode->name = node.name;
			newNode->skinIndex = node.skin;
			newNode->matrix = glm::mat4(1.0f);

			// Generate local node matrix
			glm::vec3 translation = glm::vec3(0.0f);
			if (node.translation.size() == 3) {
				translation = glm::make_vec3(node.translation.data());
				newNode->translation = translation;
			}
			glm::mat4 rotation = glm::mat4(1.0f);
			if (node.rotation.size() == 4) {
				glm::quat q = glm::make_quat(node.rotation.data());
				newNode->rotation = glm::mat4(q);
			}
			glm::vec3 scale = glm::vec3(1.0f);
			if (node.scale.size() == 3) {
				scale = glm::make_vec3(node.scale.data());
				newNode->scale = scale;
			}
			if (node.matrix.size() == 16) {
				newNode->matrix = glm::make_mat4x4(node.matrix.data());
			};

			// Node with children
			if (node.children.size() > 0) {
				for (size_t i = 0; i < node.children.size(); i++) {
					loadNode(newNode, model.nodes[node.children[i]], node.children[i], model, indexBuffer, vertexBuffer, globalscale);
				}
			}

			// Node contains mesh data
			if (node.mesh > -1) {
				const tinygltf::Mesh mesh = model.meshes[node.mesh];
				Mesh* newMesh = new Mesh( newNode->matrix);
				for (size_t j = 0; j < mesh.primitives.size(); j++) {
					const tinygltf::Primitive& primitive = mesh.primitives[j];
					uint32_t indexStart = static_cast<uint32_t>(indexBuffer.size());
					uint32_t vertexStart = static_cast<uint32_t>(vertexBuffer.size());
					uint32_t indexCount = 0;
					uint32_t vertexCount = 0;
					glm::vec3 posMin{};
					glm::vec3 posMax{};
					bool hasSkin = false;
					bool hasIndices = primitive.indices > -1;
					// Vertices
					{
						const float* bufferPos = nullptr;
						const float* bufferNormals = nullptr;
						const float* bufferTexCoordSet0 = nullptr;
						const float* bufferTexCoordSet1 = nullptr;
						const uint16_t* bufferJoints = nullptr;
						const float* bufferWeights = nullptr;

						// Position attribute is required
						assert(primitive.attributes.find("POSITION") != primitive.attributes.end());

						const tinygltf::Accessor& posAccessor = model.accessors[primitive.attributes.find("POSITION")->second];
						const tinygltf::BufferView& posView = model.bufferViews[posAccessor.bufferView];
						bufferPos = reinterpret_cast<const float*>(&(model.buffers[posView.buffer].data[posAccessor.byteOffset + posView.byteOffset]));
						posMin = glm::vec3(posAccessor.minValues[0], posAccessor.minValues[1], posAccessor.minValues[2]);
						posMax = glm::vec3(posAccessor.maxValues[0], posAccessor.maxValues[1], posAccessor.maxValues[2]);
						vertexCount = static_cast<uint32_t>(posAccessor.count);

						if (primitive.attributes.find("NORMAL") != primitive.attributes.end()) {
							const tinygltf::Accessor& normAccessor = model.accessors[primitive.attributes.find("NORMAL")->second];
							const tinygltf::BufferView& normView = model.bufferViews[normAccessor.bufferView];
							bufferNormals = reinterpret_cast<const float*>(&(model.buffers[normView.buffer].data[normAccessor.byteOffset + normView.byteOffset]));
						}

						if (primitive.attributes.find("TEXCOORD_0") != primitive.attributes.end()) {
							const tinygltf::Accessor& uvAccessor = model.accessors[primitive.attributes.find("TEXCOORD_0")->second];
							const tinygltf::BufferView& uvView = model.bufferViews[uvAccessor.bufferView];
							bufferTexCoordSet0 = reinterpret_cast<const float*>(&(model.buffers[uvView.buffer].data[uvAccessor.byteOffset + uvView.byteOffset]));
						}
						if (primitive.attributes.find("TEXCOORD_1") != primitive.attributes.end()) {
							const tinygltf::Accessor& uvAccessor = model.accessors[primitive.attributes.find("TEXCOORD_1")->second];
							const tinygltf::BufferView& uvView = model.bufferViews[uvAccessor.bufferView];
							bufferTexCoordSet1 = reinterpret_cast<const float*>(&(model.buffers[uvView.buffer].data[uvAccessor.byteOffset + uvView.byteOffset]));
						}

						// Skinning
						// Joints
						if (primitive.attributes.find("JOINTS_0") != primitive.attributes.end()) {
							const tinygltf::Accessor& jointAccessor = model.accessors[primitive.attributes.find("JOINTS_0")->second];
							const tinygltf::BufferView& jointView = model.bufferViews[jointAccessor.bufferView];
							bufferJoints = reinterpret_cast<const uint16_t*>(&(model.buffers[jointView.buffer].data[jointAccessor.byteOffset + jointView.byteOffset]));
						}

						if (primitive.attributes.find("WEIGHTS_0") != primitive.attributes.end()) {
							const tinygltf::Accessor& uvAccessor = model.accessors[primitive.attributes.find("WEIGHTS_0")->second];
							const tinygltf::BufferView& uvView = model.bufferViews[uvAccessor.bufferView];
							bufferWeights = reinterpret_cast<const float*>(&(model.buffers[uvView.buffer].data[uvAccessor.byteOffset + uvView.byteOffset]));
						}

						hasSkin = (bufferJoints && bufferWeights);

						for (size_t v = 0; v < posAccessor.count; v++) {
							Vertex vert{};
							vert.pos = glm::vec4(glm::make_vec3(&bufferPos[v * 3]), 1.0f);
							vert.normal = glm::normalize(glm::vec3(bufferNormals ? glm::make_vec3(&bufferNormals[v * 3]) : glm::vec3(0.0f)));
							vert.uv0 = bufferTexCoordSet0 ? glm::make_vec2(&bufferTexCoordSet0[v * 2]) : glm::vec3(0.0f);
							vert.uv1 = bufferTexCoordSet1 ? glm::make_vec2(&bufferTexCoordSet1[v * 2]) : glm::vec3(0.0f);

							vert.joint0 = hasSkin ? glm::vec4(glm::make_vec4(&bufferJoints[v * 4])) : glm::vec4(0.0f);
							vert.weight0 = hasSkin ? glm::make_vec4(&bufferWeights[v * 4]) : glm::vec4(0.0f);
							vertexBuffer.push_back(vert);
						}
					}
					// Indices
					if (hasIndices)
					{
						const tinygltf::Accessor& accessor = model.accessors[primitive.indices > -1 ? primitive.indices : 0];
						const tinygltf::BufferView& bufferView = model.bufferViews[accessor.bufferView];
						const tinygltf::Buffer& buffer = model.buffers[bufferView.buffer];

						indexCount = static_cast<uint32_t>(accessor.count);
						const void* dataPtr = &(buffer.data[accessor.byteOffset + bufferView.byteOffset]);

						switch (accessor.componentType) {
						case TINYGLTF_PARAMETER_TYPE_UNSIGNED_INT: {
							const uint32_t* buf = static_cast<const uint32_t*>(dataPtr);
							for (size_t index = 0; index < accessor.count; index++) {
								indexBuffer.push_back(buf[index] + vertexStart);
							}
							break;
						}
						case TINYGLTF_PARAMETER_TYPE_UNSIGNED_SHORT: {
							const uint16_t* buf = static_cast<const uint16_t*>(dataPtr);
							for (size_t index = 0; index < accessor.count; index++) {
								indexBuffer.push_back(buf[index] + vertexStart);
							}
							break;
						}
						case TINYGLTF_PARAMETER_TYPE_UNSIGNED_BYTE: {
							const uint8_t* buf = static_cast<const uint8_t*>(dataPtr);
							for (size_t index = 0; index < accessor.count; index++) {
								indexBuffer.push_back(buf[index] + vertexStart);
							}
							break;
						}
						default:
							std::cout << "Index component type " << accessor.componentType << " not supported!" << std::endl;
							return;
						}
					}
					Primitive* newPrimitive = new Primitive(primitive.mode, indexStart, indexCount, vertexCount);
					newPrimitive->setBoundingBox(posMin, posMax);
					newMesh->primitives.push_back(newPrimitive);
				}
				// Mesh BB from BBs of primitives
				for (auto p : newMesh->primitives) {
					if (p->bb.valid && !newMesh->bb.valid) {
						newMesh->bb = p->bb;
						newMesh->bb.valid = true;
					}
					newMesh->bb.min = glm::min(newMesh->bb.min, p->bb.min);
					newMesh->bb.max = glm::max(newMesh->bb.max, p->bb.max);
				}
				newNode->mesh = newMesh;
			}
			if (parent) {
				parent->children.push_back(newNode);
			}
			else {
				nodes.push_back(newNode);
			}
			linearNodes.push_back(newNode);
		}

		void loadSkins(tinygltf::Model& gltfModel)
		{
			for (tinygltf::Skin& source : gltfModel.skins) {
				Skin* newSkin = new Skin{};
				newSkin->name = source.name;

				// Find skeleton root node
				if (source.skeleton > -1) {
					newSkin->skeletonRoot = nodeFromIndex(source.skeleton);
				}

				// Find joint nodes
				for (int jointIndex : source.joints) {
					Node* node = nodeFromIndex(jointIndex);
					if (node) {
						newSkin->joints.push_back(nodeFromIndex(jointIndex));
					}
				}

				// Get inverse bind matrices from buffer
				if (source.inverseBindMatrices > -1) {
					const tinygltf::Accessor& accessor = gltfModel.accessors[source.inverseBindMatrices];
					const tinygltf::BufferView& bufferView = gltfModel.bufferViews[accessor.bufferView];
					const tinygltf::Buffer& buffer = gltfModel.buffers[bufferView.buffer];
					newSkin->inverseBindMatrices.resize(accessor.count);
					memcpy(newSkin->inverseBindMatrices.data(), &buffer.data[accessor.byteOffset + bufferView.byteOffset], accessor.count * sizeof(glm::mat4));
				}

				skins.push_back(newSkin);
			}
		}


		void loadAnimations(tinygltf::Model& gltfModel)
		{
			for (tinygltf::Animation& anim : gltfModel.animations) {
				vkglTF::Animation animation{};
				animation.name = anim.name;
				if (anim.name.empty()) {
					animation.name = std::to_string(animations.size());
				}

				// Samplers
				for (auto& samp : anim.samplers) {
					vkglTF::AnimationSampler sampler{};

					if (samp.interpolation == "LINEAR") {
						sampler.interpolation = AnimationSampler::InterpolationType::LINEAR;
					}
					if (samp.interpolation == "STEP") {
						sampler.interpolation = AnimationSampler::InterpolationType::STEP;
					}
					if (samp.interpolation == "CUBICSPLINE") {
						sampler.interpolation = AnimationSampler::InterpolationType::CUBICSPLINE;
					}

					// Read sampler input time values
					{
						const tinygltf::Accessor& accessor = gltfModel.accessors[samp.input];
						const tinygltf::BufferView& bufferView = gltfModel.bufferViews[accessor.bufferView];
						const tinygltf::Buffer& buffer = gltfModel.buffers[bufferView.buffer];

						assert(accessor.componentType == TINYGLTF_COMPONENT_TYPE_FLOAT);

						const void* dataPtr = &buffer.data[accessor.byteOffset + bufferView.byteOffset];
						const float* buf = static_cast<const float*>(dataPtr);
						for (size_t index = 0; index < accessor.count; index++) {
							sampler.inputs.push_back(buf[index]);
						}

						for (auto input : sampler.inputs) {
							if (input < animation.start) {
								animation.start = input;
							};
							if (input > animation.end) {
								animation.end = input;
							}
						}
					}

					// Read sampler output T/R/S values 
					{
						const tinygltf::Accessor& accessor = gltfModel.accessors[samp.output];
						const tinygltf::BufferView& bufferView = gltfModel.bufferViews[accessor.bufferView];
						const tinygltf::Buffer& buffer = gltfModel.buffers[bufferView.buffer];

						assert(accessor.componentType == TINYGLTF_COMPONENT_TYPE_FLOAT);

						const void* dataPtr = &buffer.data[accessor.byteOffset + bufferView.byteOffset];

						switch (accessor.type) {
						case TINYGLTF_TYPE_VEC3: {
							const glm::vec3* buf = static_cast<const glm::vec3*>(dataPtr);
							for (size_t index = 0; index < accessor.count; index++) {
								sampler.outputsVec4.push_back(glm::vec4(buf[index], 0.0f));
							}
							break;
						}
						case TINYGLTF_TYPE_VEC4: {
							const glm::vec4* buf = static_cast<const glm::vec4*>(dataPtr);
							for (size_t index = 0; index < accessor.count; index++) {
								sampler.outputsVec4.push_back(buf[index]);
							}
							break;
						}
						default: {
							std::cout << "unknown type" << std::endl;
							break;
						}
						}
					}

					animation.samplers.push_back(sampler);
				}

				// Channels
				for (auto& source : anim.channels) {
					vkglTF::AnimationChannel channel{};

					if (source.target_path == "rotation") {
						channel.path = AnimationChannel::PathType::ROTATION;
					}
					if (source.target_path == "translation") {
						channel.path = AnimationChannel::PathType::TRANSLATION;
					}
					if (source.target_path == "scale") {
						channel.path = AnimationChannel::PathType::SCALE;
					}
					if (source.target_path == "weights") {
						std::cout << "weights not yet supported, skipping channel" << std::endl;
						continue;
					}
					channel.samplerIndex = source.sampler;
					channel.node = nodeFromIndex(source.target_node);
					if (!channel.node) {
						continue;
					}

					animation.channels.push_back(channel);
				}

				animations.push_back(animation);
			}
		}

		void loadFromFile(std::string filename,  float scale = 1.0f)
		{
			tinygltf::Model gltfModel;
			tinygltf::TinyGLTF gltfContext;
			std::string error;
			std::string warning;



			bool binary = false;
			size_t extpos = filename.rfind('.', filename.length());
			if (extpos != std::string::npos) {
				binary = (filename.substr(extpos + 1, filename.length() - extpos) == "glb");
			}

			bool fileLoaded = binary ? gltfContext.LoadBinaryFromFile(&gltfModel, &error, &warning, filename.c_str()) : gltfContext.LoadASCIIFromFile(&gltfModel, &error, &warning, filename.c_str());

			std::vector<uint32_t> indexBuffer;
			std::vector<Vertex> vertexBuffer;

			if (fileLoaded) {
	
				// TODO: scene handling with no default scene
				const tinygltf::Scene& scene = gltfModel.scenes[gltfModel.defaultScene > -1 ? gltfModel.defaultScene : 0];
				for (size_t i = 0; i < scene.nodes.size(); i++) {
					const tinygltf::Node node = gltfModel.nodes[scene.nodes[i]];
					loadNode(nullptr, node, scene.nodes[i], gltfModel, indexBuffer, vertexBuffer, scale);
				}
				if (gltfModel.animations.size() > 0) {
					loadAnimations(gltfModel);
				}
				loadSkins(gltfModel);

				for (auto node : linearNodes) {
					// Assign skins
					if (node->skinIndex > -1) {
						node->skin = skins[node->skinIndex];
					}
					// Initial pose
					if (node->mesh) {
						node->update();
					}
				}
			}
			else {
				// TODO: throw
				std::cerr << "Could not load gltf file: " << error << std::endl;
				return;
			}

			extensions = gltfModel.extensionsUsed;

			size_t vertexBufferSize = vertexBuffer.size() * sizeof(Vertex);
			size_t indexBufferSize = indexBuffer.size() * sizeof(uint32_t);
			//indices.count = static_cast<uint32_t>(indexBuffer.size());

			init_vao(indexBuffer,vertexBuffer);

			assert(vertexBufferSize > 0);

			//struct StagingBuffer {
			//	VkBuffer buffer;
			//	VkDeviceMemory memory;
			//} vertexStaging, indexStaging;

			//// Create staging buffers
			//// Vertex data
			//VK_CHECK_RESULT(device->createBuffer(
			//	VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
			//	VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
			//	vertexBufferSize,
			//	&vertexStaging.buffer,
			//	&vertexStaging.memory,
			//	vertexBuffer.data()));
			//// Index data
			//if (indexBufferSize > 0) {
			//	VK_CHECK_RESULT(device->createBuffer(
			//		VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
			//		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
			//		indexBufferSize,
			//		&indexStaging.buffer,
			//		&indexStaging.memory,
			//		indexBuffer.data()));
			//}

			//// Create device local buffers
			//// Vertex buffer
			//VK_CHECK_RESULT(device->createBuffer(
			//	VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
			//	VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
			//	vertexBufferSize,
			//	&vertices.buffer,
			//	&vertices.memory));
			//// Index buffer
			//if (indexBufferSize > 0) {
			//	VK_CHECK_RESULT(device->createBuffer(
			//		VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT,
			//		VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
			//		indexBufferSize,
			//		&indices.buffer,
			//		&indices.memory));
			//}

			//// Copy from staging buffers
			//VkCommandBuffer copyCmd = device->createCommandBuffer(VK_COMMAND_BUFFER_LEVEL_PRIMARY, true);

			//VkBufferCopy copyRegion = {};

			//copyRegion.size = vertexBufferSize;
			//vkCmdCopyBuffer(copyCmd, vertexStaging.buffer, vertices.buffer, 1, &copyRegion);

			//if (indexBufferSize > 0) {
			//	copyRegion.size = indexBufferSize;
			//	vkCmdCopyBuffer(copyCmd, indexStaging.buffer, indices.buffer, 1, &copyRegion);
			//}

			//device->flushCommandBuffer(copyCmd, transferQueue, true);

			//vkDestroyBuffer(device->logicalDevice, vertexStaging.buffer, nullptr);
			//vkFreeMemory(device->logicalDevice, vertexStaging.memory, nullptr);
			//if (indexBufferSize > 0) {
			//	vkDestroyBuffer(device->logicalDevice, indexStaging.buffer, nullptr);
			//	vkFreeMemory(device->logicalDevice, indexStaging.memory, nullptr);
			//}

			getSceneDimensions();
		}

		void drawNode(Node* node)
		{
			if (node->mesh) {
				//for (Primitive* primitive : node->mesh->primitives) {
				//	vkCmdDrawIndexed(commandBuffer, primitive->indexCount, 1, primitive->firstIndex, 0, 0);
				//}
				node->mesh->render();
			}
			for (auto& child : node->children) {
				drawNode(child);
			}
		}

		void draw(CameraPtr camera)
		{
			static float time = 0.0f;
			time += 0.02;
			if (time>=2.0)
			{
				time = 0.0;
			}

			updateAnimation(0,time);
			for (auto& node : nodes) {
				node->update();
			}

			material->bind();
			material->mvp(transform.matrix(), camera->get_v(), camera->get_p());
			glBindVertexArray(vao_id);
			for (auto& node : nodes) {
				drawNode(node);
			}
			glBindVertexArray(0);
		}


		void calculateBoundingBox(Node* node, Node* parent) {
			BoundingBox parentBvh = parent ? parent->bvh : BoundingBox(dimensions.min, dimensions.max);

			if (node->mesh) {
				if (node->mesh->bb.valid) {
					node->aabb = node->mesh->bb.getAABB(node->getMatrix());
					if (node->children.size() == 0) {
						node->bvh.min = node->aabb.min;
						node->bvh.max = node->aabb.max;
						node->bvh.valid = true;
					}
				}
			}

			parentBvh.min = glm::min(parentBvh.min, node->bvh.min);
			parentBvh.max = glm::min(parentBvh.max, node->bvh.max);

			for (auto& child : node->children) {
				calculateBoundingBox(child, node);
			}
		}

		void getSceneDimensions()
		{
			// Calculate binary volume hierarchy for all nodes in the scene
			for (auto node : linearNodes) {
				calculateBoundingBox(node, nullptr);
			}

			dimensions.min = glm::vec3(FLT_MAX);
			dimensions.max = glm::vec3(-FLT_MAX);

			for (auto node : linearNodes) {
				if (node->bvh.valid) {
					dimensions.min = glm::min(dimensions.min, node->bvh.min);
					dimensions.max = glm::max(dimensions.max, node->bvh.max);
				}
			}

			// Calculate scene aabb
			aabb = glm::scale(glm::mat4(1.0f), glm::vec3(dimensions.max[0] - dimensions.min[0], dimensions.max[1] - dimensions.min[1], dimensions.max[2] - dimensions.min[2]));
			aabb[3][0] = dimensions.min[0];
			aabb[3][1] = dimensions.min[1];
			aabb[3][2] = dimensions.min[2];
		}

		void updateAnimation(uint32_t index, float time)
		{
			if (index > static_cast<uint32_t>(animations.size()) - 1) {
				std::cout << "No animation with index " << index << std::endl;
				return;
			}
			Animation& animation = animations[index];

			bool updated = false;
			for (auto& channel : animation.channels) {
				vkglTF::AnimationSampler& sampler = animation.samplers[channel.samplerIndex];
				if (sampler.inputs.size() > sampler.outputsVec4.size()) {
					continue;
				}

				for (size_t i = 0; i < sampler.inputs.size() - 1; i++) {
					if ((time >= sampler.inputs[i]) && (time <= sampler.inputs[i + 1])) {
						float u = std::max(0.0f, time - sampler.inputs[i]) / (sampler.inputs[i + 1] - sampler.inputs[i]);
						if (u <= 1.0f) {
							switch (channel.path) {
							case vkglTF::AnimationChannel::PathType::TRANSLATION: {
								glm::vec4 trans = glm::mix(sampler.outputsVec4[i], sampler.outputsVec4[i + 1], u);
								channel.node->translation = glm::vec3(trans);
								break;
							}
							case vkglTF::AnimationChannel::PathType::SCALE: {
								glm::vec4 trans = glm::mix(sampler.outputsVec4[i], sampler.outputsVec4[i + 1], u);
								channel.node->scale = glm::vec3(trans);
								break;
							}
							case vkglTF::AnimationChannel::PathType::ROTATION: {
								glm::quat q1;
								q1.x = sampler.outputsVec4[i].x;
								q1.y = sampler.outputsVec4[i].y;
								q1.z = sampler.outputsVec4[i].z;
								q1.w = sampler.outputsVec4[i].w;
								glm::quat q2;
								q2.x = sampler.outputsVec4[i + 1].x;
								q2.y = sampler.outputsVec4[i + 1].y;
								q2.z = sampler.outputsVec4[i + 1].z;
								q2.w = sampler.outputsVec4[i + 1].w;
								channel.node->rotation = glm::normalize(glm::slerp(q1, q2, u));
								break;
							}
							}
							updated = true;
						}
					}
				}
			}
			if (updated) {
				for (auto& node : nodes) {
					node->update();
				}
			}
		}

		/*
			Helper functions
		*/
		Node* findNode(Node* parent, uint32_t index) {
			Node* nodeFound = nullptr;
			if (parent->index == index) {
				return parent;
			}
			for (auto& child : parent->children) {
				nodeFound = findNode(child, index);
				if (nodeFound) {
					break;
				}
			}
			return nodeFound;
		}

		Node* nodeFromIndex(uint32_t index) {
			Node* nodeFound = nullptr;
			for (auto& node : nodes) {
				nodeFound = findNode(node, index);
				if (nodeFound) {
					break;
				}
			}
			return nodeFound;
		}
	};
}
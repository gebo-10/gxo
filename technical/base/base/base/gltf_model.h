#ifndef GLTF_MODEL_H
#define GLTF_MODEL_H
#include "core_base.h"
#include "model.h"

//#define TINYGLTF_IMPLEMENTATION
//
//#define STB_IMAGE_WRITE_IMPLEMENTATION
#define TINYGLTF_NOEXCEPTION
#define JSON_NOEXCEPTION
#include "tiny_gltf.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))
#define MAX_BONE_NUM 50
#include "bone_material.h"




/*
		glTF skin
	*/
struct Node;
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
	Node* parent=nullptr;
	uint32_t index;
	std::vector<Node*> children;
	glm::mat4 matrix;
	std::string name;
	bool mesh=false;
	Skin* skin;
	int32_t skinIndex = -1;
	glm::vec3 translation{};
	glm::vec3 scale{ 1.0f };
	glm::quat rotation{};

	mat4 *bones;

	glm::mat4 localMatrix() {
		return glm::translate(glm::mat4(1.0f), translation) * glm::mat4(rotation) * glm::scale(glm::mat4(1.0f), scale) * matrix;
	}

	glm::mat4 getMatrix() {
		glm::mat4 m = localMatrix();
		Node* p = parent;
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
				//mesh->uniformBlock.matrix = m;
				// Update join matrices
				glm::mat4 inverseTransform = glm::inverse(m);
				size_t numJoints = min((int)skin->joints.size(), MAX_BONE_NUM);
				for (size_t i = 0; i < numJoints; i++) {
					Node* jointNode = skin->joints[i];
					glm::mat4 jointMat = jointNode->getMatrix() * skin->inverseBindMatrices[i];
					jointMat = inverseTransform * jointMat;
					//mesh->uniformBlock.jointMatrix[i] = jointMat;
					bones[i]= jointMat;
				}
			}
		}

		for (auto& child : children) {
			child->update();
		}
	}

	~Node() {

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


class GltfModel :public Model
{
public:
	tinygltf::TinyGLTF tiny_gltf;
	tinygltf::Model gltf_model;

	GPUID gpu_id=-1;



	BoneNode* bone_tree=nullptr;
	mat4 offset_matrix[MAX_BONE_NUM];
	mat4 bones[MAX_BONE_NUM];

	Node* root=nullptr;
	std::vector<Skin*> skins;
	std::vector<Node*> linearNodes;

	std::vector<Animation> animations;


	BoneTextureMaterialPtr material;
	GltfModel(string_view filename);
	~GltfModel()
	{

	}

	virtual void render(CameraPtr camera) {
		material->bind();
		material->mvp(transform.matrix(), camera->get_v(), camera->get_p());
		//if (mesh->bone_num > 0)
		//{
		//	material->set_bone(&mesh->bones[0][0][0], MAX_BONE_NUM * 16);
		//}
		//mesh->bind();
		//glDrawElements(mesh->primitive, mesh->element_size, GL_UNSIGNED_SHORT, 0);

		if (root==nullptr)
		{

			for (int i = 0; i < 50; i++)
			{
				bones[i] = mat4(0.0);
			}


			const tinygltf::Scene& scene = gltf_model.scenes[gltf_model.defaultScene];
			loadNode(root, gltf_model.nodes[scene.nodes[0]] , scene.nodes[0], gltf_model, 1.0);

			loadAnimations(gltf_model);
			loadSkins(gltf_model);

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
		static float time = 0.0f;
		time+=0.01;
		float i;
		time = modf(time, &i);
		updateAnimation(0, time*2.0);
		//root->update();
		//for (int i = 0; i < 19; i++)
		//{
		//	bones[i] = mat4(1.0);
		//}
		//update_bone();
		material->set_bone(&bones[0][0][0], MAX_BONE_NUM);
		drawModel(gpu_id, gltf_model);
	}

	void update_bone() {
		if (bone_tree==nullptr)
		{
			build_tree();
		}

		for (int i=0;i<50;i++)
		{
			bones[i] = mat4(1.0);
		}

		update_bone_node(bone_tree,mat4(1.0));

	}

	void update_bone_node(BoneNode * node, mat4 parent_mat) {
		node->final_matrix = parent_mat * node->node_transform;
		if (node->bone_id>=0)
		{
			bones[node->bone_id] = node->final_matrix*node->offset_matrix;

		}
		for (auto child:node->children)
		{
			update_bone_node(child, node->final_matrix);
		}

	}


	void build_tree() {

		//offet matrix
		auto skia = gltf_model.skins[0];
		auto acc = gltf_model.accessors[skia.inverseBindMatrices];

		auto buffer_view = gltf_model.bufferViews[acc.bufferView];
		tinygltf::Buffer buffer = gltf_model.buffers[buffer_view.buffer];
		memcpy(&offset_matrix[0][0][0], buffer.data.data()+ buffer_view.byteOffset, buffer_view.byteLength);


		const tinygltf::Scene& scene = gltf_model.scenes[gltf_model.defaultScene];
		BoneNode* scene_root = new BoneNode();
		scene_root->node_transform = mat4(1.0);
		scene_root->bone_id = -1;

		for (size_t i = 0; i < scene.nodes.size(); ++i) {
			auto bone_node=build_node(gltf_model.nodes[scene.nodes[i]],i);
			scene_root->children.push_back(bone_node);
		}

		bone_tree = scene_root;
	}

	BoneNode* build_node(tinygltf::Node tiny_node,int node_index) {

		BoneNode* bone_node = new BoneNode();
		bone_node->node_transform = transform_cast(tiny_node.scale,tiny_node.rotation,tiny_node.translation);
		bone_node->bone_id = find_bone_index(node_index);
		
		if (bone_node->bone_id >=0)
		{
			bone_node->offset_matrix = offset_matrix[bone_node->bone_id];
		}
		


		for (size_t i = 0; i < tiny_node.children.size(); ++i) {
			auto node = build_node(gltf_model.nodes[tiny_node.children[i]],i);
			bone_node->children.push_back(node);
		}

		return bone_node;
	}

	int find_bone_index(int node_index) {
		for (int i=0;i<gltf_model.skins[0].joints.size();i++)
		{
			if (i==node_index)
			{
				return i;
			}
		}
		error("find_bone_index NULL :node_index={}", node_index);
		return -1;
	}


	mat4 mat_cast(std::vector<double> matrix) {
		if (matrix.size()==0)
		{
			return mat4(1.0);
		}
		return glm::make_mat4(matrix.data());
	}

	vec3 vec3_cast(std::vector<double> vec) {
		if (vec.size()==0)
		{
			return vec3(0);
		}
		return vec3(vec[0],vec[1],vec[2]);
	}

	quat quat_cast(std::vector<double> vec) {
		if (vec.size() == 0)
		{
			return quat(1.0,0,0,0);
		}
		return glm::make_quat(vec.data());
	}

	mat4 transform_cast(std::vector<double> scale, std::vector<double> rotate, std::vector<double> t) {
		mat4 identity(1.f);

		if (scale.size()==0)
		{
			scale.push_back(1);
			scale.push_back(1);
			scale.push_back(1);
		}



		mat4 matrix = translate(identity, vec3_cast(t)) * mat4(quat_cast(rotate)) * glm::scale(identity, vec3_cast(scale));
		return matrix;
	}


	bool loadModel( const char* filename);


	std::map<int, GLuint> bindMesh(std::map<int, GLuint> vbos,
		tinygltf::Model& model, tinygltf::Mesh& mesh) {
		for (size_t i = 0; i < model.bufferViews.size(); ++i) {
			const tinygltf::BufferView& bufferView = model.bufferViews[i];
			if (bufferView.target == 0) {  // TODO impl drawarrays
				std::cout << "WARN: bufferView.target is zero" << std::endl;
				continue; 
			}

			tinygltf::Buffer buffer = model.buffers[bufferView.buffer];
			std::cout << "bufferview.target " << bufferView.target << std::endl;

			GLuint vbo;
			glGenBuffers(1, &vbo);
			vbos[i] = vbo;
			glBindBuffer(bufferView.target, vbo);

			std::cout << "buffer.data.size = " << buffer.data.size()
				<< ", bufferview.byteOffset = " << bufferView.byteOffset
				<< std::endl;


			if (i== 1)
			{
				const uint16_t* bufferJoints = nullptr;

				float* new_buf = new float[3273 * 4];
				const tinygltf::Accessor& jointAccessor = model.accessors[3];
				const tinygltf::BufferView& jointView = model.bufferViews[jointAccessor.bufferView];
				bufferJoints = reinterpret_cast<const uint16_t*>(&buffer.data.at(0) + bufferView.byteOffset);
				for (size_t v = 0; v < 3273 * 4; v++) {
					new_buf[v] = static_cast<float>(bufferJoints[v]);
					//std::cout << new_buf[v] << " ";
					if (new_buf[v] <0 || new_buf[v]>19)
					{
						error("ddddddddddddddddd");
					}
				}
			
				glBufferData(bufferView.target, 3273 * 4*4, new_buf, GL_STATIC_DRAW);
			}
			else {
				glBufferData(bufferView.target, bufferView.byteLength,
					&buffer.data.at(0) + bufferView.byteOffset, GL_STATIC_DRAW);
			}
		}

		for (size_t i = 0; i < mesh.primitives.size(); ++i) {
			tinygltf::Primitive primitive = mesh.primitives[i];
			tinygltf::Accessor indexAccessor = model.accessors[primitive.indices];

			for (auto& attrib : primitive.attributes) {
				tinygltf::Accessor accessor = model.accessors[attrib.second];
				int byteStride =
					accessor.ByteStride(model.bufferViews[accessor.bufferView]);
				glBindBuffer(GL_ARRAY_BUFFER, vbos[accessor.bufferView]);

				int size = 1;
				if (accessor.type != TINYGLTF_TYPE_SCALAR) {
					size = accessor.type;
				}

				int vaa = -1;
				if (attrib.first.compare("POSITION") == 0) vaa = 0;
				if (attrib.first.compare("NORMAL") == 0) vaa = 1;
				if (attrib.first.compare("TEXCOORD_0") == 0) vaa = 2;
				if (attrib.first.compare("JOINTS_0") == 0) vaa = 3;
				if (attrib.first.compare("WEIGHTS_0") == 0) vaa = 4;
				
				if (vaa == 3)
				{
					glEnableVertexAttribArray(vaa);
					glVertexAttribPointer(vaa, 4, GL_FLOAT, GL_FALSE,0, 0);
				}
				else if (vaa > -1) {
					glEnableVertexAttribArray(vaa);
					glVertexAttribPointer(vaa, size, accessor.componentType,
						accessor.normalized ? GL_TRUE : GL_FALSE,
						byteStride, BUFFER_OFFSET(accessor.byteOffset));
				}
				else
					std::cout << "vaa missing: " << attrib.first << std::endl;
			}

			//GLuint texid;
			//glGenTextures(1, &texid);

			//tinygltf::Texture& tex = model.textures[0];
			//tinygltf::Image& image = model.images[tex.source];

			//glBindTexture(GL_TEXTURE_2D, texid);
			//glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			//glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			//GLenum format = GL_RGBA;

			//if (image.component == 1) {
			//	format = GL_RED;
			//}
			//else if (image.component == 2) {
			//	format = GL_RG;
			//}
			//else if (image.component == 3) {
			//	format = GL_RGB;
			//}
			//else {
			//	// ???
			//}

			//GLenum type = GL_UNSIGNED_BYTE;
			//if (image.bits == 8) {
			//	// ok
			//}
			//else if (image.bits == 16) {
			//	type = GL_UNSIGNED_SHORT;
			//}
			//else {
			//	// ???
			//}

			//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width, image.height, 0,
			//	format, type, &image.image.at(0));
		}

		return vbos;
	}

	// bind models
	void bindModelNodes(std::map<int, GLuint> vbos, tinygltf::Model& model,
		tinygltf::Node& node) {
		if (node.mesh >=0)
		{
			bindMesh(vbos, model, model.meshes[node.mesh]);
		}
		
		for (size_t i = 0; i < node.children.size(); i++) {
			bindModelNodes(vbos, model, model.nodes[node.children[i]]);
		}
	}
	GLuint bindModel(tinygltf::Model& model) {
		std::map<int, GLuint> vbos;
		GLuint vao;
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		const tinygltf::Scene& scene = model.scenes[model.defaultScene];
		for (size_t i = 0; i < scene.nodes.size(); ++i) {
			bindModelNodes(vbos, model, model.nodes[scene.nodes[i]]);
		}

		glBindVertexArray(0);
		// cleanup vbos
		for (size_t i = 0; i < vbos.size(); ++i) {
			glDeleteBuffers(1, &vbos[i]);
		}

		return vao;
	}



	void drawMesh(tinygltf::Model& model, tinygltf::Mesh& mesh) {
		for (size_t i = 0; i < mesh.primitives.size(); ++i) {
			tinygltf::Primitive primitive = mesh.primitives[i];
			tinygltf::Accessor indexAccessor = model.accessors[primitive.indices];

			glDrawElements(primitive.mode, indexAccessor.count,
				indexAccessor.componentType,
				BUFFER_OFFSET(indexAccessor.byteOffset));
		}
	}

	// recursively draw node and children nodes of model
	void drawModelNodes(tinygltf::Model& model, tinygltf::Node& node) {
		if (node.mesh >=0)
		{
			drawMesh(model, model.meshes[node.mesh]);
		}
		
		for (size_t i = 0; i < node.children.size(); i++) {
			drawModelNodes(model, model.nodes[node.children[i]]);
		}
	}
	void drawModel(GLuint vao, tinygltf::Model& model) {
		glBindVertexArray(vao);

		const tinygltf::Scene& scene = model.scenes[model.defaultScene];
		for (size_t i = 0; i < scene.nodes.size(); ++i) {
			drawModelNodes(model, model.nodes[scene.nodes[i]]);
		}

		glBindVertexArray(0);
	}

	void dbgModel(tinygltf::Model& model) {
		for (auto& mesh : model.meshes) {
			std::cout << "mesh : " << mesh.name << std::endl;
			for (auto& primitive : mesh.primitives) {
				const tinygltf::Accessor& indexAccessor =
					model.accessors[primitive.indices];

				std::cout << "indexaccessor: count " << indexAccessor.count << ", type "
					<< indexAccessor.componentType << std::endl;

				tinygltf::Material& mat = model.materials[primitive.material];
				for (auto& mats : mat.values) {
					std::cout << "mat : " << mats.first.c_str() << std::endl;
				}

				for (auto& image : model.images) {
					std::cout << "image name : " << image.uri << std::endl;
					std::cout << "  size : " << image.image.size() << std::endl;
					std::cout << "  w/h : " << image.width << "/" << image.height
						<< std::endl;
				}

				std::cout << "indices : " << primitive.indices << std::endl;
				std::cout << "mode     : "
					<< "(" << primitive.mode << ")" << std::endl;

				for (auto& attrib : primitive.attributes) {
					std::cout << "attribute : " << attrib.first.c_str() << std::endl;
				}
			}
		}
	}





	void loadNode(Node* parent, const tinygltf::Node& node, uint32_t nodeIndex, const tinygltf::Model& model,  float globalscale)
	{
		Node* newNode = new Node{};

		newNode->bones = bones;

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
				loadNode(newNode, model.nodes[node.children[i]], node.children[i], model, globalscale);
			}
		}

		// Node contains mesh data
		if (node.mesh > -1) {
			newNode->mesh = true;
		}
		if (parent) {
			parent->children.push_back(newNode);
		}
		else {
			root = newNode;
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
		return findNode(root, index);
	}




	void loadAnimations(tinygltf::Model& gltfModel)
	{
		for (tinygltf::Animation& anim : gltfModel.animations) {
			Animation animation{};
			animation.name = anim.name;
			if (anim.name.empty()) {
				animation.name = std::to_string(animations.size());
			}

			// Samplers
			for (auto& samp : anim.samplers) {
				AnimationSampler sampler{};

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
				AnimationChannel channel{};

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






	void updateAnimation(uint32_t index, float time)
	{
		if (index > static_cast<uint32_t>(animations.size()) - 1) {
			std::cout << "No animation with index " << index << std::endl;
			return;
		}
		Animation& animation = animations[index];

		bool updated = false;
		for (auto& channel : animation.channels) {
			AnimationSampler& sampler = animation.samplers[channel.samplerIndex];
			if (sampler.inputs.size() > sampler.outputsVec4.size()) {
				continue;
			}

			for (size_t i = 0; i < sampler.inputs.size() - 1; i++) {
				if ((time >= sampler.inputs[i]) && (time <= sampler.inputs[i + 1])) {
					float u = std::max(0.0f, time - sampler.inputs[i]) / (sampler.inputs[i + 1] - sampler.inputs[i]);
					if (u <= 1.0f) {
						switch (channel.path) {
						case AnimationChannel::PathType::TRANSLATION: {
							glm::vec4 trans = glm::mix(sampler.outputsVec4[i], sampler.outputsVec4[i + 1], u);
							channel.node->translation = glm::vec3(trans);
							//auto tmp=glm::vec3(trans);
							// channel.node->translation = vec3(tmp.x, tmp.z, tmp.y);
							break;
						}
						case AnimationChannel::PathType::SCALE: {
							glm::vec4 trans = glm::mix(sampler.outputsVec4[i], sampler.outputsVec4[i + 1], u);
							channel.node->scale = glm::vec3(trans);
							break;
						}
						case AnimationChannel::PathType::ROTATION: {
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
			//for (auto& node : nodes) {
			//	node->update();
			//}
			root->update();
		}
	}


};
REG(GltfModel)


#endif
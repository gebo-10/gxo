#ifndef MODEL_H
#define MODEL_H
#include "core_base.h"
#include "material.h"
#include "mesh.h"
#include "camera.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
public:
	MeshPtr mesh;
	MaterialPtr material;
	Transform3d transform;
	Model(MeshPtr mesh, MaterialPtr material)
	{
		this->mesh = mesh;
		this->material = material;
	}

	Model(string_view filename) {
		import(string(filename));
	}

	~Model()
	{
	}

	void set_mesh(MeshPtr mesh) {
		this->mesh = mesh;
	}

	void set_material(MaterialPtr material) {
		this->material = material;
	}

	virtual void render( CameraPtr camera) {
		material->bind();
		material->mvp(transform.matrix(), camera->get_v(), camera->get_p());
		if (mesh->bone_num >0)
		{
			material->set_bone(&mesh->bones[0][0][0], MAX_BONE_NUM * 16);
		}
		mesh->bind();
		glDrawElements(mesh->primitive, mesh->element_size, GL_UNSIGNED_SHORT, 0);
	}

	void print_tree(aiNode* node,int blk=0) {
		string b;
		for (int i=0;i<blk;i++)
		{
			b.append("--");
		}
		info("{}{}", b,string(node->mName.data));
		for (int i=0; i<node->mNumChildren;i++)
		{
			print_tree(node->mChildren[i],blk+1);
		}
	}

	bool import(const std::string& pFile)
	{
		Assimp::Importer importer;
		const aiScene* scene;
		info("import model: {}", pFile);
		scene = importer.ReadFile(pFile,
			aiProcess_CalcTangentSpace | 
			aiProcess_Triangulate | 
			aiProcess_JoinIdenticalVertices | 
			aiProcess_SortByPType |
			aiProcess_GenSmoothNormals
		); 
		if (!scene)
		{ 
			error("Import model error:{} {}", pFile, importer.GetErrorString());
			importer.FreeScene();
			return false;
		}

		auto ai_mesh = scene->mMeshes[0];
		info("mesh num: {}", scene->mNumMeshes);
		info("bone num: {}", ai_mesh->mNumBones);
		print_tree(scene->mRootNode);
		load_mesh(ai_mesh);
		if (ai_mesh->HasBones())
		{
			load_bone(scene);
		}
		


		importer.FreeScene();
		info("model import success :{}", pFile);
		return true;
	}

	void load_mesh(aiMesh* ai_mesh)
	{
		std::vector< std::vector<VertexBoneData> > vertex_bone_data;
		vertex_bone_data.resize(ai_mesh->mNumVertices);

		for (int i = 0; i < ai_mesh->mNumBones; i++)
		{
			auto b = ai_mesh->mBones[i];
			info("bone name: {}", string(b->mName.data));
			auto weight = b->mWeights;
			for (unsigned int j = 0; j < b->mNumWeights; j++)
			{
				VertexBoneData bone_data;
				bone_data.bone_id = i;
				bone_data.weight = weight[j].mWeight;
				vertex_bone_data[weight[j].mVertexId].push_back(bone_data);

				if (vertex_bone_data[i].size() > 4)
				{
					error("too much bone per vertex");
				}
			}
		}


		mesh = std::make_shared<Mesh>();
		mesh->primitive = ai_mesh->mPrimitiveTypes;;

		std::vector<float> vertex;
		for (unsigned int i = 0; i < ai_mesh->mNumVertices; i++) {
			vertex.push_back(ai_mesh->mVertices[i].x);
			vertex.push_back(ai_mesh->mVertices[i].y);
			vertex.push_back(ai_mesh->mVertices[i].z);

			const aiVector3D* norm = &(ai_mesh->mNormals[i]);
			if (norm != NULL)
			{
				vertex.push_back(norm->x);
				vertex.push_back(norm->y);
				vertex.push_back(norm->z);
			}

			if (ai_mesh->HasTextureCoords(0))
			{
				const aiVector3D* pTexCoord = &(ai_mesh->mTextureCoords[0][i]);
				vertex.push_back(pTexCoord->x);
				vertex.push_back(pTexCoord->y);
			}
			

			if (ai_mesh->HasBones())
			{
				auto bone_data = vertex_bone_data[i];
				for (int j = 0; j < 4; j++)
				{
					if (bone_data.size() > j)
					{
						vertex.push_back(bone_data[j].bone_id);
					}
					else {
						vertex.push_back(0);
					}
				}
				//4个ID 然后 4个weight
				for (int j = 0; j < 4; j++)
				{
					if (bone_data.size() > j)
					{
						vertex.push_back(bone_data[j].weight);
					}
					else {
						vertex.push_back(0);
					}
				}
			}
		}

		std::vector<unsigned short> index;
		for (unsigned int i = 0; i < ai_mesh->mNumFaces; i++) {
			const aiFace& Face = ai_mesh->mFaces[i];
			index.push_back(Face.mIndices[0]);
			index.push_back(Face.mIndices[1]);
			index.push_back(Face.mIndices[2]);
		}

		if (index.size() >65536)
		{
			error("Mesh too large limit 65536");
			return;
		}

		Buffer v;
		v.malloc(vertex.size() * sizeof(float));
		memcpy(v.data, vertex.data(), v.size);
		mesh->vertex = v;

		Buffer i;
		i.malloc(index.size() * sizeof(unsigned short));
		memcpy(i.data, index.data(), i.size);
		mesh->indices = i;

		mesh->element_size = index.size();
		
		mesh->add_default_attr(VAT_POSITION);
		if (ai_mesh->HasNormals())
		{
			mesh->add_default_attr(VAT_NORMAL);
		}
		if (ai_mesh->HasTextureCoords(0))
		{
			mesh->add_default_attr(VAT_UV0);
		}

		if (ai_mesh->HasBones())
		{
			mesh->bone_num = ai_mesh->mNumBones;
			mesh->add_default_attr(VAT_BONEIDS);
			mesh->add_default_attr(VAT_WEIGHTS);
		}

		mesh->build();

	}


	aiNode* find_tree(aiNode* node,const string &name) {
		if (name == string(node->mName.data)) {
			return node;
		}
		for (int i = 0; i < node->mNumChildren; i++)
		{
			auto n=find_tree(node->mChildren[i], name);
			if (n!=nullptr)
			{
				return n;
			}
		}
		return nullptr;
	}

	int find_bone_index(int num,aiBone** bones,const string &name) {
		for (int i=0;i<num;i++)
		{
			if (string(bones[i]->mName.data) ==name)
			{
				return i;
			}
		}
		error("find_bone_index error");
	}


	void load_bone(const aiScene* scene) {
		auto bones = scene->mMeshes[0]->mBones;
		auto ai_bone_root=find_tree(scene->mRootNode, bones[0]->mName.data);

		mesh->bone_tree= load_bone(scene,ai_bone_root, scene->mMeshes[0]->mNumBones, bones);
	}

	BoneNode * load_bone(const aiScene* scene,aiNode * ai_bone_root,int num,aiBone ** bones) {
		int index = find_bone_index(num, bones,string(ai_bone_root->mName.data));
		BoneNode* bone_root = new BoneNode;
		bone_root->name = string(ai_bone_root->mName.data);
		bone_root->bone_id = index;
		bone_root->offset_matrix= matrix_to_glm(bones[index]->mOffsetMatrix);
		bone_root->node_transform = matrix_to_glm(ai_bone_root->mTransformation);
		bone_root->final_matrix = mat4(1.f);

		auto m_GlobalInverseTransform = scene->mRootNode->mTransformation;
		bone_root->GlobalInverseTransform = matrix_to_glm(m_GlobalInverseTransform);
		bone_root->GlobalInverseTransform = inverse(bone_root->GlobalInverseTransform);

		mesh->bone_tree = bone_root;

		auto ai_animation = scene->mAnimations[0];
		bone_root->animation.duration = ai_animation->mDuration;
		bone_root->animation.ticks_per_second = ai_animation->mTicksPerSecond;


		aiNodeAnim* chan = nullptr;
		

		for (int i=0;i< ai_animation->mNumChannels; i++)
		{
			if (ai_animation->mChannels[i]->mNodeName == ai_bone_root->mName)
			{
				chan = ai_animation->mChannels[i];
			}
		}

		info("animation name {}", string(chan->mNodeName.data));

		for (int i=0;i< chan->mNumPositionKeys;i++)
		{
			Transform3d transform;
			convert_vec3(transform.position ,chan->mPositionKeys[i].mValue);
			convert_vec3(transform.scale, chan->mScalingKeys[i].mValue);
			quat q;
			q.x = chan->mRotationKeys[i].mValue.x;
			q.y = chan->mRotationKeys[i].mValue.y;
			q.z = chan->mRotationKeys[i].mValue.z;
			q.w = chan->mRotationKeys[i].mValue.w;
			transform.rotate = glm::eulerAngles(q) * 3.1415926f / 180.f;

			bone_root->animation.keys.push_back(transform);
		}
		

		for (int i=0;i<ai_bone_root->mNumChildren;i++)
		{
			auto child=load_bone(scene,ai_bone_root->mChildren[i], num, bones);
			bone_root->children.push_back(child);
		}
		return bone_root;

	}


	glm::mat4 matrix_to_glm(const aiMatrix4x4& from)
	{
		glm::mat4 to;
		//the a,b,c,d in assimp is the row ; the 1,2,3,4 is the column
		to[0][0] = from.a1; to[1][0] = from.a2; to[2][0] = from.a3; to[3][0] = from.a4;
		to[0][1] = from.b1; to[1][1] = from.b2; to[2][1] = from.b3; to[3][1] = from.b4;
		to[0][2] = from.c1; to[1][2] = from.c2; to[2][2] = from.c3; to[3][2] = from.c4;
		to[0][3] = from.d1; to[1][3] = from.d2; to[2][3] = from.d3; to[3][3] = from.d4;
		return to;
	}


	void convert_vec3(vec3 &dis, aiVector3D & source) {
		dis.x = source.x;
		dis.y = source.y;
		dis.z = source.z;
	}



};
typedef shared_ptr<Model> ModelPtr;

#endif

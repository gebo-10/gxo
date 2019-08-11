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
		mesh->bind();
		glDrawElements(mesh->primitive, mesh->element_size, GL_UNSIGNED_SHORT, 0);
	}



	bool import(const std::string& pFile)
	{
		Assimp::Importer importer;
		const aiScene* scene;

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

		load_mesh(scene->mMeshes[0]);

		importer.FreeScene();
		info("model import success :{}", pFile);
		return true;
	}

	void load_mesh(aiMesh* paiMesh)
	{
		mesh = std::make_shared<Mesh>();
		mesh->primitive = paiMesh->mPrimitiveTypes;;

		std::vector<float> vertex;
		for (unsigned int i = 0; i < paiMesh->mNumVertices; i++) {
			vertex.push_back(paiMesh->mVertices[i].x);
			vertex.push_back(paiMesh->mVertices[i].y);
			vertex.push_back(paiMesh->mVertices[i].z);

			const aiVector3D* norm = &(paiMesh->mNormals[i]);
			if (norm != NULL)
			{
				vertex.push_back(norm->x);
				vertex.push_back(norm->y);
				vertex.push_back(norm->z);
			}

			const aiVector3D* pTexCoord = &(paiMesh->mTextureCoords[0][i]);
			if (pTexCoord != NULL)
			{
				vertex.push_back(pTexCoord->x);
				vertex.push_back(pTexCoord->y);
			}
		}

		std::vector<unsigned short> index;
		for (unsigned int i = 0; i < paiMesh->mNumFaces; i++) {
			const aiFace& Face = paiMesh->mFaces[i];
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
		if (paiMesh->HasNormals())
		{
			mesh->add_default_attr(VAT_NORMAL);
		}
		if (paiMesh->HasTextureCoords(0))
		{
			mesh->add_default_attr(VAT_UV);
		}

		mesh->build();

	}

private:

};
typedef shared_ptr<Model> ModelPtr;

#endif

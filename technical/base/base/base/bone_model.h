#ifndef BONE_MODEL_H
#define BONE_MODEL_H
#include "model.h"
#include "bone_material.h"
class BoneModel :public Model
{
public:
	BoneTextureMaterialPtr material;
	BoneModel(string_view filename,TexturePtr texture) :Model(filename)
	{
		this->material = std::make_shared<BoneTextureMaterial>(texture);
	}


	void set_texture(TexturePtr texture) {
		std::dynamic_pointer_cast<BoneTextureMaterial>(material)->set_texture(texture);
	}

	virtual void render(CameraPtr camera) {
		static float i = 0;
		i+=0.2;


		mesh->update_bone((int)i %49);
		material->bind();
		material->mvp(transform.matrix(), camera->get_v(), camera->get_p());
		
		material->set_bone( &mesh->bones[0][0][0], MAX_BONE_NUM);
		mesh->bind();
		glDrawElements(mesh->primitive, mesh->element_size, GL_UNSIGNED_SHORT, 0);
	}
};
REG(BoneModel)

#endif#pragma once

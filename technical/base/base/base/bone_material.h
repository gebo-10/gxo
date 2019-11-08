#ifndef BONE_TEXTURE_METARIAL_H
#define BONE_TEXTURE_METARIAL_H

#include"material.h"

class BoneTextureMaterial :public Material
{
public:
	TexturePtr texture;
	BoneTextureMaterial(TexturePtr tex) :Material(nullptr)
	{
		texture = tex;
		string vs = "main/shader/bone_texture2.vert.glsl";
		string fs = "main/shader/bone_texture2.frag.glsl";
		auto texture_shader = std::make_shared<Shader>(vs, fs);
		set_shader(texture_shader);
	}

	virtual void bind() {
		shader->bind();
		texture->bind(0);
		int location = glGetUniformLocation(shader->gpu_id, "texture0");
		glUniform1i(location, 0);
	}

	void set_bone(float* bones, int size) {
		int location = glGetUniformLocation(shader->gpu_id, "bones");
		//glUniformmatrix4fv(location, size, bones);
		glUniformMatrix4fv(location, size, GL_TRUE, bones);
	}

	void set_texture(TexturePtr texture) {
		this->texture = texture;
	}


};
REG(BoneTextureMaterial)

#endif
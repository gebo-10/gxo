#ifndef PHONG_METARIAL_H
#define PHONG_METARIAL_H

#include"material.h"

class PhongMaterial :public Material
{
public:
	TexturePtr texture;
	PhongMaterial() :Material(nullptr)
	{
		string vs = "main/shader/phong.vert.glsl";
		string	fs = "main/shader/phong.frag.glsl";
		auto texture_shader = std::make_shared<Shader>(vs, fs);
		set_shader(texture_shader);
	}

	virtual void bind() {
		shader->bind();
		texture->bind(0);
		int location = glGetUniformLocation(shader->gpu_id, "texture0");
		glUniform1i(location, 0);
	}

	void set_texture(TexturePtr texture) {
		this->texture = texture;
	}

};
typedef shared_ptr<PhongMaterial> PhongMaterialPtr;

#endif
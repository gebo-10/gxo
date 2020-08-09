#ifndef GXO_DEFERRED_GPASS_METARIAL_H
#define GXO_DEFERRED_GPASS_METARIAL_H

#include"material.h"

class DeferredGpassMaterial :public Material
{
public:
	TexturePtr texture;
	DeferredGpassMaterial(TexturePtr tex) :Material(nullptr)
	{
		texture = tex;
		string vs = "main/shader/deferred_gpass.vert.glsl";
		string fs = "main/shader/deferred_gpass.frag.glsl";
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
private:

};
typedef std::shared_ptr<DeferredGpassMaterial> DeferredGpassMaterialPtr;

#endif
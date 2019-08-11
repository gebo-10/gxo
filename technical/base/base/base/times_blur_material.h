#ifndef TIMES_BLUR_MATERIAL_H
#define TIMES_BLUR_MATERIAL_H
#include "texture_material.h"
class TimesBlurMaterial : public TextureMaterial {
public:
	float blurRadius=1;
	float mDirectionx;
	float mDirectiony;

	TimesBlurMaterial() :TextureMaterial(nullptr) {
		string vs = "main/shader/times_blur.vert.glsl";
		string	fs = "main/shader/times_blur.frag.glsl";
		auto shader = std::make_shared<Shader>(vs, fs);
		set_shader(shader);

		
	}

	virtual void bind() {
		TextureMaterial::bind();

		int location = glGetUniformLocation(shader->gpu_id, "BlurRadius");
		glUniform1f(location, blurRadius);

		location = glGetUniformLocation(shader->gpu_id, "kzTextureWidth0");
		glUniform1f(location, texture->width);

		location = glGetUniformLocation(shader->gpu_id, "kzTextureHeight0");
		glUniform1f(location, texture->height);

		location = glGetUniformLocation(shader->gpu_id, "BlurDirection");
		glUniform2f(location, mDirectionx, mDirectiony);


	}

	void set_texture(TexturePtr texture) {
		this->texture = texture;
	}

	void set_direction(float x, float y) {
		mDirectionx = x ;
		mDirectiony = y ;
	}
	void set_radius(int radius) {
		blurRadius = radius;
	}
	int get_radius() {
		return blurRadius;
	}

};
REG(TimesBlurMaterial)

#endif

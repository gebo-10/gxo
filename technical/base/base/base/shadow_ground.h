#ifndef SHADOW_GROUND_H
#define SHADOW_GROUND_H
#include "ground.h"

class ShadowGround :public Ground
{
public:
	CameraPtr light_camera;
	TexturePtr shadow_map;
	ShadowGround() {
		string  vs = "main/shader/shadow_texture.vert.glsl";
		string	fs = "main/shader/shadow_texture.frag.glsl";
		auto material = make(TextureMaterial, vs, fs);
		material->set_texture(make(Texture, "main/texture/grid20.jpg"));
		this->material = material;
		transform.scale = vec3(6, 0, 6);
	}


	virtual void render(CameraPtr camera) {
		material->bind();
		material->set_uniform("texture1", GPU_SAMPLE2D, shadow_map);
		material->set_uniform("light_vp", GPU_MAT4, light_camera->get_p() * light_camera->get_v());

		material->mvp(transform.matrix(), camera->get_v(), camera->get_p());
		mesh->bind();
		glDrawElements(mesh->primitive, mesh->element_size, GL_UNSIGNED_SHORT, 0);
	}

	void set_shadow_map(TexturePtr shadow_map) {
		this->shadow_map = shadow_map;
	}
	void set_light_camera(CameraPtr light_camera) {
		this->light_camera = light_camera;
	}
};
REG(ShadowGround)

#endif

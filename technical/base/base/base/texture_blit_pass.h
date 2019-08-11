#ifndef TEXTURE_BLIT_PASS_H
#define TEXTURE_BLIT_PASS_H
#include "render_target.h"
#include "material.h"
#include "camera.h"
#include "texture_plane_model.h"
#include "screen_target.h"
class TextureBlitPass
{
public:
	CameraPtr ortho_camera;
	ModelPtr plane;
	RenderTargetPtr render_target;

	TexturePtr target;
	TexturePtr source;
	TextureMaterialPtr material;



	TextureBlitPass(TexturePtr target, TexturePtr source)
	{
		this->target = target;
		this->source = source;
		this->material = std::make_shared<TextureMaterial>(nullptr);

		init();
	}

	TextureBlitPass(TexturePtr target, TexturePtr source, TextureMaterialPtr material)
	{
		this->target = target;
		this->source = source;
		this->material = material;

		init();
	}

	void init() {
		render_target = std::make_shared<RenderTarget>(target->width, target->height);


		plane = std::make_shared<Model>(std::make_shared<Plane>(), material);
		ortho_camera = std::make_shared<Camera>();
		ortho_camera->set_type(Camera::ORTHO);
		if (target)
		{
			ortho_camera->set_ortho(-target->width / 2.0, target->width / 2.0, -target->height / 2.0, target->height / 2.0);
		}
		if (source)
		{
			material->set_texture(source);
		}

		//ortho_camera->set_near(-1);

		ortho_camera->set_type(Camera::PERSPECTIVE); //£¿£¿£¿ Ortho camera not usefull ???
		ortho_camera->set_fov(90);
		ortho_camera->lookat(vec3(0, 0, 0.5), vec3(0, 0, 0), vec3(0, 1, 0));
	}

	virtual void process() {
		blit();
	}

	void blit() {
		glDisable(GL_DEPTH_TEST);
		render_target->bind();
		glViewport(0, 0, target->width, target->height);
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		material->set_texture(source);
		plane->render(ortho_camera);
		render_target->unbind();
		glEnable(GL_DEPTH_TEST);
	}

	void set_material(TextureMaterialPtr mt) {
		material = mt;
		plane->material = material;
	}

	void set_target(TexturePtr t) {
		target = t;
		ortho_camera->set_ortho(-target->width / 2.0, target->width / 2.0, -target->height / 2.0, target->height / 2.0);

	}

	void set_source(TexturePtr s) {
		source = s;
	}

};
typedef shared_ptr<TextureBlitPass> TextureBlitPassPtr;
#endif

#ifndef DEFFERED_LIGHT_PASS_H
#define DEFFERED_LIGHT_PASS_H
#include "render_target.h"
#include "material.h"
#include "camera.h"
#include "texture_plane_model.h"
#include "screen_target.h"
class DeferredLightPass
{
public:
	CameraPtr ortho_camera;
	ModelPtr plane;

	RenderTargetPtr target;
	DeferredLightPassMaterialPtr material;

	DeferredLightPass() {
	}

	DeferredLightPass(RenderTargetPtr target, DeferredLightPassMaterialPtr mat)
	{
		this->target = target;
		this->material = mat;

		init();
	}


	void init() {
		plane = std::make_shared<Model>(std::make_shared<Plane>(), material);
		ortho_camera = std::make_shared<Camera>();
		ortho_camera->set_type(Camera::ORTHO);
		if (target)
		{
			ortho_camera->set_ortho(-target->width / 2.0, target->width / 2.0, -target->height / 2.0, target->height / 2.0);
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
		target->bind();
		glViewport(0, 0, target->width, target->height);
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		plane->render(ortho_camera);
		target->unbind();
		glEnable(GL_DEPTH_TEST);
	}

	void set_material(DeferredLightPassMaterialPtr mt) {
		material = mt;
		plane->material = material;
	}

	void set_target(RenderTargetPtr t) {
		target = t;
		ortho_camera->set_ortho(-target->width / 2.0, target->width / 2.0, -target->height / 2.0, target->height / 2.0);

	}

};
typedef std::shared_ptr<DeferredLightPass> DeferredLightPassPtr;
#endif

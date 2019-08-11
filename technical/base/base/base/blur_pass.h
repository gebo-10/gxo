#ifndef BLUR_PASS_H
#define BLUR_PASS_H
#include "blit_pass.h"
#include "blur_material.h"
class BlurPass
{
public:
	CameraPtr ortho_camera;
	TexturePlaneModelPtr plane;
	BlurMaterialPtr blur_material;
	RenderTargetPtr blur_x_target;
	RenderTargetPtr blur_y_target;
	int width;
	int height;

	BlurPass(TexturePtr source,int blur_radius=5) {
		width = source->width;
		height = source->height;

		blur_material = std::make_shared<BlurMaterial>(source->width/8, source ->height/8);
		blur_material->set_radius(blur_radius);
		blur_material->set_texture(source);

		blur_x_target = std::make_shared<RenderTarget>(source->width / 8, source->height / 8);
		blur_y_target = std::make_shared<RenderTarget>(source->width / 8, source->height / 8);

		plane = std::make_shared<TexturePlaneModel>(source);

		ortho_camera = std::make_shared<Camera>();
		ortho_camera->set_type(Camera::PERSPECTIVE);
		ortho_camera->set_ortho(-width / 2.0, width / 2.0, -height / 2.0, height / 2.0);
		
		ortho_camera->set_fov(90);
		ortho_camera->lookat(vec3(0, 0, 0.5), vec3(0, 0, 0), vec3(0, 1, 0));
	}


	virtual void process() {
		blur();
	}

	void blur() {
		blur_x_target->bind();
		glViewport(0, 0, width / 8, height / 8);
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		plane->material = blur_material;
		blur_material->set_direction(1, 0);
		plane->set_texture(blur_material->texture);
		plane->render(ortho_camera);
		blur_x_target->unbind();


		blur_y_target->bind();
		glViewport(0, 0, width / 8, height / 8);
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		plane->material = blur_material;
		blur_material->set_direction(0, 1);
		plane->set_texture(blur_x_target->get_texture());
		plane->render(ortho_camera);
		blur_y_target->unbind();
	}

	void set_source(TexturePtr s) {
		blur_material->set_texture(s); 
	}
	void set_radius(int r) {
		blur_material->set_radius(r);
	}

	TexturePtr get_texture() {
		return blur_y_target->get_texture();
	}
};
typedef shared_ptr<BlurPass> BlurPassPtr;
#endif

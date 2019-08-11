#ifndef TIMES_BLUR_PASS_H
#define TIMES_BLUR_PASS_H
#include "blit_pass.h"
#include "times_blur_material.h"
class TimesBlurPass
{
public:
	CameraPtr ortho_camera;
	TexturePlaneModelPtr plane;
	TimesBlurMaterialPtr blur_material;
	RenderTargetPtr blur_x_target;
	RenderTargetPtr blur_y_target;
	int width;
	int height;

	std::vector<float> times;
	TexturePtr source;
	TimesBlurPass(TexturePtr source, int blur_times = 2) {
		this->source = source;
		times.clear();
		times.push_back(3);
		times.push_back(8);
		init();
	}

	TimesBlurPass(TexturePtr source, std::vector<float> times) {
		this->source = source;
		this->times = times;
		init();
	}

	void init() {
		width = source->width;
		height = source->height;

		blur_material = std::make_shared<TimesBlurMaterial>();
		//blur_material->set_radius(1.0);
		blur_material->set_texture(source);

		blur_x_target = std::make_shared<RenderTarget>(source->width, source->height);
		blur_y_target = std::make_shared<RenderTarget>(source->width, source->height);

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

		TexturePtr input = source;
		for (auto radius:times)
		{
			blur_material->set_radius(radius);
			blur_x_target->bind();
			glViewport(0, 0, width , height );
			glClearColor(0.0, 0.0, 0.0, 0.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			plane->material = blur_material;
			blur_material->set_direction(1, 0);
			plane->set_texture(input);
			plane->render(ortho_camera);
			blur_x_target->unbind();


			blur_y_target->bind();
			glViewport(0, 0, width , height );
			glClearColor(0.0, 0.0, 0.0, 0.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			plane->material = blur_material;
			blur_material->set_direction(0, 1);
			plane->set_texture(blur_x_target->get_texture());
			plane->render(ortho_camera);
			blur_y_target->unbind();

			input = blur_y_target->get_texture();
		}
		
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
REG(TimesBlurPass)
#endif

#ifndef BLUR_MODULE_H
#define BLUR_MODULE_H
#include "module.h"
class BlurModule :public Module
{
public:

	CameraPtr camera;
	CameraPtr full_camera;
	ModelPtr cube;
	RenderTargetPtr render_target;

	TexturePlaneModelPtr plane;

	BlurMaterialPtr blur_material;
	RenderTargetPtr blur_x_target;
	RenderTargetPtr blur_y_target;

	TextureMaterialPtr texture_material;

	BlitPassPtr blit_pass;
	//BlurPassPtr blur_pass;

	TimesBlurPassPtr blur_pass;

	BlurModule()
	{
	}


	virtual void init() {

		texture_material = std::make_shared<TextureMaterial>(nullptr);

		blur_material = std::make_shared<BlurMaterial>(800/8, 800/8);
		blur_material->set_radius(15);

		blur_x_target= std::make_shared<RenderTarget>(800 / 8, 800 / 8);
		blur_y_target = std::make_shared<RenderTarget>(800 / 8, 800 / 8);

		render_target = std::make_shared<RenderTarget>(800, 800);

		TexturePtr t = std::make_shared<Texture>("main/texture/1.jpeg");
		plane = std::make_shared<TexturePlaneModel>(t);

		cube = std::make_shared<Model>(std::make_shared<Cube>(), std::make_shared<TextureMaterial>(t));

		camera = std::make_shared<Camera>();
		camera->lookat(vec3(0, 0, 2), vec3(0, 0, 0), vec3(0, 1, 0));

		full_camera = std::make_shared<Camera>();
		full_camera->set_fov(90);
		full_camera->lookat(vec3(0, 0, 0.5), vec3(0, 0, 0), vec3(0, 1, 0));


		//blur_pass = std::make_shared<BlurPass>(render_target->get_texture());
		blur_pass = make(TimesBlurPass, render_target->get_texture(), 2);
		blit_pass = std::make_shared<BlitPass>(std::make_shared<ScreenTarget>(800, 800), blur_pass->get_texture());

		

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glClearColor(1.0, 0.5, 0.2, 1.0);

		glViewport(0, 0, 800, 800);

		
	}
	virtual void render() {
		/* Render here */
		static int i = 30;
		cube->transform.rotate = vec3(i, i, i);
		i++;

		render_target->bind();
		glViewport(0, 0, 800 , 800 );
		glClearColor(1.0, 0.5, 0.2, 0.8);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //| GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT
		cube->render(camera);
		render_target->unbind();


		//blur_x_target->bind();
		//glViewport(0, 0, 800 / 8, 800 / 8);
		//glClearColor(1.0, 0.5, 0.8, 0.8);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//plane->material = blur_material;
		//blur_material->set_direction(1, 0);
		//plane->set_texture(render_target->get_texture());
		//plane->render(full_camera);
		//blur_x_target->unbind();


		//blur_y_target->bind();
		//glViewport(0, 0, 800 / 8, 800 / 8);
		//glClearColor(1.0, 0.5, 0.8, 0.1);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//plane->material = blur_material;
		//blur_material->set_direction(0, 1);
		//plane->set_texture(blur_x_target->get_texture());
		//plane->render(full_camera);
		//blur_y_target->unbind();

		//blit_pass->set_source(blur_y_target->get_texture());

		blur_pass->set_source(render_target->get_texture());
		blur_pass->process();


		blit_pass->set_source(blur_pass->get_texture());
		blit_pass->process();
		//glViewport(0, 0, 800, 800);
		//glClearColor(0.0, 0.5, 0.9, 1.0);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//plane->material = texture_material;
		//plane->set_texture(blur_y_target->get_texture());
		//plane->render(camera);
	}

	virtual void key(int key) {}

	virtual void mouse(int button, int x, int y) {}

private:

};

#endif
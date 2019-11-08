#ifndef SHADOW_MAP_MODULE_H
#define SHADOW_MAP_MODULE_H
#include "module.h"
class ShadowMapModule :public Module
{
public:
	CameraPtr camera;
	CameraPtr light_camera;
	ModelPtr model;

	PhongMaterialPtr phong_material;

	ShadowGroundPtr ground;

	DepthRenderTargetPtr depth_render_target;

	virtual void init() {
		ground = std::make_shared<ShadowGround>();
		TexturePtr t = std::make_shared<Texture>("main/texture/miku.png");

		model = std::make_shared<Model>("main/mesh/miku.gltf");
		//model = std::make_shared<Model>("main/mesh/plane.gltf");

		phong_material = std::make_shared<PhongMaterial>();
		phong_material->set_texture(t);

		model->material = phong_material;

		depth_render_target = make(DepthRenderTarget, 2048, 2048);
		//shadow_msaa_pass = make(MsaaRttPass, 2048, 2048, 1, GL_RGBA, []() {});

		camera = std::make_shared<Camera>();
		camera->set_type(Camera::PERSPECTIVE);
		camera->set_ortho(-400, 400, -400, 400);
		camera->lookat(vec3(0, 1, 4), vec3(0, 0, 0), vec3(0, 1, 0));

		light_camera = make(Camera);
		light_camera->set_type(Camera::PERSPECTIVE);
		light_camera->set_ortho(-1024, 1024, -1024, 1024);
		light_camera->lookat(vec3(1, 2, 3), vec3(0, 0, 0), vec3(0, 1, 0));

		ground->set_light_camera(light_camera);
		


		glEnable(GL_TEXTURE_2D);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glCullFace(GL_BACK);
		glClearColor(1.0, 0.5, 0.2, 1.0);




		//shadow_msaa_pass->set_pass([this]() {
		//	CameraPtr light_camera=make(Camera);
		//	light_camera->set_type(Camera::PERSPECTIVE);
		//	light_camera->set_ortho(-1024, 1024, -1024, 1024);
		//	light_camera->lookat(vec3(1, 2, 3), vec3(0, 0, 0), vec3(0, 1, 0));

		//	glViewport(0,0,2048, 2048);
		//	glClearColor(0.0, 0.0, 0.0, 0.0);
		//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//	model->render(light_camera);
		//	//ground->render(camera);
		//	});


	}
	virtual void render() {
		/* Render here */
		static int i = 0;
		model->transform.rotate = vec3(0, i, 0);
		i+=1;

		depth_render_target->bind();
		glViewport(0, 0, 2048, 2048);
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		model->render(light_camera);
		depth_render_target->unbind();

		ground->set_shadow_map(depth_render_target->get_texture());

		//shadow_msaa_pass->process();
		glViewport(0, 0, 800, 800);
		glClearColor(1.0, 0.5, 0.2, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //| GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT
		model->render(camera);
		ground->render(camera);


		
	}

	virtual void key(int key) {}

	virtual void mouse(int button, int x, int y) {}

private:

};

#endif
#ifndef SHADOW_MAP_MODULE_H
#define SHADOW_MAP_MODULE_H
#include "module.h"
class ShadowMapModule :public Module
{
public:
	CameraPtr camera;
	ModelPtr model;

	PhongMaterialPtr phong_material;

	GroundlPtr ground;


	virtual void init() {
		ground = std::make_shared<Ground>();
		TexturePtr t = std::make_shared<Texture>("main/texture/miku.png");

		model = std::make_shared<Model>("main/mesh/miku.gltf");
		//model = std::make_shared<Model>("main/mesh/plane.gltf");

		phong_material = std::make_shared<PhongMaterial>();
		phong_material->set_texture(t);

		model->material = phong_material;


		camera = std::make_shared<Camera>();
		camera->set_type(Camera::PERSPECTIVE);
		camera->set_ortho(-400, 400, -400, 400);
		camera->lookat(vec3(0, 1, 3), vec3(0, 0, 0), vec3(0, 1, 0));

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glCullFace(GL_BACK);
		glClearColor(1.0, 0.5, 0.2, 1.0);


	}
	virtual void render() {
		/* Render here */
		static int i = 0;
		model->transform.rotate = vec3(0, i, 0);
		i++;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //| GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT
		model->render(camera);
		ground->render(camera);
	}

	virtual void key(int key) {}

	virtual void mouse(int button, int x, int y) {}

private:

};

#endif
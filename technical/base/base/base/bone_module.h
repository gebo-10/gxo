#ifndef BONE_MODULE_H
#define BONE_MODULE_H
#include "module.h"
class BoneModule :public Module
{
public:
	CameraPtr camera;
	BoneModelPtr model;

	GroundlPtr ground;

	virtual void init() {
		ground = std::make_shared<Ground>();
		ground->transform.position = vec3(0, 0, 0);
		TexturePtr t = std::make_shared<Texture>("main/mesh/man2.png");

		model = std::make_shared<BoneModel>("main/mesh/man2.gltf", t);
		//model->material = make(BoneTextureMaterial,t);
		model->transform.scale = vec3(0.001,0.001,0.001);

		camera = std::make_shared<Camera>();
		camera->set_type(Camera::PERSPECTIVE);
		camera->set_ortho(-400, 400, -400, 400);
		camera->lookat(vec3(0, 0, 2), vec3(0, 0.4, 0), vec3(0, 1, 0));

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_TEXTURE_2D_MULTISAMPLE);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glCullFace(GL_BACK);
		glClearColor(0.4, 0.5, 0.6, 1.0);


	}
	virtual void render() {
		/* Render here */
		static int i = 0;
		//model->transform.rotate = vec3(0, i, 0);
		i++;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //| GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT
		model->render(camera);
		//ground->render(camera);
	}

	virtual void key(int key) {}

	virtual void mouse(int button, int x, int y) {}

private:

};

#endif
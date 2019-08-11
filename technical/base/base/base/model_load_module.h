#ifndef MODEL_LOAD_MODULE_H
#define MODEL_LOAD_MODULE_H
#include "module.h"
class ModelLoadModule :public Module
{
public:
	CameraPtr camera;
	ModelPtr model;


	virtual void init() {
		TexturePtr t = std::make_shared<Texture>("main/texture/miku.png");

		model = std::make_shared<Model>("main/mesh/miku.gltf");
		model->material = std::make_shared<TextureMaterial>(t);

		camera = std::make_shared<Camera>();
		camera->set_type(Camera::PERSPECTIVE);
		camera->set_ortho(-400, 400, -400, 400);
		camera->lookat(vec3(0, 0, 3), vec3(0, 0, 0), vec3(0, 1, 0));

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_DEPTH_TEST);
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

	}

	virtual void key(int key) {}

	virtual void mouse(int button, int x, int y) {}

private:

};

#endif
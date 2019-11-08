#ifndef GLTF_MODULE_H
#define GLTF_MODULE_H
#include "module.h"
#include "gltf_scene.h"
class GltfModule :public Module
{
public:
	CameraPtr camera;
	ModelPtr model;
	GltfModelPtr gltf_model;
	vkglTF::Model scene;
	GroundlPtr ground;
	virtual void init() {
		ground = std::make_shared<Ground>();
		gltf_model = make(GltfModel,"main/mesh/CesiumMan.gltf");

		TexturePtr t = std::make_shared<Texture>("main/texture/miku.png");

		model = std::make_shared<Model>("main/mesh/miku.gltf");
		model->material = std::make_shared<TextureMaterial>(t);


		scene.loadFromFile("main/mesh/man2.gltf");


		//gltf_model->set_material(make(BoneTextureMaterial,t));

		camera = std::make_shared<Camera>();
		camera->set_type(Camera::PERSPECTIVE);
		camera->set_ortho(-400, 400, -400, 400);
		camera->lookat(vec3(0, 1, 3), vec3(0, 0, 0), vec3(0, 1, 0));

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_DEPTH_TEST);
		//glCullFace(GL_BACK);
		glClearColor(1.0, 0.5, 0.2, 1.0);


	}
	virtual void render() {
		/* Render here */
		static int i = 0;
		model->transform.rotate = vec3(0, i, 0);
		//gltf_model->transform.rotate = vec3(-90, 0, 0);
		scene.transform.rotate = vec3(0, i, 0);
		//scene.transform.position= vec3(-0.0, -1, 0);
		ground->transform.position= vec3(0, 0, 0);
		i++;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //| GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT
		//model->render(camera);
		//gltf_model->render(camera);
		ground->render(camera);
		scene.draw(camera);
	}

	virtual void key(int key) {}

	virtual void mouse(int button, int x, int y) {}

private:

};

#endif
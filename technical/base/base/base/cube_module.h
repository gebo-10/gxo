#ifndef CUBE_MODULE_H
#define CUBE_MODULE_H
#include "module.h"
class CubeModule :public Module
{
public:
	
	CameraPtr camera;
	ModelPtr cube;
	CubeModule()
	{
	}

	~CubeModule()
	{
	}

	virtual void init() {
		TexturePtr t = std::make_shared<Texture>("main/texture/road.jpg");

		cube=std::make_shared<Model>(std::make_shared<Cube>(), std::make_shared<TextureMaterial>(t));

		camera = std::make_shared<Camera>();
		camera->set_type(Camera::PERSPECTIVE);
		camera->set_ortho(-400, 400, -400, 400);
		camera->lookat(vec3(0, 0, 5), vec3(0, 0, 0), vec3(0, 1, 0));

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_DEPTH_TEST);
		glClearColor(1.0, 0.5, 0.2, 1.0);

		 
	}
	virtual void render() {
		/* Render here */
		static int i = 0;
		cube->transform.rotate = vec3(i, i, i);
		i++;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //| GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT
		cube->render(camera);

	}

	virtual void key(int key) {}

	virtual void mouse(int button, int x, int y) {}

private:

};

#endif
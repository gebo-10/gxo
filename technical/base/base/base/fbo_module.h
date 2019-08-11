#ifndef FBO_MODULE_H
#define FBO_MODULE_H
#include "module.h"
class FboModule :public Module
{
public:

	CameraPtr camera;
	ModelPtr cube;
	RenderTargetPtr render_target;

	TexturePlaneModelPtr plane;
	FboModule()
	{
	}

	~FboModule()
	{
	}

	virtual void init() {
		
		render_target =std::make_shared<RenderTarget>(800,800);

		TexturePtr t = std::make_shared<Texture>("main/texture/road.jpg");
		plane = std::make_shared<TexturePlaneModel>(t);

		cube = std::make_shared<Model>(std::make_shared<Cube>(), std::make_shared<TextureMaterial>(t));

		camera = std::make_shared<Camera>();
		camera->set_type(Camera::PERSPECTIVE);
		camera->set_ortho(-400, 400, -400, 400);
		camera->lookat(vec3(0, 0, 2), vec3(0, 0, 0), vec3(0, 1, 0));

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_DEPTH_TEST);
		glClearColor(1.0, 0.5, 0.2, 1.0);


	}
	virtual void render() {
		/* Render here */
		static int i = 0;
		cube->transform.rotate = vec3(i, i, i);
		i++;
		render_target->bind();
		glClearColor(1.0, 0.5, 0.2, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //| GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT
		cube->render(camera);
		render_target->unbind();

		glClearColor(0.0, 0.5, 0.2, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		plane->set_texture(render_target->get_texture());
		plane->render(camera);
	}

	virtual void key(int key) {}

	virtual void mouse(int button, int x, int y) {}

private:

};

#endif
#ifndef DEFERRED_MODULE_H
#define DEFERRED_MODULE_H
#include "module.h"
#include<vector>
#include "deferred_gpass_material.h"
#include "deferred_lightpass_material.h"
#include "deferred_light_pass.h"
class DeferredModule :public Module
{
public:
	CameraPtr camera;
	ModelPtr model;
	GroundlPtr ground;

	DeferredLightPassPtr light_pass;

	RenderTargetPtr gbuffer;
	std::vector<TexturePtr> gbuffer_texture;
	TexturePtr gpos;
	TexturePtr gnormal;
	TexturePtr gcolor;

	DeferredLightPassMaterialPtr light_mat;


	virtual void init() {
		ground = std::make_shared<Ground>();
		TexturePtr t = std::make_shared<Texture>("main/texture/miku.png");

		model = std::make_shared<Model>("main/mesh/miku.gltf");
		
		gpos = std::make_shared<Texture>(800, 800, nullptr, GL_RGB, GL_RGBA16);
		gnormal = std::make_shared<Texture>(800, 800, nullptr, GL_RGB, GL_RGBA16);
		gcolor = std::make_shared<Texture>(800, 800, nullptr, GL_RGBA);
		gbuffer_texture.push_back(gpos);
		gbuffer_texture.push_back(gnormal);
		gbuffer_texture.push_back(gcolor);

		gbuffer = make(RenderTarget, 800, 800, gbuffer_texture);

		DeferredGpassMaterialPtr mat= std::make_shared<DeferredGpassMaterial>(t);
		model->material = mat;

		
		
		light_mat = std::make_shared<DeferredLightPassMaterial>(gpos, gnormal, gcolor);
		light_pass = std::make_shared<DeferredLightPass>(std::make_shared<ScreenTarget>(800, 800), light_mat);


		camera = std::make_shared<Camera>();
		camera->set_type(Camera::PERSPECTIVE);
		camera->set_ortho(-400, 400, -400, 400);
		camera->lookat(vec3(0, 1, 3), vec3(0, 0, 0), vec3(0, 1, 0));

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_TEXTURE_2D_MULTISAMPLE);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		//glCullFace(GL_BACK);
		glClearColor(1.0, 0.5, 0.2, 1.0);
		srand((unsigned)time(0));
	}
	virtual void render() {
		static float i = 0;
		i+=0.6;
		model->transform.rotate = vec3(0, i, 0);

		for (size_t i = 0; i < 32; i++)
		{
			
			float r=(rand() % 500) / 100.0;

			light_mat->set_light(i, vec3(r,r,r), vec3(r/100.0,r/100.0,r/100.0));
		}
		


		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		ground->render(camera);

		gbuffer->bind();
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		model->render(camera);
		
		gbuffer->unbind();

		
		light_mat->set_view_pos(vec3(0, 1, 3));
		light_pass->process();

		
	}

	virtual void key(int key) {}


};

#endif
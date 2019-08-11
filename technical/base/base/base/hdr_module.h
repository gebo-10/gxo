#ifndef HDR_MODULE_H
#define HDR_MODULE_H
#include "module.h"
class HdrModule :public Module
{
public:
	CameraPtr camera;
	ModelPtr model;

	PhongMaterialPtr phong_material;

	GroundlPtr ground;

	MsaaRttPassPtr msaa_pass;

	BlitPassPtr blit_pass;
	TimesBlurPassPtr blur_pass;

	TextureMaterialPtr bloom_combin;

	virtual void init() {
		ground = std::make_shared<Ground>();
		TexturePtr t = std::make_shared<Texture>("main/texture/miku.png");

		model = std::make_shared<Model>("main/mesh/miku.gltf");
		//model = std::make_shared<Model>("main/mesh/plane.gltf");

		phong_material = std::make_shared<PhongMaterial>();
		phong_material->set_texture(t);

		string vs = "main/shader/bloom_phong.vert.glsl";
		string	fs = "main/shader/bloom_phong.frag.glsl";
		auto texture_shader = std::make_shared<Shader>(vs, fs);
		phong_material->set_shader(texture_shader);

		model->material = phong_material;

		msaa_pass = make(MsaaRttPass, 800, 800, 2,GL_RGBA16F,[]() {});

		std::vector<float> times;
		times.push_back(1);
		times.push_back(3);
		times.push_back(8);
		times.push_back(16);
		times.push_back(30);
		blur_pass = std::make_shared<TimesBlurPass>(msaa_pass->get_texture(1), times);
		blit_pass= std::make_shared<BlitPass>(std::make_shared<ScreenTarget>(800, 800), msaa_pass->get_texture());

		//string hdr_vs = "main/shader/hdr_texture.vert.glsl";
		//string hdr_fs = "main/shader/hdr_texture.frag.glsl";
		//blit_pass->set_material(std::make_shared<TextureMaterial>(hdr_vs, hdr_fs));

		string bloom_vs = "main/shader/bloom_combin.vert.glsl";
		string bloom_fs = "main/shader/bloom_combin.frag.glsl";
		bloom_combin = make(TextureMaterial, bloom_vs, bloom_fs);
		bloom_combin->set_texture(msaa_pass->get_texture());
		//bloom_combin->set_uniform("texture0", GPU_SAMPLE2D,msaa_pass->get_texture());
		//bloom_combin->set_uniform("texture1", GPU_SAMPLE2D, blur_pass->get_texture());
		blit_pass->set_material(bloom_combin);


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




		msaa_pass->set_pass([this]() {
			glClearColor(0.0, 0.0, 0.0, 0.0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
			model->render(camera);
			//ground->render(camera);
		});

	}
	virtual void render() {
		static float i = 0;
		i+=0.6;
		model->transform.rotate = vec3(0, i, 0);
		
		msaa_pass->process();

		//int r = i/5 % 31 + 1;
		//blur_pass->set_radius(30);
		blur_pass->set_source(msaa_pass->get_texture(1));
		blur_pass->process();

		//blit_pass->set_source(msaa_pass->get_texture());
		bloom_combin->set_uniform("texture0", GPU_SAMPLE2D, msaa_pass->get_texture());
		bloom_combin->set_uniform("texture1", GPU_SAMPLE2D, blur_pass->get_texture());
		//blit_pass->set_source(blur_pass->get_texture());
		
		blit_pass->process();
	}

	virtual void key(int key) {}


};

#endif
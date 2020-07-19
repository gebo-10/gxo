#include "gxo.h"
using namespace gxo;
class TestApplication:public Application
{
public:
	TestApplication()
	{
	}

	~TestApplication()
	{

	}


	virtual void on_config() {

	}

	virtual void on_project_loaded()
	{
		auto ui_root = new UiRoot;
		//ui_root->add_property(LAYOUT_SIZE, ivec2(200, 200));
		//ui_root->add_property(POSITION, ivec2(20, 20));


		auto img = new UiImage();
		ui_root->add_child(img);


		auto node = new UiNode();
		RenderPass* rp = new RenderPass();
		rp->type = 3;
		node->add_property(RENDER_PASS, rp);
		node->add_property(LAYOUT_SIZE, ivec2(100, 100));
		node->add_property(POSITION, ivec2(100, 10));
		node->add_property(ALIGN_X, ALIGN_CENTER);
		node->add_property(ALIGN_Y, ALIGN_TOP);

		Transform3d t;
		t.position = vec3(0, 0, 0);
		t.scale = vec3(1, 2, 1);
		t.rotate = vec3(0, 0, 10);
		node->add_property(TRANSFORM3D, t);

		node->add_property(ANCHOR, vec2(0.5,0));


		ui_root->add_child(node);


		auto text = new UiText();
		node->add_child(text);



		auto viewport2d = new UiViewPort();
		viewport2d->add_property(LAYOUT_SIZE, ivec2(50, 300));
		viewport2d->add_property(POSITION, ivec2(100, 10));

		ui_root->add_child(viewport2d);

		auto scene = new Scene();
		ui_root->add_child(scene);

		
		auto scene_camera = new SceneCamera();
		scene->add_child(scene_camera);

		{
			 cube = new SceneCube();
			Transform3d t;
			t.position = vec3(0, 0, 0);
			t.scale = vec3(1,1, 1);
			t.rotate = vec3(60, 60, 60);
			cube->set(TRANSFORM3D, t);
			scene->add_child(cube);
		}

		//viewport2d->scene = scene;
		viewport2d->set<SceneRef>(SCENE,scene);
		viewport2d->scene_camera = scene_camera;

		Engine::instacne().tree_manager.screen.add_child(ui_root);
	}


	virtual void on_update() {
		//info("Hello, {}!", "Application");

		Transform3d t;
		t.position = vec3(0, 0, 0);
		t.scale = vec3(1, 1, 1);
		t.rotate = vec3(degree, degree, degree);
		//t.rotate = vec3(0, 0, 0);
		cube->set(TRANSFORM3D, t);
		degree += 1;
	}

	

	virtual void register_matedata()
	{
	}



private:
	SceneCube* cube;
	float degree=0;
};
APP(TestApplication);
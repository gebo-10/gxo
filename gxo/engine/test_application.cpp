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
		ui_root->add_property(LAYOUT_SIZE, ivec2(200, 200));
		ui_root->add_property(POSITION, ivec2(0, 0));

		auto node = new UiNode();
		RenderPass* rp = new RenderPass();
		rp->type = 3;
		node->add_property(RENDER_PASS, rp);
		node->add_property(LAYOUT_SIZE, ivec2(100, 100));
		node->add_property(ALIGN_X, ALIGN_CENTER);

		ui_root->add_child(node);

		Engine::instacne().tree_manager.screen.add_child(ui_root);
	}


	virtual void on_update() {
		//info("Hello, {}!", "Application");
	}

	

	virtual void register_matedata()
	{
	}



private:

};
APP(TestApplication);
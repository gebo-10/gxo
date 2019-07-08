#include"render_system.h"
#include"engine.h"
#include"ui_node.h"
#include"evn.h"
void gxo::RenderSystem::init()
{
	
	render.init();

	return ;
}

void gxo::RenderSystem::update()
{
	//
	//glBegin(GL_TRIANGLES);

	//glColor3f(1.0, 0.0, 0.0);    // Red
	//glVertex3f(0.0, 1.0, 0.0);

	//glColor3f(0.0, 1.0, 0.0);    // Green
	//glVertex3f(-1.0, -1.0, 0.0);

	//glColor3f(0.0, 0.0, 1.0);    // Blue
	//glVertex3f(1.0, -1.0, 0.0);

	//glEnd();
	//glMatrixMode(GL_PROJECTION);
	//glLoadIdentity();
	//glOrtho(-1, 1, -1, 1, -4, 4000);
	//glViewport(0, 0, Engine::instacne().window_system.rect.width-300, Engine::instacne().window_system.rect.height);



	//glClearColor(0.f, 0.f, 0.f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT| GL_STENCIL_BUFFER_BIT);
	//auto rect = Rect(0, 0, 500, 500);
	//Engine::instacne().tree_manager.screen.on_layout(rect);

	//Engine::instacne().tree_manager.visit_preorder([](TreeNode * node) -> bool{
	//	return node->on_render();
	//});
	//Engine::instacne().window_system.swap_buffer();




	//auto rect = Rect(0, 0, 500, 500);
	//Engine::instacne().tree_manager.screen.on_layout(rect);
	//Engine::instacne().tree_manager.screen.on_render();
	//render.rcmd(RCMD_SWAPBUFFER);



	auto pipe = std::make_shared<Pipeline>();

	string name = "main/material/Default";
	pipe->material = * env.engine->resource_manager.get<Material>(name);
	pipe->viewport = Rect(0, 0, 500, 500);
	pipe->target = std::make_shared<RenderTarget>();

	render.rcmd(RCMD_SET_PIPELINE, pipe);
	static float r = 0.0f;
	r += 0.001;
	render.rcmd(RCMD_CLEAR, Color(r,1-r,1.0,1.0));
	render.rcmd(RCMD_SWAPBUFFER);

}



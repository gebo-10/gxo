#include"render_system.h"
#include"engine.h"
#include"ui_node.h"
#include"env.h"
#include"camera.h"
#include "gpu_type.h"
void gxo::RenderSystem::init()
{
	render.init();
	return ;
}

void gxo::RenderSystem::update()
{
	env.engine->tree_manager.screen.on_render();

	render.rcmd(RCMD_SWAPBUFFER);
}

void gxo::RenderSystem::stop()
{
	render.quit();
}



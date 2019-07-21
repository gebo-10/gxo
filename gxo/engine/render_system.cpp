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
	auto rect = Rect(0, 0, 600, 600);
	
	auto pipe = std::make_shared<Pipeline>();
	pipe->viewport = rect;
	pipe->target = std::make_shared<RenderTarget>();
	pipe->cull_face = CULL_NULL;
	render.rcmd(RCMD_SET_PIPELINE, pipe);

	
	Engine::instacne().tree_manager.screen.on_layout(rect);
	Engine::instacne().tree_manager.screen.on_render();

	render.rcmd(RCMD_SWAPBUFFER);
}



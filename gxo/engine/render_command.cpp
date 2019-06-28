#include"render_commend.h"
#include"engine.h"
void gxo::RenderCommand::process(Render* render)
{
}

void gxo::RcmdSwapBuffer::process(Render* render)
{
	Engine::instacne().window_system.swap_buffer();
}

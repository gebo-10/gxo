#include "render.h"
#include"engine.h"
void gxo::Render::init()
{
	render_thread = std::thread(thread_main, this);
}

void gxo::Render::process()
{
	Engine::instacne().window_system.make_current();
	gpu.init();
	
	gpu.log_device_info();

	RenderCommandPtr cmd;
	while (!stop)
	{
		cmd = pop_command();
		if (cmd != nullptr) {
			cmd->process(this);
			cmd = nullptr;
		}
		else {
			std::unique_lock <std::mutex> lck(lock);
			cv.wait(lck);
			wait = true;
		}
	}
}
#ifndef GXO_RENDERER_H
#define GXO_RENDERER_H
#include"render_commend.h"
#include"circle_queue.h"
#include"pipeline.h"
namespace gxo {
	#define RENDER_COMMAND_QUEUE_SIZE 100
	class Render
	{
	public:
		bool stop;
		bool wait;
		CircleQueue<RenderCommandPtr, RENDER_COMMAND_QUEUE_SIZE> command_queue;
		std::thread render_thread;

		GPU gpu;

		Render():stop(false),wait(false){}

		void init() {
			render_thread=std::thread()
		}

		void push_command(RenderCommandPtr rcmd) {
			command_queue.write([&](RenderCommandPtr* cmd) {
				*cmd = rcmd;
			});
			if (wait) {
			//	notify();
				process();
			}
		}
		RenderCommandPtr pop_command() {
			RenderCommandPtr rcmd=nullptr;
			auto succ=command_queue.read([&](RenderCommandPtr* cmd) {
				rcmd=*cmd ;
			});
			
			return rcmd;
		}
		void quit() {
			stop = true;
		}

		static void process(Render * renderer) {
			RenderCommandPtr cmd;
			while (!stop)
			{
				cmd = pop_command();
				if (cmd != nullptr) {
					cmd->process(this);
					cmd = nullptr;
				}
				else {
					//wait = true;
					break;
				//	wait();
				}
			}
		}
	};
}
#endif
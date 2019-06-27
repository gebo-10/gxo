#ifndef GXO_RENDER_ENGINE_H
#define GXO_RENDER_ENGINE_H
#include"render_commend.h"
#include"circle_queue.h"
namespace gxo {
#define RENDER_COMMAND_QUEUE_SIZE 100
	class RenderEngine
	{
	public:
		bool stop;
		bool wait;
		RenderEngine():stop(false),wait(false){}
		CircleQueue<RenderCommand*, RENDER_COMMAND_QUEUE_SIZE> command_queue;

		void push_command(RenderCommand* rcmd) {
			command_queue.write([&](RenderCommand** cmd) {
				*cmd = rcmd;
			});
			if (wait) {
				notify();
			}
		}
		RenderCommand* pop_command() {
			RenderCommand* rcmd=nullptr;
			auto succ=command_queue.read([&](RenderCommand** cmd) {
				rcmd=*cmd ;
			});
			
			return rcmd;
		}
		void quit() {
			stop = true;
		}

		void process() {
			RenderCommand* cmd;
			while (!stop)
			{
				cmd = pop_command();
				if (cmd != nullptr) {
					cmd->process(this);
				}
				else {
					wait = true;
					wait();
				}
			}
		}
	};
}
#endif
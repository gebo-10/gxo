#ifndef GXO_RENDERER_H
#define GXO_RENDERER_H
#include"render_commend.h"
#include"circle_queue.h"
#include"pipeline.h"
#include <thread>              
#include <mutex>                
#include <condition_variable> 
#include"gpu.h"
namespace gxo {
	#define RENDER_COMMAND_QUEUE_SIZE 100
	class Render
	{
	public:
		bool stop;
		bool wait;
		std::mutex lock; 
		std::condition_variable cv;
		CircleQueue<RenderCommandPtr, RENDER_COMMAND_QUEUE_SIZE> command_queue;
		std::thread render_thread;

		GPU gpu;

		Render():stop(false),wait(false){}

		void init();

		void push_command(RenderCommandPtr rcmd) {
			command_queue.write([&](RenderCommandPtr* cmd) {
				*cmd = rcmd;
			});
			if (wait) {
				std::unique_lock <std::mutex> lck(lock);
				wait = false; 
				cv.notify_all();
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
	private:
		void process();
		static void thread_main(Render* render) {
			render->process();
		}
	};
}
#endif
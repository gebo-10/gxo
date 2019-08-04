#ifndef GXO_COMMAND_PIPE_H
#define GXO_COMMAND_PIPE_H
#include"circle_queue.h"
#include <thread>              
#include <mutex>                
#include <condition_variable>
#include <chrono>
#include"render_commend.h"
#include"const_define.h"

namespace gxo {
	class CommandPipe
	{
	public:
		CommandPipe()
		{
	
		}

		~CommandPipe()
		{
		}
		bool quit_sign = false;
		bool quit_succ = false;
		void quit() {
			quit_sign = true;
			cv.notify_all();
			while (quit_succ)
			{
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				break;
			}
		}

		void push(RenderCommandPtr rcmd) {
			while (true)
			{
				auto succ = command_queue.push([&](RenderCommandPtr* cmd) {
					*cmd = rcmd;
				});
				if (succ) {
					cv.notify_all();
					break;
				}
				else {
					std::unique_lock <std::mutex> lck(lock);
					cv.wait(lck);
				}
			}
		}


		void process(std::function<void(RenderCommandPtr)> deal) {
			while (true) {
				if (quit_sign)
				{
					break;
				}

				auto succ = command_queue.pop([&](RenderCommandPtr* cmd) {
					deal(*cmd);
				});

				if (succ) {
					cv.notify_all();
				}
				else {
					std::unique_lock <std::mutex> lck(lock);
					cv.wait(lck);
				}
			}
			quit_succ = true;
		}

	private:
		std::mutex lock;
		std::condition_variable cv;
		CircleQueue<RenderCommandPtr, RENDER_COMMAND_QUEUE_SIZE> command_queue;
	};

}
#endif
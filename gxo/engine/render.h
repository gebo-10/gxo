#ifndef GXO_RENDERER_H
#define GXO_RENDERER_H
#include"render_commend.h"
#include"circle_queue.h"
#include"pipeline.h"
#include <thread>              
#include <mutex>                
#include <condition_variable> 
#include"gpu.h"


struct NVGcontext;
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


		NVGcontext* vg;

		Render():stop(false),wait(false){}

		void init();

		void init_vg();

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


	public:
		std::map<RenderCommandType, CallablePtr> function;
		bool register_cmd(RenderCommandType type, std::function<void(void)> any_fun) {

			if (function.find(type) != function.end()) {
				error("register same render command");
				assert(false);
			}

			CallObject<void>* new_call = new CallObject<void>;
			new_call->fun = any_fun;
			function[type] = CallablePtr(new_call);
			return true;
		}

		template <typename... Args>
		bool register_cmd(RenderCommandType type, std::function<void(Args...)> any_fun) {

			if (function.find(type) != function.end()) {
				error("register same render command");
				assert(false);
			}

			CallObject<Args...>* new_call = new CallObject<Args...>;
			new_call->fun = any_fun;
			function[type] = CallablePtr(new_call);
			return true;
		}

		void gen_params(Params& params) { return; }
		template <class T, class... Args>
		void gen_params(Params& params, T head, Args... rest) {
			params.push_param(head);
			gen_params(params, rest...);
		}

		void rcmd(RenderCommandType type) {
			auto cmd = std::make_shared<RenderCommand>(type);
			push_command(cmd);
		}
		template<typename... Args>
		void rcmd(RenderCommandType type, Args... args) {
			auto cmd = std::make_shared<RenderCommand>(type);
			gen_params(cmd->params, args...);
			push_command(cmd);
		}

		void deal_cmd(RenderCommandPtr cmd) {
			RenderCommandType type = cmd->type;

			auto itr = function.find(type);
			if (itr == function.end()) return;

			CallablePtr call = function[type];
			(*call)(cmd->params);
		}



	public:
		void register_all_cmd();
	public:


	};
}
#endif
#ifndef GXO_RENDERER_H
#define GXO_RENDERER_H
#include<cassert>
#include"command_pipe.h"
#include"pipeline.h"
#include"gpu.h"


struct NVGcontext;
namespace gxo {
	
	class Render
	{
	public:
		bool stop;
		CommandPipe command_pipe;
		std::thread render_thread;

		GPU gpu;

		std::stack<PipelinePtr> pipeline_stack;
		PipelinePtr pipeline=nullptr;


		NVGcontext* vg;

		Render():stop(false){}

		void init();

		void init_vg();

		void push_command(RenderCommandPtr rcmd) {
			command_pipe.push(rcmd);
		}

		void quit() {
			stop = true;
		}

	private:
		void register_all_cmd();
		void process();
		static void thread_main(Render* render) {
			render->process();
		}

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
	
	};
}
#endif
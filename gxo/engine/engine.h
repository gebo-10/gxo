#ifndef _GXO_ENGINE_H
#define _GXO_ENGINE_H
#include"config.h"

#include"async_system.h"
#include"render_system.h"
#include"event_system.h"
#include"tree_manager.h"
#include"profiler.h"
#include"gxo_log.h"
#include"application.h"
#include"window_system.h"
namespace gxo {
	class Engine
	{
	public:
		enum EngineStatus
		{
			ES_STOP = 0,
			ES_RUN,
			ES_PAUSE,
		};
		int width;
		int height;
		EngineStatus status;
		//uint32 last_tick;
		WindowSystem window_system;
		AsyncSystem async_system;

		RenderSystem render_system;
		EventSystem event_system;
		
		TreeManager tree_manager;

		Application* app;

		static Engine& instacne() {
			static Engine engine;
			return engine;
		}
		Engine()
		{
			app = gxo_create_application();
		}
		~Engine()
		{

		}
		void init() {
			Config::instacne().init();
			Profiler::instacne().init();
			window_system.init();
			event_system.init();
			async_system.init();
			render_system.init();

			init_env();

			app->on_config();
			app->on_project_loaded();

			return;
		}

		void init_env();

		bool start() {
			async_system.loop();
			return true;
		}
		void pause();
		void resume();
		void stop();

		void update() {
			//TODO 性能检测 benchmarking 
			if (!Profiler::instacne().fps()) return;
			window_system.update();
			event_system.update();

			app->on_update();

			render_system.update();
		}

		//void on_resize(int width,int height) {} 写进event系统 事件传输

		void clear(){
		
		}
	private:
		
	};

}

#endif
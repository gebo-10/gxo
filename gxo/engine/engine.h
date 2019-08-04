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
#include"resource_manager.h"
#include"file_system.h"
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
		
		RenderSystem render_system;
		
		AsyncSystem async_system;
		EventSystem event_system;
		
		FileSystem	file_system;
		TreeManager tree_manager;
		
		ResourceManager resource_manager;

		Application* app;
		
		static Engine& instacne() {
			static Engine engine;
			return engine;
		}
		Engine()
		{
			app = gxo_create_application();
		}

		void init() {
			init_env();
			Config::instacne().init();
			Profiler::instacne().init();
			file_system.init();
			window_system.init();
			event_system.init();
			async_system.init();
			render_system.init();
			
			resource_manager.init();
			tree_manager.init();

			app->on_config();
			app->on_project_loaded();

			return;
		}

		void init_env();

		bool start() {
			status = ES_RUN;
			//排版第一次 window的第一个resize 没捉到
			auto rect = Rect(0, 0, Config::instacne().data["width"], Config::instacne().data["height"]);
			tree_manager.screen.on_layout(rect);

			async_system.loop();
			return true;
		}
		void pause();
		void resume();
		void stop() {
			status = ES_STOP;
			render_system.stop();

			window_system.stop();
			info("Engine: Stop");
		}

		void update() {
			if (status == ES_STOP)
			{
				async_system.stop();
				return;
			}

			//TODO 性能检测 benchmarking 
			if (!Profiler::instacne().fps()) return;
			window_system.update();
			event_system.update();

			app->on_update();

			tree_manager.update();
			render_system.update();
		}

		//void on_resize(int width,int height) {} 写进event系统 事件传输

		void clear(){
		
		}
	private:
		
	};

}

#endif
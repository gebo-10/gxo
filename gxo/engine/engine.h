#ifndef _GXO_ENGINE_H
#define _GXO_ENGINE_H
#include"config.h"
#include"window_system.h"
#include"async_system.h"
#include"render_system.h"
#include"event_system.h"
#include"tree_manager.h"
#include"profiler.h"
#include"log.h"

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

		static Engine& instacne() {
			static Engine engine;
			return engine;
		}
		Engine()
		{
			
		}
		~Engine()
		{

		}
		bool init() {
			Config::instacne().init();
			Profiler::instacne().init();
			window_system.init();
			event_system.init();
			async_system.init();
			return true;
		}

		bool start() {
			async_system.loop();
			return true;
		}
		void pause();
		void resume();
		void stop();

		void update() {
			//TODO 帧率控制 根据配置文件
			//TODO 性能检测 benchmarking 
			if (!Profiler::instacne().fps()) return;
			window_system.update();
			event_system.update();
			render_system.update();
		}

		void clear(){
		
		}
	private:
		
	};

}

#endif
#ifndef _GXO_ENGINE_H
#define _GXO_ENGINE_H
#include"config.h"
#include"window_system.h"
#include"async_system.h"
#include"render_system.h"
#include "ui_root.h"
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
		Config config;
		EngineStatus status;
		//uint32 last_tick;
		WindowSystem window_system;
		AsyncSystem async_system;

		RenderSystem render_system;
		UiRoot tree;

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
			config.init();
			window_system.init();
			async_system.init();
			return true;
		}

		bool init(char * name, int width, int height);
		bool run() {
			async_system.loop();
			return true;
		}
		void pause();
		void resume();
		void stop();

		void update() {
			//TODO 帧率控制 根据配置文件
			//TODO 性能检测 benchmarking 
			window_system.update();
			render_system.update();
		}

		void clear(){
		
		}
	private:
		
	};

}

#endif
#ifndef _GXO_ENGINE_H
#define _GXO_ENGINE_H
#include"window_system.h"
#include"async_system.h"
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
			window_system.init();
			async_system.init();
			async_system.register_update(std::bind(&Engine::update,this));
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
			window_system.update();
		}

		void clear(){
		
		}
	private:
		
	};

}

#endif
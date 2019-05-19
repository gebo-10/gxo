#ifndef _GXO_ENGINE_H
#define _GXO_ENGINE_H
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
		static Engine& instacne() {
			static Engine ins;
			return ins;
		}

		~Engine()
		{

		}
		bool init() {
			window_system.init();
			return true;
		}

		bool init(char * name, int width, int height);
		bool run();
		void pause();
		void resume();
		void stop();

		void update();
	private:
		Engine()
		{
			
		}
	};

}

#endif
#ifndef _GXO_PROFILER_H
#define _GXO_PROFILER_H
#include"uv.h"
#include <chrono>
#include"gxo_log.h"
namespace gxo {
	class Profiler
	{
	public:
		int fps_limit;
		double interval;
		int fps_num;
		uint64_t last_time;

		static Profiler& instacne() {
			static Profiler profiler;
			return profiler;
		}
		
		Profiler() :fps_limit(0),interval(0), last_time(0){}
		~Profiler() {}
		void init() {
			last_time= uv_hrtime();
			fps_limit = Config::instacne().data["max_fps"];
			if(fps_limit != 0)
				interval = 1000000000.0f / fps_limit;
			return;
		}
		bool fps() {
			auto now = uv_hrtime();
			auto elapsed = now - last_time;
			int fps=(int) (1000000000.0f / elapsed +1);

			if (elapsed > interval) {
				last_time = now;
				//info("fps: {}", fps);
				fps_num = fps;
				return true;
			}
			auto micro =(long long) ( (interval - elapsed)/1050.0f);
			std::this_thread::sleep_for(std::chrono::microseconds(micro));
			return false;
		} 
	private:

	};

}
#endif
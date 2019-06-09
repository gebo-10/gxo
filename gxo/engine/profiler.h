#ifndef _GXO_PROFILER_H
#define _GXO_PROFILER_H
#include"uv.h"
#include <chrono>
#include"log.h"
namespace gxo {
	class Profiler
	{
	public:
		int fps_limit;
		double interval;

		uint64_t last_time;

		static Profiler& instacne() {
			static Profiler profiler;
			return profiler;
		}
		
		Profiler() :fps_limit(0),interval(0), last_time(0){}
		~Profiler() {}
		bool init() {
			last_time= uv_hrtime();
			fps_limit = Config::instacne().data["max_fps"];
			if(fps_limit != 0)
				interval = 1000000000.0 / fps_limit;
			return true;
		}
		bool fps() {
			auto now = uv_hrtime();
			int fps=1000000000.0 / (now - last_time)+1;

			if (now - last_time > interval) {
				last_time = now;
				info("fps: {}", fps);
				return true;
			}

			return false;
		}
	private:

	};

}
#endif
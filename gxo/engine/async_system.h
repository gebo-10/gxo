#ifndef _GXO_ASYNC_SYSTEM_H
#define _GXO_ASYNC_SYSTEM_H
#include"uv.h"
#include<functional>
#include<iostream>
namespace gxo {
	class AsyncSystem
	{
	public:
		uv_idle_t idler;
		AsyncSystem()
		{
		}

		~AsyncSystem()
		{
		}

		void init() {
			idler.data = this;
			uv_idle_init(uv_default_loop(), &idler);
			uv_idle_start(&idler, idle);
			return;
		}
		void loop() {
			uv_run(uv_default_loop(), UV_RUN_DEFAULT);
			uv_loop_close(uv_default_loop());
		}
		//void destory() {
		//	uv_idle_stop(handle);
		//}

		static void idle(uv_idle_t* handle);

	};

}

#endif
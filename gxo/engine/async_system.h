#ifndef _GXO_ASYNC_SYSTEM_H
#define _GXO_ASYNC_SYSTEM_H
#include"uv.h"
#include<functional>
namespace gxo {
	class AsyncSystem
	{
	public:
		uv_idle_t idler;
		std::function<void(void)> update;
		AsyncSystem()
		{
		}

		~AsyncSystem()
		{
		}

		bool init() {
			idler.data = this;
			uv_idle_init(uv_default_loop(), &idler);
			uv_idle_start(&idler, idle);
			return true;
		}
		void loop() {
			uv_run(uv_default_loop(), UV_RUN_DEFAULT);
			uv_loop_close(uv_default_loop());
		}
		//void destory() {
		//	uv_idle_stop(handle);
		//}
		void register_update(std::function<void(void)> update) {
			this->update = update;
		}
		static void idle(uv_idle_t* handle) {
				//uv_idle_stop(handle);
			AsyncSystem* as = (AsyncSystem*)handle->data;
			as->update();
			std::cout << "hah" << std::endl;
		}

	};

}

#endif
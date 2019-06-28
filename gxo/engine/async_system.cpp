#include"async_system.h"
#include"engine.h"
#include"gxo_log.h"

void gxo::AsyncSystem::idle(uv_idle_t* handle) {
	//uv_idle_stop(handle);
	AsyncSystem* as = (AsyncSystem*)handle->data;
	Engine::instacne().update();
	//std::cout << "hah" << std::endl;
	//error("Hello, {}!", "World");
}
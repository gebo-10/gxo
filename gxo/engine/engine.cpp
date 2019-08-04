#include"engine.h"
#include"env.h"
gxo::Environment env;
void gxo::Engine::init_env()
{
	env.engine = this;
	env.render = &render_system.render;
	env.resource = &resource_manager;
	env.event = &event_system;
}

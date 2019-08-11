#include "env.h"

ivec2 gxo::Environment::get_screen_size()
{
	return engine->tree_manager.get_screen()->size;
}

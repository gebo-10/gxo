#ifndef GXO_EVN_H
#define GXO_EVN_H
//Can not use before system init
#include"engine.h"
namespace gxo {
	class Environment
	{
	public:
		Engine* engine=nullptr;
		Render* render = nullptr;
		ResourceManager* resource = nullptr;
		EventSystem* event = nullptr;

		ivec2 get_screen_size();
	};
}
extern "C" gxo::Environment env;
#endif
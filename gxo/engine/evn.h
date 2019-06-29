#ifndef GXO_EVN_H
#define GXO_EVN_H
#include"engine.h"
namespace gxo {
	class Environment
	{
	public:

		Engine* engine;
		Render* render;
	};
	extern "C" Environment env;
}

#endif
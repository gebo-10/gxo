#ifndef _GXO_RENDER_SYSTEM_H
#define _GXO_RENDER_SYSTEM_H
#include"gpu.h"
#include"color.h"
#include"render_engine.h"
namespace gxo {
	class RenderSystem
	{
	public:
		GPU gpu;
		Renderer renderer;
		RenderSystem()
		{
		}

		~RenderSystem()
		{
			
		}

		void init();

		void update();
		
	private:

	};

}
#endif
#ifndef _GXO_RENDER_SYSTEM_H
#define _GXO_RENDER_SYSTEM_H
#include"gpu.h"
namespace gxo {
	class RenderSystem
	{
	public:
		GPU gpu;
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
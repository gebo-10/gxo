#ifndef _GXO_RENDER_SYSTEM_H
#define _GXO_RENDER_SYSTEM_H
#include"gxo_color.h"
#include"render.h"
namespace gxo {
	class RenderSystem
	{
	public:
		Render render;

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
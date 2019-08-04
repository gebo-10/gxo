#ifndef ENGINE_UI_SCREEN_H
#define ENGINE_UI_SCREEN_H
#include<vector>
#include"ui_node.h"
#include"gxo_color.h"

namespace gxo {
	class UiScreen :public UiNode
	{
	public:
		UiScreen();
		void init();
		virtual void on_render_begin();
		virtual void on_rendre_end();

		void on_size(int width, int height);
	private:

	};
}
#endif 
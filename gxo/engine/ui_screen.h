#ifndef ENGINE_UI_SCREEN_H
#define ENGINE_UI_SCREEN_H
#include<vector>
#include"ui_node.h"
#include"gxo_color.h"

namespace gxo {
	class UiScreen :public UiNode
	{
	public:
		UiScreen() {
			add_property(CLEAR_COLOR, color_darkolivegreen);
			
		}

		virtual void on_render_begin();
		virtual void on_rendre_end();

		void set_size() {
		}
	private:

	};
}
#endif 
#ifndef ENGINE_UI_SCREEN_H
#define ENGINE_UI_SCREEN_H
#include<vector>
#include"ui_node.h"
#include"engine.h"
namespace gxo {
	class UiScreen :public UiNode
	{
	public:
		UiScreen() {
			add_property(CLEAR_COLOR, color_darkolivegreen);
			
		}

		//bool on_render() {

		//	auto color = get<Color>(CLEAR_COLOR);

		//	//todo 转化为命令或接口 交给gpu模块 
		//	glClearColor(color.r, color.g, color.b, color.a);
		//	glClear(GL_COLOR_BUFFER_BIT);

		//	return true;
		//}


		void set_size() {
		}
	private:

	};
}
#endif 
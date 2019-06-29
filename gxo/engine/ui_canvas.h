#ifndef GXO_ENGINE_UI_CANVAS_H
#define GXO_ENGINE_UI_CANVAS_H
#include"ui_node.h"
#include"render_target.h"
namespace gxo {
	class UiCanvas :public UiNode
	{
	public:
		RenderTargetPtr render_target;

		UiCanvas() {
		
		}

	private:

	};
}
#endif
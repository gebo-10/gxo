#ifndef GXO_ENGINE_UI_VIEW_H
#define GXO_ENGINE_UI_VIEW_H
#include"ui_node.h"
#include"render_target.h"

namespace gxo {
	class UiView :public UiNode
	{
	public:
		RenderTargetPtr render_target;
		
		UiView() {
			
		}

	private:

	};
}
#endif 
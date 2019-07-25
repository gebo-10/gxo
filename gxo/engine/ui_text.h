#ifndef GXO_UI_TEXT_H
#define GXO_UI_TEXT_H
#include"ui_node.h"
#include "gxo_font.h"
namespace gxo {
	class UiText :public UiNode
	{
	public:
		Font f;
		TexturePtr text_texture;
		UiText() {
			f.Init();
			f.SetFont("hah");
			f.SetFontSize(40);
			text_texture = f.GetStrTexture("hah");
		}

		void on_render_begin();
	private:

	};
}
#endif
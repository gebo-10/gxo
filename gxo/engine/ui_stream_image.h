#ifndef GXO_UI_FRAME_IMAGE_H
#define GXO_UI_FRAME_IMAGE_H
#include"ui_node.h"
#include"texture.h"
namespace gxo {
	class UiStreamImage :public UiNode
	{
	public:
		std::vector<TexturePtr> texture;
		float interval;
		UiStreamImage();

		void on_render_begin();
	private:

	};
}
#endif
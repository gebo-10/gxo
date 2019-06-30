#include "ui_image.h"
#include"env.h"
void gxo::UiImage::on_render_begin()
{
	string id = "main/texture/1";
	auto tex = env.engine->resource_manager.get<Texture>(id);
	//env.render->rcmd(RCMD_IMAGE, tex, Rect(0, 0, 640, 510));
}

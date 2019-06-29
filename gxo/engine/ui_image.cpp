#include "ui_image.h"
#include"env.h"
void gxo::UiImage::on_render_begin()
{
	string path="1.jpeg";
	env.render->rcmd(RCMD_IMAGE, path, Rect(0, 0, 640, 510));
}

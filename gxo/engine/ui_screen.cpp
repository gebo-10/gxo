#include "ui_screen.h"
#include"evn.h"
using namespace gxo;
void gxo::UiScreen::on_render_begin()
{
	env.render->rcmd(RCMD_CLEAR, color_black);
	env.render->rcmd(RCMD_UI_BEGIN);
	draw_rect();
}

void gxo::UiScreen::on_rendre_end()
{
	env.render->rcmd(RCMD_UI_END);
}

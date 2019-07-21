#include "ui_screen.h"
#include"env.h"
using namespace gxo;
void gxo::UiScreen::on_render_begin()
{
	//env.render->rcmd(RCMD_CLEAR, color_black);
	//env.render->rcmd(RCMD_UI_BEGIN);
	//draw_rect();
	auto color= get<Color>(CLEAR_COLOR);
	env.render->rcmd(RCMD_CLEAR, color);
}

void gxo::UiScreen::on_rendre_end()
{
	//env.render->rcmd(RCMD_UI_END);
}

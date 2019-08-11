#include "ui_screen.h"
#include"env.h"
using namespace gxo;

gxo::UiScreen::UiScreen()
{
	add_property(CLEAR_COLOR, color_darkolivegreen);
	
}

void gxo::UiScreen::init()
{
	env.event->add_event_process(GXO_EVENT_RESIZE, [this](Event* event) {
		on_size(event->resize.width, event->resize.height);
	});
}

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

void gxo::UiScreen::on_size(int width, int height)
{

	auto rect = Rect(0, 0, width, height);
	on_layout(rect);
	size.x = width;
	size.y = height;
}

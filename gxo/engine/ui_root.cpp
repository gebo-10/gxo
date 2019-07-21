#include "ui_root.h"
#include"env.h"
using namespace gxo;
void UiRoot::on_render_begin()
{
	env.render->rcmd(RCMD_SET_PIPELINE, pipeline);
}

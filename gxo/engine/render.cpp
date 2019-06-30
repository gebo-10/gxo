#include "render.h"
#include"engine.h"
#include"vg.h"

void gxo::Render::init()
{
	register_all_cmd();
	render_thread = std::thread(thread_main, this);
}

void gxo::Render::init_vg()
{
	vg = nvgCreateGL3(NVG_STENCIL_STROKES | NVG_DEBUG);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_SCISSOR_TEST);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glStencilMask(0xffffffff);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	glStencilFunc(GL_ALWAYS, 0, 0xffffffff);
	glActiveTexture(GL_TEXTURE0);

	auto font = nvgCreateFont(vg, "sans", "Roboto-Regular.ttf");
	if (font == -1) {
		error("Could not add font italic.\n");
	}

}

//process 在另一个线程 
void gxo::Render::process()
{
	Engine::instacne().window_system.make_current();
	gpu.init();
	gpu.log_device_info();

	init_vg();

	RenderCommandPtr cmd;
	while (!stop)
	{
		cmd = pop_command();
		if (cmd != nullptr) {
			deal_cmd(cmd);
		}
		else {
			std::unique_lock <std::mutex> lck(lock);
			wait = true;
			cv.wait(lck);
			
		}
	}
}

void gxo::Render::register_all_cmd()
{
	Engine& engine = Engine::instacne();

	register_cmd(RCMD_SWAPBUFFER, [&]() {
		engine.window_system.swap_buffer();
	});

	register_cmd<Color>(RCMD_CLEAR, [&](Color color) {
		glClearColor(color.r, color.g, color.b, color.a);
		glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	});

	register_cmd(RCMD_UI_BEGIN, [&]() {
		nvgBeginFrame(vg, 500, 500, 1.0);
		});

	register_cmd(RCMD_UI_END, [&]() {
		nvgEndFrame(vg);
		});

	register_cmd<Rect>(RCMD_RECT, [&](Rect rect) {
		nvgBeginPath(vg);
		nvgRect(vg, rect.x, rect.y, rect.width, rect.height);
		//nvgFillColor(vg, nvgRGBA(size.y, position.x, size.x, 255));
		//nvgFill(vg);
		nvgStrokeColor(vg, nvgRGBA(234, 60, 17, 255));
		nvgStroke(vg);
		});
	register_cmd<string, Rect>(RCMD_TEXT, [&](string text, Rect rect) {
		

		NVG_NOTUSED(rect.width);

		nvgFontSize(vg, 40.0f);
		nvgFontFace(vg, "sans");
		nvgFillColor(vg, nvgRGBA(0, 255, 255, 128));

		nvgTextAlign(vg, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);
		nvgText(vg, rect.x, rect.y + rect.height * 0.5f, text.c_str(), NULL);

		nvgBeginPath(vg);
		nvgRect(vg, rect.x, rect.y, rect.width, rect.height);
		//nvgFillColor(vg, nvgRGBA(size.y, position.x, size.x, 255));
		//nvgFill(vg);
		nvgStrokeColor(vg, nvgRGBA(234, 60, 17, 255));
		nvgStroke(vg);
		});


	register_cmd<TexturePtr, Rect>(RCMD_IMAGE, [&](TexturePtr tex, Rect rect) {
		//auto image = nvgCreateImage(vg, text.c_str(), 0);
		auto image = nvgCreateImageMem(vg, 0, tex->ram.data, tex->ram.size);
		if (image == 0) {
			error("Could not load image\n");
		}

		auto imgPaint = nvgImagePattern(vg, rect.x, rect.y, rect.width, rect.height, 0.0f / 180.0f * NVG_PI, image, 1.0f);
		nvgBeginPath(vg);
		nvgRect(vg, rect.x, rect.y, rect.width, rect.height);
		nvgFillPaint(vg, imgPaint);
		nvgFill(vg);

;		//nvgDeleteImage(vg, image);
		});
}

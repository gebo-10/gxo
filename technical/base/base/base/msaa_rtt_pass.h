#ifndef MSAA_RTT_PASS_H
#define MSAA_RTT_PASS_H
#include "render_target.h"
#include "material.h"
#include "camera.h"
#include "texture_plane_model.h"
#include "screen_target.h"
#include "msaa_render_target.h"
class MsaaRttPass
{
public:
	MsaaRenderTargetPtr msaa_render_target;
	RenderTargetPtr render_target;
	std::function<void()> child_pass;
	MsaaRttPass(int width, int height, std::function<void()> pass) {
		render_target = make(RenderTarget, width, height);
		msaa_render_target = make(MsaaRenderTarget, width, height);
		child_pass = pass;
	}

	MsaaRttPass(int width, int height,int attachment_count, int format, std::function<void()> pass) {
		render_target = make(RenderTarget, width, height, attachment_count, format);
		msaa_render_target = make(MsaaRenderTarget, width, height, attachment_count, format);
		child_pass = pass;
	}

	virtual void process() {
		msaa_render_target->bind();
		child_pass();
		msaa_render_target->unbind();

		glBindFramebuffer(GL_READ_FRAMEBUFFER, msaa_render_target->gpu_id);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, render_target->gpu_id);

		for (unsigned int i=0;i< render_target->textures.size();i++)
		{
			glReadBuffer(GL_COLOR_ATTACHMENT0 + i);
			glDrawBuffer(GL_COLOR_ATTACHMENT0 + i);
			glBlitFramebuffer(0, 0, msaa_render_target->width, msaa_render_target->height, 0, 0, render_target->width, render_target->height, GL_COLOR_BUFFER_BIT, GL_NEAREST);

		}



		
	}

	TexturePtr get_texture(int i=0) {
		return render_target->get_texture(i);
	}

	void set_pass(std::function<void()> pass) {
		child_pass = pass;
	}

	void set_target(RenderTargetPtr t) {
	}

	void set_source(TexturePtr s) {
		
	}

};
REG(MsaaRttPass)
#endif

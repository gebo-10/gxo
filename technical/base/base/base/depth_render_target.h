#ifndef DEPTH_RENDER_TARGET_H
#define DEPTH_RENDER_TARGET_H
#include "render_target.h"
#include "msaa_texture.h"
class DepthRenderTarget 
{
public:
	GPUID gpu_id = 0;
	int width;
	int height;
	TexturePtr depth_texture;

	DepthRenderTarget(int width, int height)
	{
		glGenFramebuffers(1, &gpu_id);
		depth_texture = make(Texture, width, height, nullptr, GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT);
		glBindFramebuffer(GL_FRAMEBUFFER, gpu_id);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_texture->gpu_id, 0);
		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	}

	void  bind() {
		glBindFramebuffer(GL_FRAMEBUFFER, gpu_id);;
	}
	void unbind() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	TexturePtr get_texture() {
		return depth_texture;
	}

};
REG(DepthRenderTarget)

#endif
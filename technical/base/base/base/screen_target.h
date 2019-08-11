#ifndef SCREEEN_TARGET_H
#define SCREEEN_TARGET_H
#include "render_target.h"
class ScreenTarget :public RenderTarget
{
public:
	ScreenTarget(int width, int height) :RenderTarget()
	{
		this->width = width;
		this->height = height;
		this->gpu_id = 0;

	}

	virtual void bind() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	virtual void unbind() {
	}

};

#endif

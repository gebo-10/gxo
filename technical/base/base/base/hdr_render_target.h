#ifndef HDR_RENDER_TARGET_H
#define HDR_RENDER_TARGET_H
#include "render_target.h"
class HdrRenderTarget :public RenderTarget
{
public:
	HdrRenderTarget(int width,int height,int attachment_count):RenderTarget(width,height,attachment_count,GL_RGB16F)
	{
	}

	

private:

};

#endif

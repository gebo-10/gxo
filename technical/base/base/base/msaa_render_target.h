#ifndef MSAA_RENDER_TARGET_H
#define MSAA_RENDER_TARGET_H
#include "render_target.h"
#include "msaa_texture.h"
class MsaaRenderTarget :public RenderTarget
{
public:
	MsaaRenderTarget(int width, int height, int attachment_count=1, int internal_format=GL_RGBA) 
	{
		for (unsigned int i = 0; i < attachment_count; i++)
		{
			auto color_texture0 = std::make_shared<MsaaTexture>(width, height,4, internal_format);
			//auto color_texture0 = std::make_shared<Texture>(width, height, nullptr, GL_RGBA, internal_format);
			textures.push_back(color_texture0);
		}
		create(width, height);
	}



private:

};
REG(MsaaRenderTarget)

#endif

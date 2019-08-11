#ifndef HDR_TEXTURE_H
#define HDR_TEXTURE_H
#include "texture.h"
class HdrTexture :public Texture
{
public:
	HdrTexture(int width, int height):Texture(width,height,nullptr,GL_RGBA, GL_RGB16F)
	{

	}

};

#endif

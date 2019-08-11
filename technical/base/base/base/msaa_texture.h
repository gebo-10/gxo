#ifndef MSAA_TEXTURE_H
#define MSAA_TEXTURE_H
#include "texture.h"
class MsaaTexture :public Texture
{
public:
	int samples;
	MsaaTexture(int width, int height, int samples=4, int internal_format = GL_RGBA) :
		Texture( width, height,  nullptr, GL_RGBA, internal_format)
	{
		this->samples = samples;
		type = GL_TEXTURE_2D_MULTISAMPLE;
		create(width, height, nullptr, format, internal_format);
	}

	virtual bool create(int width, int height, void* data, int format, int internal_format) {
		this->format = format;
		this->width = width;
		this->height = height;

		glGenTextures(1, &gpu_id);
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, gpu_id);
		glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, internal_format, width, height, GL_TRUE);
		
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		//glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
		return true;
	}

private:

};


#endif
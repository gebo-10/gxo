#ifndef _GXO_TEXTURE_H
#define _GXO_TEXTURE_H
#include"gpu.h"
#include"resource.h"
namespace gxo {
	class Texture :public Resource
	{
	public:
		int width;
		int height;
		int warp_mode;
		int format;
	public:
		Texture()
		{
		}

		~Texture()
		{
		}
		virtual void on_load() {

		}

		void load_to_gpu() {
			glGenTextures(1, &gpu_id);
			glBindTexture(GL_TEXTURE_2D, gpu_id);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, ram.data);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		}
		

	private:

	};
	typedef shared_ptr<Texture> TexturePtr;
}
#endif
#ifndef GXO_GPU_TEXTURE_H
#define GXO_GPU_TEXTURE_H
#include <vector>
#include <cassert>
#include "core_base.h"
#include "gpu_buffer.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "mmap.h"
	class Texture
	{
	public:
		int type=GL_TEXTURE_2D;
		GPUID gpu_id=-1;
		int format;
		int width;
		int height;

		Texture(int width, int height, void* data, int format, int internal_format= GL_RGBA) {
			create(width, height, data, format, internal_format);
		}

		Texture(string_view filename) 
		{
			Mmap tex(filename);
			int w, h, n;
			stbi_set_flip_vertically_on_load(true);
			auto data = stbi_load_from_memory((byte*)tex.memery, tex.filesize, &w, &h, &n, 0);
			int size = w * h * n;
			//int format;
			if (n == 3) {
				format = GL_RGB;
			}
			else if (n == 4) {
				format = GL_RGBA;
			}
			create(w, h, data, format, GL_RGBA);
		}

		~Texture()
		{
			glDeleteTextures(1, &gpu_id);
		}
		virtual bool create(int width, int height, void* data, int format, int internal_format) {
			this->format = format;
			this->width = width;
			this->height = height;

			glGenTextures(1, &gpu_id);
			glBindTexture(GL_TEXTURE_2D, gpu_id);
			glTexImage2D(GL_TEXTURE_2D, 0, internal_format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			return true;
		}
		void update(void* data) {

		}

		void bind(int index) {
			//glEnable(GL_TEXTURE_2D);
			glActiveTexture(GL_TEXTURE0 + index);
			glBindTexture(type, gpu_id);
		}
		void unbind(void) {
			glBindTexture(type, 0);
		}

		void destroy() {
			glDeleteTextures(1, &gpu_id);
		}

		void set_param(int target, int name, int param) {
			glTexParameteri(target, name, param);
		}
	private:

	};
	typedef shared_ptr<Texture> TexturePtr;

#endif
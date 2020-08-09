#include"texture.h"

#define STB_IMAGE_IMPLEMENTATION

#include <stb_image.h>
Texture::Texture(string_view filename)
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
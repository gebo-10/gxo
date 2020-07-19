#ifndef GXO_VIDEO_METARIAL_H
#define GXO_VIDEO_METARIAL_H

#include"material.h"

class VideoMaterial :public Material
{
public:
	TexturePtr texture;
	VideoMaterial(int width, int hight) :Material(nullptr)
	{
		char* data = new char[width * hight * 4];
		texture =std::make_shared<Texture>(width, hight, data, GL_RGBA);
		delete data;

		string vs = "main/shader/video.vert.glsl";
		string	fs = "main/shader/video.frag.glsl";
		auto texture_shader = std::make_shared<Shader>(vs, fs);
		set_shader(texture_shader);
	}

	virtual void bind() {
		shader->bind();
		texture->bind(0);
		int location = glGetUniformLocation(shader->gpu_id, "texture0");

		glUniform1i(location, 0);
	}

	void update_frame(void * data) {
		texture->update(data);
	}

	TexturePtr get_texture() {
		return texture;
	}
};
typedef shared_ptr<VideoMaterial> VideoMaterialPtr;

#endif
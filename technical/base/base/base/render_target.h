#ifndef GXO_RENDER_TARGET_H
#define GXO_RENDER_TARGET_H
#include"core_base.h"
#include"texture.h"

class RenderTarget 
{
public:
	enum RboType {
		RBO_NONE,
		RBO_DEPTH16,
		RBO_DEPTH24,
		RBO_DEPTH_STENCIL,
	};
	RboType rbo_type;
	GPUID gpu_id=0;
	int width;
	int height;
	std::vector<GLenum> color_attachment;
	std::vector<TexturePtr> textures;
	
	GPUID depth_rbo_id=-1;

	int width_temp;
	int height_temp;

	RenderTarget(){}

	RenderTarget(int width, int height,int attachment_count=1,int internal_format=GL_RGBA) {

		// generate texture
		for (unsigned int i=0; i<attachment_count;i++)
		{
			auto color_texture0 = std::make_shared<Texture>(width, height, nullptr, GL_RGBA, internal_format);
			textures.push_back(color_texture0);
		}
		create(width, height);
	}
	RenderTarget(int width, int height,std::vector<TexturePtr> &textures) {
		this->textures = textures;
		create(width, height);
	}

	~RenderTarget() {
		release();
	}

	bool create(int width, int height) {
		
		return create_internal(width, height);
	}

	bool create_internal(int width, int height) {
		this->width = width;
		this->height = height;

		// generate frame buffer
		glGenFramebuffers(1, &gpu_id);
		glBindFramebuffer(GL_FRAMEBUFFER, gpu_id);

		
		for (unsigned int i=0;i<textures.size();i++)
		{
			color_attachment.push_back(GL_COLOR_ATTACHMENT0 + i);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0+i,
				textures[i]->type, textures[i]->gpu_id, 0);
		}
		


		glGenRenderbuffers(1, &depth_rbo_id);
		glBindRenderbuffer(GL_RENDERBUFFER, depth_rbo_id);
		//glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
		glRenderbufferStorageMultisample(GL_RENDERBUFFER,4, GL_DEPTH_COMPONENT, width, height);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth_rbo_id);

		// unbind
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
			error( "create framebuffer failed");
			return false;
		}
		
		return true;
	}

	virtual void bind() {
		glBindFramebuffer(GL_FRAMEBUFFER, gpu_id);
		glDrawBuffers(color_attachment.size(), color_attachment.data());
	}

	virtual void unbind() {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		//glDrawBuffers(1, color_attachment.data());
	}

	void draw(std::function<void()> draw_fun) {
		bind();
		draw_fun();
		unbind();
	}

	int get_width() {
		return width;
	}

	int get_height() {
		return height;
	}

	int get_id() {
		return gpu_id;
	}

	TexturePtr get_texture() {
		return textures[0];
	}
	TexturePtr get_texture(int index) {
		return textures[index];
	}

	void release() {
		if (gpu_id != -1) {
			glBindFramebuffer(GL_FRAMEBUFFER, gpu_id);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, 0, 0);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);

			glDeleteFramebuffers(1, &gpu_id);
		}

		width = 0;
		height = 0;
		gpu_id = -1;
		textures.clear();
	}
};
typedef shared_ptr<RenderTarget> RenderTargetPtr;

#endif
#ifndef GXO_GPU_TEXTURE_H
#define GXO_GPU_TEXTURE_H
#include <vector>
#include <cassert>
#include "gpu_api.h"
#include "gpu_type.h"
#include "gpu_buffer.h"
namespace gxo {
	class GPUTexture
	{
	public:
		GPUID gpu_id;
		GPUTexture():gpu_id(0)
		{
		}

		~GPUTexture()
		{
		}
		bool create(int width, int height, void * data) {
			glGenTextures(1, &gpu_id);
			glBindTexture(GL_TEXTURE_2D, gpu_id);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		}
		void update(void * data) {

		}

		void bind(int index) {
			//glEnable(GL_TEXTURE_2D);
			glActiveTexture(GL_TEXTURE0 + index);
			glBindTexture(GL_TEXTURE_2D, gpu_id);
		}
		void unbind(void) {
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		void destroy() {
			glDeleteTextures(1, &gpu_id);
		}

		void set_param(int target, int name, int param) {
			glTexParameteri(target, name, param);
		}
	private:

	};

}
#endif
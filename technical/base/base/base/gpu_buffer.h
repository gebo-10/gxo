#ifndef GXO_GPU_BUFFER_H
#define GXO_GPU_BUFFER_H

#include"core_base.h"
#include"buffer.h"

	class GPUBuffer {
	public:
		GPUID  gpu_id;
		uint32_t size;
		int type;
		int gpu_memery_hint;
		GPUBuffer() :gpu_id(-1), size(0) {}

		void create(Buffer& buffer, int type, int hint) {
			size = buffer.size;
			type = type;
			gpu_memery_hint = hint;
			glGenBuffers(1, &gpu_id);
			glBindBuffer(type, gpu_id);
			glBufferData(type, buffer.size, buffer.data, hint);
		}

		bool update_date(void* data)
		{
			glBindBuffer(type, gpu_id);
			glBufferSubData(type, 0, size, data);
			return true;
		}
		void bind() {
			glBindBuffer(type, gpu_id);
		}
		void destroy() {
			glDeleteBuffers(1, &gpu_id);
		}
	};


#endif
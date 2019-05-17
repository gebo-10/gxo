#ifndef _GXO_GPU_OBJECT_H
#define _GXO_GPU_OBJECT_H
#include <vector>
#include <assert.h>
#include "gpu_api.h"
namespace gxo {
	class GPUObject
	{
	public:
		GPUID gpu_id;
		std::vector<GPUBuffer> gpu_buffer;
	public:
		GPUObject():gpu_id(-1)
		{
		}

		~GPUObject()
		{
		}
		void bind(void) {
			assert(gpu_id != -1);
			glBindVertexArray(gpu_id);
		}
		void unbind(void) {
			glBindVertexArray(0);
		}
	};

}
#endif
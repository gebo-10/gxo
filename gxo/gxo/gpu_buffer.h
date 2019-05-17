#ifndef _GXO_GPU_BUFFER_H
#define _GXO_GPU_BUFFER_H
#include"base.h"
#include"gpu_type.h"
namespace gxo {
	struct GPUBuffer {
		GPUBuffer() :gpu_id(-1), size(0) {}
		GPUID  gpu_id;
		uint32_t size;
	};

	

}
#endif
#ifndef GXO_GPU_CONCEPT_H
#define GXO_GPU_CONCEPT_H
#include"gpu_type.h"
namespace gxo {
	enum CullFaceType {
		CULL_NULL,
		CULL_BACK,
		CULL_FRONT,
	};

	enum BlendMode {
		BLEND_NONE,
		BLEND_MIX,
		BLEND_PREBUILD,
	};



}
#endif
#ifndef GXO_GPU_TYPE_H
#define GXO_GPU_TYPE_H
namespace gxo {
	typedef unsigned int GPUID;
	enum GPUDataType {
		GPU_BYTE,
		GPU_SHORT,
		GPU_USHORT,
		GPU_INT,
		GPU_UINT,
		GPU_HALF_FLOAT,
		GPU_FLOAT,
		GPU_VEC2,
		GPU_VEC3,
		GPU_VEC4,
		GPU_MAT3,
		GPU_MAT4,
	};
	
}
#endif

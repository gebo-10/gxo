#ifndef _GXO_GPU_TYPE_H
#define _GXO_GPU_TYPE_H
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
	int gpu_type_size(GPUDataType type) {
		switch (type)
		{
		case gxo::GPU_BYTE:
			break;
		case gxo::GPU_SHORT:
			break;
		case gxo::GPU_USHORT:
			break;
		case gxo::GPU_INT:
			break;
		case gxo::GPU_UINT:
			break;
		case gxo::GPU_HALF_FLOAT:
			break;
		case gxo::GPU_FLOAT:
			break;
		case gxo::GPU_VEC2:
			break;
		case gxo::GPU_VEC3:
			break;
		case gxo::GPU_VEC4:
			break;
		case gxo::GPU_MAT3:
			break;
		case gxo::GPU_MAT4:
			break;
		default:
			break;
		}
	}
}
#endif

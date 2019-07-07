#include"gpu_type.h"
namespace gxo {
	std::map < GPUDataType, GPUDataTypeInfo > gpu_data_type_info = {
		{GPU_BYTE, GPUDataTypeInfo(GL_BYTE,1, 8) },
		{GPU_VEC3, GPUDataTypeInfo(GL_FLOAT, 3, 3 * sizeof(float))},
		{GPU_VEC2, GPUDataTypeInfo(GL_FLOAT, 2, 2 * sizeof(float))},
	};
}
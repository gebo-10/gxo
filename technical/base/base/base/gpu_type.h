#ifndef GXO_GPU_TYPE_H
#define GXO_GPU_TYPE_H
#include <stdexcept>
#include<map>
#include "core_base.h"

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
	GPU_SAMPLE2D,
};
struct GPUDataTypeInfo
{
	int type;
	int num;
	int size;
	GPUDataTypeInfo() {}
	GPUDataTypeInfo(int data_type, int data_num, int data_size) :type(data_type), num(data_num), size(data_size) {}
};
extern std::map < GPUDataType, GPUDataTypeInfo > gpu_data_type_info;

#endif

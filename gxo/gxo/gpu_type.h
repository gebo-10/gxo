#ifndef GXO_GPU_TYPE_H
#define GXO_GPU_TYPE_H
#include <stdexcept>
#include<map>
#include<gpu_api.h>
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
	//std::map < GPUDataType, { size type } > info;
	class GPUDataTypeInfo
	{
	public:
		int size;
		int type;

		GPUDataTypeInfo()
		{
			//info[GPU_BYTE] = GPUDataTypeInfo(1, GL_BYTE);
			//info[GPU_VEC3] = GPUDataTypeInfo(3, GL_FLOAT);
		}
		GPUDataTypeInfo(int data_size, int data_type):size(data_size),type(data_type)
		{
		}

		~GPUDataTypeInfo()
		{
		}
		static GPUDataTypeInfo get_size(GPUDataType type) {
			return info[type];
		}

		//template<GPUDataType T>
		//static GPUDataTypeInfo get_size() {
		//	std::logic_error("Undefine GPU data type!");
		//	return GPUDataTypeInfo();
		//}

		//template<>
		//static GPUDataTypeInfo get_size<GPU_BYTE>() {
		//	return GPUDataTypeInfo(1, GL_BYTE);
		//}

	private:
		
		static std::map<GPUDataType, GPUDataTypeInfo> info;
	};
	std::pair<GPUDataType, GPUDataTypeInfo> pairArray[] =
	{
		std::make_pair(GPU_BYTE,GPUDataTypeInfo(1, GL_BYTE)),
		std::make_pair(GPU_VEC3,GPUDataTypeInfo(3, GL_FLOAT)),
	};
	std::map<GPUDataType, GPUDataTypeInfo> GPUDataTypeInfo::info(pairArray, pairArray + sizeof(pairArray) / sizeof(pairArray[0]));
	
}
#endif

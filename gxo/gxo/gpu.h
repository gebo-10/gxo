#ifndef GXO_GPU_H
#define GXO_GPU_H
#include"gpu_header.h"
#include"gxo_log.h"

namespace gxo {
	class GPU
	{
	public:
		//map<UID, GPUOBJEC> GPUobject;
	public:
		GPU()
		{
		}

		~GPU()
		{
		}
		void init() {
			GLenum result = glewInit();
			if (result != GLEW_OK )
			{
				error("glewInit failed");
				abort();
			}
		}
		void log_device_info() {
			info("GL_VERSION: {}", glGetString(GL_VERSION));
			info("GL_VENDOR: {}", glGetString(GL_VENDOR));
			info("GL_RENDERER: {}", glGetString(GL_RENDERER));
			info("GLSL Version: {}", glGetString(GL_SHADING_LANGUAGE_VERSION));
		}


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
			return 0;
		}
	private:

	};
}
#endif
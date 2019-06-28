#ifndef _GXO_GPU_H
#define _GXO_GPU_H
#include <stdlib.h>
#define GLEW_STATIC
#include <GL/glew.h>
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
				info("");
				abort();
			}
		}
		void log_device_info() {
			info("GL_VERSION: {}", glGetString(GL_VERSION));
			info("GL_VENDOR: {}", glGetString(GL_VENDOR));
			info("GL_RENDERER: {}", glGetString(GL_RENDERER));
			info("GLSL Version: {}", glGetString(GL_SHADING_LANGUAGE_VERSION));
		}
	private:

	};
}
#endif
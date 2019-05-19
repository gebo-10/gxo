#ifndef _GXO_GPU_IMAGE_H
#define _GXO_GPU_IMAGE_H
#include <GL/glew.h>
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
		bool init() {
			GLenum err = glewInit();
			if (GLEW_OK != err)
			{
				//assert(true);
			}
		}
	private:

	};
}
#endif
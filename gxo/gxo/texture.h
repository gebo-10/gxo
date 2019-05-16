#ifndef _GXO_TEXTURE_H
#define _GXO_TEXTURE_H
#include"gpu.h"
#include"resource.h"
namespace gxo {
	class Texture :public Resource
	{
	public:
		GPUID gpu_id;
		int width;
		int height;
	public:
		Texture()
		{
		}

		~Texture()
		{
		}

	private:

	};

}
#endif
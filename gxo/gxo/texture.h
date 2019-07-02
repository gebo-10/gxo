#ifndef GXO_TEXTURE_H
#define GXO_TEXTURE_H
#include"gpu_header.h"
#include"resource.h"
namespace gxo {
	class Texture :public Resource
	{
	public:
		GPUTexture gpu_texture;
		int width;
		int height;
		int warp_mode;
		int format;
	public:
		Texture()
		{
		}

		~Texture()
		{
		}
		virtual void on_load() {

		}

		void load_to_gpu() {
			gpu_texture.create(width, height, ram.data);
		}
		

	private:

	};
	typedef shared_ptr<Texture> TexturePtr;
}
#endif
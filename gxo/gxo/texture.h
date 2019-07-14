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

		void gpu_load() override{
			gpu_texture.create(width, height, ram.data, format);
		}
		
		void use(int texture_index) {
			gpu_texture.use(texture_index);

		}
	private:

	};
	typedef shared_ptr<Texture> TexturePtr;
}
#endif
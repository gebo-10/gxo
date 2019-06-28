#ifndef GXO_RENDER_TARGET_H
#define GXO_RENDER_TARGET_H
#include"resource.h"
#include"texture.h"
#include"gxo_type.h"
namespace gxo {
	class RenderTarget: public Resource
	{
	public:
		enum RboType {
			RBO_NONE,
			RBO_DEPTH16,
			RBO_DEPTH24,
			RBO_DEPTH_STENCIL,
		};
		int id;
		int width;
		int height;
		//GpuView
		std::vector<Texture> textures;
		RboType rbo_type;
		int rbo_id;

	};
	typedef shared_ptr<RenderTarget> RenderTargetPtr;
}
#endif
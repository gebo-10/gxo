#ifndef GXO_METARIAL_H
#define GXO_METARIAL_H
#include"resource.h"
#include"shader.h"
namespace gxo {
	class Material :public Resource
	{
	public:
		ShaderPtr shader;
		std::vector<Uniform> uniforms;
		Material()
		{
		}

		~Material()
		{
		}

	private:

	};
	typedef std::shared_ptr<Material> MaterialPtr;
}
#endif
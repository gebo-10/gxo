#ifndef GXO_METARIAL_H
#define GXO_METARIAL_H
#include"gxo_math.h"
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
		void use() {
			shader->use();
		}
		void mvp(mat4 M, mat4 V, mat4 P) {

		}
	private:

	};
	typedef std::shared_ptr<Material> MaterialPtr;
}
#endif
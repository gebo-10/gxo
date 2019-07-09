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
			glUseProgram(shader->gpu_id);
			for (auto uniform: uniforms)
			{
				set_uniform(uniform);
			}
		}
		void mvp(mat4 M, mat4 V, mat4 P) {
			//mat4 m4 = std::any_cast<mat4>(uniform.value);
			//glUniformMatrix4fv(uniform.location, 1, false, &m4[0][0]);
		}

		void gpu_load() override {
			shader->gpu_load();
		}


		void set_uniform(Uniform uniform) {
			switch (uniform.data_type)
			{
			case gxo::GPU_BYTE:
				break;
			case gxo::GPU_SHORT:
				break;
			case gxo::GPU_USHORT:
				break;
			case gxo::GPU_INT:
				glUniform1i(uniform.location, std::any_cast<int>(uniform.value));
				break;
			case gxo::GPU_UINT:
				break;
			case gxo::GPU_HALF_FLOAT:
				break;
			case gxo::GPU_FLOAT:
				glUniform1f(uniform.location, std::any_cast<float>(uniform.value));
				break;
			case gxo::GPU_VEC2: {
				auto v2 = std::any_cast<vec2>(uniform.value);
				glUniform2f(uniform.location, v2.x,v2.y);
				break;
			}
			case gxo::GPU_VEC3: {
				auto v3 = std::any_cast<vec3>(uniform.value);
				glUniform3f(uniform.location, v3.x, v3.y, v3.z);
				break;
			}
			case gxo::GPU_VEC4: {
				auto v4 = std::any_cast<vec4>(uniform.value);
				glUniform4f(uniform.location, v4.x, v4.y, v4.z, v4.w);
				break;
			}
			case gxo::GPU_MAT3:
				mat3 m3 = std::any_cast<mat3>(uniform.value);
				glUniformMatrix4fv(uniform.location, 1, false, &m3[0][0]);
				break;
			case gxo::GPU_MAT4:{
				mat4 m4 = std::any_cast<mat4>(uniform.value);
				glUniformMatrix4fv(uniform.location, 1, false, &m4[0][0]);
				break;
			}
			default:
				break;
			}
		}
	private:

	};
	typedef std::shared_ptr<Material> MaterialPtr;
}
#endif
#ifndef GXO_METARIAL_H
#define GXO_METARIAL_H
#include"core_base.h"
#include"shader.h"
#include"texture.h"
#include "gpu_type.h"
#include <any>
	class Material 
	{
	public:
		ShaderPtr shader;

		Material(ShaderPtr pshader)
		{
			shader = pshader;
		}

		Material(string_view vs, string_view fs)
		{
			shader = std::make_shared<Shader>(vs, fs);
		}

		~Material()
		{
		}
		virtual void bind() {
			shader->bind();

		}

		void set_shader(ShaderPtr  shader) {
			this->shader = shader;
		}

		void mvp(mat4 M, mat4 V, mat4 P) {
			int location = glGetUniformLocation(shader->gpu_id, "M");
			glUniformMatrix4fv(location, 1, false, &M[0][0]);

			location = glGetUniformLocation(shader->gpu_id, "V");
			glUniformMatrix4fv(location, 1, false, &V[0][0]);

			location = glGetUniformLocation(shader->gpu_id, "P");
			glUniformMatrix4fv(location, 1, false, &P[0][0]);
		}

		void set_bone(float* bones, int size) {
			int location = glGetUniformLocation(shader->gpu_id, "bones");
			glUniformMatrix4fv(location, size, GL_TRUE, bones);
		}
		
	  void set_uniform(string_view key, GPUDataType data_type, std::any value) {
			bind();
			int location = glGetUniformLocation(shader->gpu_id, key.data());
			switch (data_type)
			{
			case GPU_BYTE:
				break;
			case GPU_SHORT:
				break;
			case GPU_USHORT:
				break;
			case GPU_INT:
				glUniform1i(location, std::any_cast<int>(value));
				break;
			case GPU_UINT:
				break;
			case GPU_HALF_FLOAT:
				break;
			case GPU_FLOAT:
				glUniform1f(location, std::any_cast<float>(value));
				break;
			case GPU_VEC2: {
				auto v2 = std::any_cast<vec2>(value);
				glUniform2f(location, v2.x, v2.y);
				break;
			}
			case GPU_VEC3: {
				auto v3 = std::any_cast<vec3>(value);
				glUniform3f(location, v3.x, v3.y, v3.z);
				break;
			}
			case GPU_VEC4: {
				auto v4 = std::any_cast<vec4>(value);
				glUniform4f(location, v4.x, v4.y, v4.z, v4.w);
				break;
			}
			case GPU_MAT3:
				mat3 m3 = std::any_cast<mat3>(value);
				glUniformMatrix4fv(location, 1, false, &m3[0][0]);
				break;
			case GPU_MAT4: {
				mat4 m4 = std::any_cast<mat4>(value);
				glUniformMatrix4fv(location, 1, false, &m4[0][0]);
				break;
			}
			case GPU_SAMPLE2D: {
				auto tex = std::any_cast<TexturePtr>(value);
				int texture_index = std::atoi(key.data()+7);
				tex->bind(texture_index);
				glUniform1i(location, texture_index);
				break;
			}
			default:
				break;
			}
		}

	};
	typedef shared_ptr<Material> MaterialPtr;

#endif
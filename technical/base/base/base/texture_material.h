#ifndef GXO_TEXTURE_METARIAL_H
#define GXO_TEXTURE_METARIAL_H

#include"material.h"

class TextureMaterial :public Material
{
public:
	TexturePtr texture;
	TextureMaterial(TexturePtr tex):Material(nullptr)
	{
		texture = tex;
		string vs = "main/shader/texture.vert.glsl";
		string	fs = "main/shader/texture.frag.glsl";
		auto texture_shader = std::make_shared<Shader>(vs, fs);
		set_shader(texture_shader);
	}

	TextureMaterial(string_view vs, string_view fs) :Material(vs, fs)
	{
	}


	~TextureMaterial()
	{
	}
	virtual void bind() {
		shader->bind();
		texture->bind(0);
		int location = glGetUniformLocation(shader->gpu_id, "texture0");
		
		glUniform1i(location, 0);
	}

	void set_texture(TexturePtr texture) {
		this->texture = texture;
	}

	/*  void upload_uniform(Uniform& uniform) {
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
				glUniform2f(uniform.location, v2.x, v2.y);
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
			case gxo::GPU_MAT4: {
				mat4 m4 = std::any_cast<mat4>(uniform.value);
				glUniformMatrix4fv(uniform.location, 1, false, &m4[0][0]);
				break;
			}
			case gxo::GPU_SAMPLE2D: {
				auto tex = std::any_cast<TexturePtr>(uniform.value);
				int texture_index = std::atoi(uniform.name.to_string().c_str());
				int location = glGetUniformLocation(shader->gpu_id, uniform.name.to_string().c_str());
				tex->bind()(texture_index);
				glUniform1i(location, texture_index);
				break;
			}
			default:
				break;
			}
		}*/
private:

};
typedef shared_ptr<TextureMaterial> TextureMaterialPtr;

#endif
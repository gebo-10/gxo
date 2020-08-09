#ifndef GXO_DEFERRED_LIGHTPASS_METARIAL_H
#define GXO_DEFERRED_LIGHTPASS_METARIAL_H

#include"material.h"

class DeferredLightPassMaterial :public Material
{
private:
	struct Light {
		vec3 Position;
		vec3 Color;
	};
	Light lights[32];
	vec3 view_pos;
public:
	TexturePtr gpos;
	TexturePtr gnormal;
	TexturePtr gcolor;
	DeferredLightPassMaterial(TexturePtr pos, TexturePtr normal,TexturePtr color) :Material(nullptr)
	{
		gpos = pos;
		gnormal = normal;
		gcolor = color;
		string vs = "main/shader/deferred_lightpass.vert.glsl";
		string fs = "main/shader/deferred_lightpass.frag.glsl";
		auto shader = std::make_shared<Shader>(vs, fs);
		set_shader(shader);
		init_light();
	}

	void init_light() {
		for (size_t i = 0; i < 32; i++)
		{
			lights[i].Position = vec3(0,5, 0);
			lights[i].Color = vec3(0.1, 0.02, 0.0);

		}
	}

	virtual void bind() {
		shader->bind();
		gpos->bind(0);
		int location = glGetUniformLocation(shader->gpu_id, "gPosition");
		glUniform1i(location, 0);

		gnormal->bind(1);
		location = glGetUniformLocation(shader->gpu_id, "gNormal");
		glUniform1i(location, 1);

		gcolor->bind(2);
		location = glGetUniformLocation(shader->gpu_id, "gAlbedoSpec");
		glUniform1i(location, 2);

		//location = glGetUniformLocation(shader->gpu_id, "lights");
		//glUniform1fv(location, 32*6,(GLfloat *)lights);

		for (size_t i = 0; i < 32; i++)
		{
			string name = "lights[" + std::to_string(i) + "].Position";
			int loc = glGetUniformLocation(shader->gpu_id, name.c_str());
			glUniform3f(loc, (GLfloat)lights[i].Position.x, (GLfloat)lights[i].Position.y, (GLfloat)lights[i].Position.z);
			
			name = "lights[" + std::to_string(i) + "].Color";
			loc = glGetUniformLocation(shader->gpu_id, name.c_str());
			glUniform3f(loc, (GLfloat)lights[i].Color.x, (GLfloat)lights[i].Color.y, (GLfloat)lights[i].Color.z);
		}


		set_uniform("viewPos", GPU_VEC3, view_pos);
	}
	void set_light(int index,vec3 pos, vec3 color) {
		lights[index].Position = pos;
		lights[index].Color = color;
	}

	void set_view_pos(vec3 pos) {
		view_pos = pos;
	}

};
typedef std::shared_ptr<DeferredLightPassMaterial> DeferredLightPassMaterialPtr;

#endif
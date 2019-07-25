#include "ui_text.h"
#include"env.h"
void gxo::UiText::on_render_begin()
{
//	string a = "hello";
//	env.render->rcmd(RCMD_TEXT,a , Rect(0, 0, 100, 100));


	auto material = env.engine->resource_manager.get<Material>("main/material/Texture");

	Material mat = *material;
	auto texture = text_texture;
	//auto texture = env.engine->resource_manager.get<Texture>("main/texture/house");
	Uniform uf;
	uf.data_type = GPU_SAMPLE2D;
	uf.name = Name("texture0");
	uf.value = texture;
	mat.set_uniform(uf);

	if (material->shader->gpu_id <= 0) {
		env.render->gpu_load(material);
	}
	env.render->rcmd(RCMD_MATERIAL, mat);

	auto ui_mesh = env.resource->get<Mesh>("default/plane");

	Transform3d t;
	t.position = vec3(position.x, 600 - size.y - position.y, 0);
	t.scale = vec3(size.x, size.y, 1);
	t.rotate = vec3(0, 0, 0);


	env.render->rcmd(RCMD_MESH, ui_mesh, t.matrix());


}

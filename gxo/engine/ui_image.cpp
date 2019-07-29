#include "ui_image.h"
#include"env.h"
#include"texture.h"
#include "gxo_name.h"
gxo::UiImage::UiImage()
{
	auto texture = env.engine->resource_manager.get<Texture>("main/texture/house");
	set<TexturePtr>(TEXTURE_PTR, texture);
}

void gxo::UiImage::on_render_begin()
{
	auto material = env.engine->resource_manager.get<Material>("main/material/Texture");

	Material mat = *material;
	auto texture= get<TexturePtr>(TEXTURE_PTR);
	Uniform uf;
	uf.data_type = GPU_SAMPLE2D;
	uf.name = Name("texture0") ;
	uf.value = texture;
	mat.set_uniform(uf);

	if (material->shader->gpu_id <= 0) {
		env.render->gpu_load(material);
	}
	env.render->rcmd(RCMD_MATERIAL, mat);

	auto ui_mesh = env.resource->get<Mesh>("default/plane");


	env.render->rcmd(RCMD_MESH, ui_mesh, get_box_transform());
}

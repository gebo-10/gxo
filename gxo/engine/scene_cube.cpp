#include "scene_cube.h"
#include "env.h"
bool gxo::SceneCube::on_render()
{
	
	auto material = env.engine->resource_manager.get<Material>("main/material/Texture");
	if (material->shader->gpu_id <= 0) {
		env.render->gpu_load(material);
	}
	env.render->rcmd(RCMD_MATERIAL, *material);

	auto ui_mesh = env.resource->get<Mesh>("default/cube");
	//ui_mesh->build(size.x, size.y);
	//ui_mesh->build(100, 100);


	env.render->rcmd(RCMD_MESH, ui_mesh, matrix() );
	return true;
}
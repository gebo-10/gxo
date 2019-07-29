#include"ui_node.h"
#include"engine.h"
#include"env.h"

gxo::UiNode::UiNode()
{
	
}
void gxo::UiNode::draw_rect() {


	auto material = env.engine->resource_manager.get<Material>("main/material/Texture");
	if (material->shader->gpu_id <= 0) {
		env.render->gpu_load(material);
	}
	env.render->rcmd(RCMD_MATERIAL, *material);

	auto ui_mesh = env.resource->get<Mesh>("default/plane");
	//ui_mesh->build(size.x, size.y);
	//ui_mesh->build(100, 100);

	Transform3d t;
	get<Transform3d>(TRANSFORM3D,t);

	vec2 anchor;
	get<vec2>(ANCHOR, anchor);
	Transform3d anchor_t;
	anchor_t.position = vec3(-anchor.x, -anchor.y, 0);

	env.render->rcmd(RCMD_MESH, ui_mesh,  get_box_transform() * t.matrix() * anchor_t.matrix());

}

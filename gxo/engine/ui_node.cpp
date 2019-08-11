#include"ui_node.h"
#include"engine.h"
#include"env.h"

gxo::UiNode::UiNode()
{
	
}

int gxo::UiNode::to_screen_y(int y)
{
	return env.get_screen_size().y - y;
}

ivec2 gxo::UiNode::get_screen_coord()
{
	return ivec2(position.x, env.get_screen_size().y - position.y - size.y);
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
	anchor.x = 0;
	anchor.y = 0;
	get<vec2>(ANCHOR, anchor);
	Transform3d anchor_t;
	anchor_t.position = vec3(-anchor.x, -anchor.y, 0);

	env.render->rcmd(RCMD_MESH, ui_mesh,  get_box_transform() * t.matrix() * anchor_t.matrix());

}

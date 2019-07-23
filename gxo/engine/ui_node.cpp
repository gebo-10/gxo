#include"ui_node.h"
#include"engine.h"
#include"env.h"

gxo::UiNode::UiNode()
{
	
}
void gxo::UiNode::draw_rect() {
	//static NVGcontext* vg = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
	//if (vg == nullptr) {
	//	vg = nvgCreateGL3(NVG_STENCIL_STROKES | NVG_DEBUG);

	//	//glUseProgram(prog);
	//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//	glEnable(GL_CULL_FACE);
	//	glCullFace(GL_BACK);
	//	glFrontFace(GL_CCW);
	//	glEnable(GL_BLEND);
	//	glDisable(GL_DEPTH_TEST);
	//	glDisable(GL_SCISSOR_TEST);
	//	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	//	glStencilMask(0xffffffff);
	//	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	//	glStencilFunc(GL_ALWAYS, 0, 0xffffffff);
	//	glActiveTexture(GL_TEXTURE0);
	//	//glBindBuffer(GL_UNIFORM_BUFFER, buf);
	//	//glBindVertexArray(arr);
	//	//glBindBuffer(GL_ARRAY_BUFFER, buf);
	//	//glBindTexture(GL_TEXTURE_2D, tex);
	//	//glUniformBlockBinding(..., GLNVG_FRAG_BINDING);
	//}
	//nvgBeginFrame(vg, 500, 500, 1.0);
	//nvgBeginPath(vg);
	//nvgRect(vg, position.x, position.y, size.x, size.y);
	////nvgFillColor(vg, nvgRGBA(size.y, position.x, size.x, 255));
	////nvgFill(vg);
	//nvgStrokeColor(vg, nvgRGBA(size.y, position.x, size.x, 255));
	//nvgStroke(vg);
	//nvgEndFrame(vg);
	//glEnable(GL_SCISSOR_TEST);
	//glScissor(position.x, position.y, size.x, size.y);
	////glViewport(position.x, position.y, size.x, size.y);
	//glClearColor(position.x / 1000.0f, 0.5f, size.y / 1000.0f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT);



	//Engine::instacne().render_system.render.rcmd(RCMD_RECT, Rect(position.x, position.y, size.x, size.y));


	auto material = env.engine->resource_manager.get<Material>("main/material/Texture");
	if (material->shader->gpu_id <= 0) {
		env.render->gpu_load(material);
	}
	env.render->rcmd(RCMD_MATERIAL, *material);

	auto ui_mesh = env.resource->get<Mesh>("default/plane");
	//ui_mesh->build(size.x, size.y);
	//ui_mesh->build(100, 100);

		
	Transform3d t;
	t.position = vec3(position.x,600- size.y- position.y, 0);
	t.scale = vec3(size.x, size.y, 1);
	t.rotate = vec3(0, 0, 0);


	env.render->rcmd(RCMD_MESH, ui_mesh, t.matrix());

}

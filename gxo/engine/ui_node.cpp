#include"ui_node.h"
#include"vg.h"
NVGcontext* vg=nullptr;
gxo::UiNode::UiNode()
{
	
}
void gxo::UiNode::draw_rect() {
	//static NVGcontext* vg = nvgCreateGL3(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
	if (vg == nullptr) {
		vg = nvgCreateGL3(NVG_STENCIL_STROKES | NVG_DEBUG);

		//glUseProgram(prog);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);
		glEnable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_SCISSOR_TEST);
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		glStencilMask(0xffffffff);
		glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
		glStencilFunc(GL_ALWAYS, 0, 0xffffffff);
		glActiveTexture(GL_TEXTURE0);
		//glBindBuffer(GL_UNIFORM_BUFFER, buf);
		//glBindVertexArray(arr);
		//glBindBuffer(GL_ARRAY_BUFFER, buf);
		//glBindTexture(GL_TEXTURE_2D, tex);
		//glUniformBlockBinding(..., GLNVG_FRAG_BINDING);
	}
	nvgBeginFrame(vg, 500, 500, 1.0);
	nvgBeginPath(vg);
	nvgRect(vg, position.x, position.y, size.x, size.y);
	//nvgFillColor(vg, nvgRGBA(size.y, position.x, size.x, 255));
	//nvgFill(vg);
	nvgStrokeColor(vg, nvgRGBA(size.y, position.x, size.x, 255));
	nvgStroke(vg);
	nvgEndFrame(vg);
	//glEnable(GL_SCISSOR_TEST);
	//glScissor(position.x, position.y, size.x, size.y);
	////glViewport(position.x, position.y, size.x, size.y);
	//glClearColor(position.x / 1000.0f, 0.5f, size.y / 1000.0f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT);
}

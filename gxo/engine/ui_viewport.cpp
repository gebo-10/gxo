#include "ui_viewport.h"
#include "env.h"
bool gxo::UiViewPort::on_render()
{
	auto scene = get<SceneRef>(SCENE);
	if (!scene.available() || !scene_camera.available()) return false;

	draw_rect();

	//lookAt()
	//glViewport();
	//cameranode;

	//mvp
	//bvh kdtree 
	//oit
	//pre-z
	//dof
	//post-process



	env.render->rcmd(RCMD_PUSH_PIPELINE, pipeline);
	//env.render->rcmd(RCMD_CLEAR, color_firebrick);
	scene->render_scene(scene_camera);
	env.render->rcmd(RCMD_POP_PIPELINE);
	return true;
}

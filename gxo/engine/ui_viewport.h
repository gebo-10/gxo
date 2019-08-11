#ifndef UI_VIEWPORT_H
#define UI_VIEWPORT_H
#include"ui_node.h"
#include"gxo_math.h"
#include"scene_camera.h"
#include"scene.h"
#include"pipeline.h"
namespace gxo {
	class UiViewPort :public UiNode
	{
	public:
		SceneRef scene = nullptr;
		SceneCameraRef scene_camera = nullptr;
		PipelinePtr pipeline;
		RenderPass passgroup;
		UiViewPort()
		{
			pipeline = std::make_shared<Pipeline>();
		}

		~UiViewPort()
		{
		}
		virtual bool on_render();

		virtual void on_layout_end() {
			//auto size = get<ivec2>(LAYOUT_SIZE);
			scene_camera->camera.set_ortho(-size.x/2.0, size.x/2.0, -size.y / 2.0, size.y / 2.0);

			//pipe->material = *material;
			pipeline->viewport = Rect(position.x, get_screen_coord().y, size.x, size.y);
			pipeline->target = std::make_shared<RenderTarget>();

			pipeline->P = scene_camera->camera.get_p();
			pipeline->V = scene_camera->camera.get_v();

			pipeline->depth_enable = true;
			pipeline->cull_face = CULL_NULL;
		}
	private:

	};
}
#endif
#ifndef ENGINE_UI_ROOT_H
#define ENGINE_UI_ROOT_H
#include<vector>
#include"ui_node.h"
#include"engine.h"
#include"camera.h"
#include"pipeline.h"
namespace gxo {
	class UiRoot :public UiNode
	{
	public:
		UiNode* mouse_focus;//有问题 当节点删除的时候 要同时把这个null
		UiNode* key_focus;
		Camera camera;
		PipelinePtr pipeline;
		UiRoot() :mouse_focus(nullptr), key_focus(nullptr){
			pipeline = std::make_shared<Pipeline>();
			camera.set_type(Camera::CameraType::ORTHO);
			camera.lookat(vec3(0, 0, 1), vec3(0, 0, 0), vec3(0, 1, 0));
		}
		//bool on_render() {
		//	auto size = get<ivec2>(LAYOUT_SIZE);
		//	glViewport(0, 0, size.x, size.y);
		//	for (auto child : children) {
		//		Engine::instacne().tree_manager.visit_preorder([](TreeNode* node) -> bool {
		//			return node->on_render();
		//			}, child);
		//	}
		//	
		//	return false;
		//}

		virtual void on_render_begin();

		virtual void on_layout_begin() {
			auto size = get<ivec2>(LAYOUT_SIZE);
			camera.set_ortho(0, size.x, 0, size.y);

			//pipe->material = *material;
			pipeline->viewport = Rect(0, 0, size.x, size.y);
			pipeline->target = std::make_shared<RenderTarget>();

			pipeline->P = camera.get_p();
			pipeline->V = camera.get_v();

			pipeline->cull_face = CULL_NULL;
		}

		void set_size() {
		}
	private:

	};
}
#endif 
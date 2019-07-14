#ifndef ENGINE_UI_ROOT_H
#define ENGINE_UI_ROOT_H
#include<vector>
#include"ui_node.h"
#include"engine.h"
#include"camera.h"
namespace gxo {
	class UiRoot :public UiNode
	{
	public:
		UiNode* mouse_focus;//有问题 当节点删除的时候 要同时把这个null
		UiNode* key_focus;
		Camera camera;
		UiRoot():mouse_focus(nullptr),key_focus(nullptr){

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

		virtual void on_render_begin() {
			auto size = get<ivec2>(LAYOUT_SIZE);
			camera.set_type(Camera::CameraType::ORTHO);
			camera.set_ortho(0, 0, size.x, size.y);
			camera.lookat(vec3(0, 0, 1), vec3(0, 0, 0), vec3(0, 1, 0));
		}

		//Rect on_layout(Rect& rect_parent) {
		//	Rect rect_self;
		//	return rect_self;
		//}

		void set_size() {
		}
	private:

	};
}
#endif 
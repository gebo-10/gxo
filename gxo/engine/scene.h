#ifndef GXO_SCENE_H
#define GXO_SCENE_H
#include"tree_node.h"
#include"gxo_math.h"
#include "scene_camera.h"
namespace gxo {
	class Scene :public Node
	{
	public:
		//scene_manager;
		//bvh  kdtree
		Scene()
		{
		}

		~Scene()
		{
		}
		virtual bool on_render() {
			//lookAt()
			//glViewport();
			//cameranode;

			//mvp
			//bvh kdtree
			//oit
			//pre-z
			//dof
			//post-process


			return false;
		}
		Rect on_layout(Rect& rect_parent) {
			return Rect(0, 0, 0, 0);
		}

		void render_scene(SceneCamera * camera) {
			for (auto child: children)
			{
				child->on_render();
			}
		}

	private:

	};
	REG_NODE(Scene)
}
#endif
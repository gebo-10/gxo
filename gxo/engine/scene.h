#ifndef GXO_SCENE_H
#define GXO_SCENE_H
#include"tree_node.h"
#include"gxo_math.h"
namespace gxo {
	class Scene :public TreeNode
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

		void render_scene() {
			for (auto child: children)
			{
				child->on_render();
			}
		}

	private:

	};
}
#endif
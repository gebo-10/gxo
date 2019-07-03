#ifndef SCENE_NODE_H
#define SCENE_NODE_H
#include"ui_node.h"
#include "gxo_math.h"
namespace gxo {
	class Scene :public UiNode
	{
	public:
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
		virtual void on_event() {
			//manipulator.event(); --> camera
		}
	private:

	};
}
#endif
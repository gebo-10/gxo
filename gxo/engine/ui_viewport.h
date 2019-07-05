#ifndef UI_VIEWPORT_H
#define UI_VIEWPORT_H
#include"ui_node.h"
#include"gxo_math.h"
#include"scene_camera.h"
#include"scene.h"
namespace gxo {
	class UiViewPort :public UiNode
	{
	public:
		Scene *scene;
		SceneCamera *scene_camera;

		UiViewPort()
		{
		}

		~UiViewPort()
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

			scene->render_scene();
			return true; 
		}
		virtual void on_event() {
			//manipulator.event(); --> camera
		}
	private:

	};
}
#endif
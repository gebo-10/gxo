#ifndef GXO_SCENE_CAMERA_H
#define GXO_SCENE_CAMERA_H
#include"scene_node.h"
#include "gxo_math.h"
#include"camera.h"
namespace gxo {
	class SceneCamera :public SceneNode
	{
	public:
		Camera camera;

		SceneCamera()
		{
			camera.set_type(Camera::CameraType::PERSPECTIVE);
			camera.lookat(vec3(0, 0, 5), vec3(0, 0, 0), vec3(0, 1, 0));
		}

		~SceneCamera()
		{
		}
	
	};
	REG_NODE(SceneCamera)
}
#endif
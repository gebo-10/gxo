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
		}

		~SceneCamera()
		{
		}
	
		mat4 get_vp() {
			auto transform=get<Transform3d>(TRANSFORM3D);
			auto mat = transform.matrix();
			return camera.get_projectionx() * mat;
		}

	};
}
#endif
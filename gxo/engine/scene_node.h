#ifndef SCENE_NODE_H
#define SCENE_NODE_H
#include"tree_node.h"
#include"node_ref.h"
#include "gxo_math.h"
namespace gxo {
	class SceneNode :public Node
	{
	public:
		//vec3  position;
		//vec3  rotate;
		//vec3  scale;
		SceneNode()
		{
			Transform3d transform;
			add_property(TRANSFORM3D, transform);
		}

		~SceneNode()
		{
		}

		mat4 matrix() {
			auto transform = get<Transform3d>(TRANSFORM3D);
			auto mat = transform.matrix();
			return  mat;
		}
	private:

	};
}
#endif

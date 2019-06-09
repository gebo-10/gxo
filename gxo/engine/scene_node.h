#ifndef SCENE_NODE_H
#define SCENE_NODE_H
#include"tree_node.h"
#include "gxo_math.h"
namespace gxo {
	class SceneNode :public TreeNode
	{
	public:
		vec3  position;
		vec3  rotate;
		vec3  scale;
		SceneNode()
		{
		}

		~SceneNode()
		{
		}

	private:

	};
}
#endif

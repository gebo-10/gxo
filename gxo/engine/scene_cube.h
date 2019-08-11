#ifndef GXO_SCENE_CUBE_H
#define GXO_SCENE_CUBE_H
#include"scene_node.h"
#include "gxo_math.h"

namespace gxo {
	class SceneCube :public SceneNode
	{
	public:
		
		SceneCube()
		{
		}

		~SceneCube()
		{
		}

		bool on_render();

	};

}
#endif
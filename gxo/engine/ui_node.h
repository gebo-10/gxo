#ifndef ENGINE_UI_NODE_H
#define ENGINE_UI_NODE_H
#include<vector>
#include"tree_node.h"
namespace gxo {
	class UiNode :public TreeNode
	{
	public:
		int width;
		int height;
		int x;
		int y;
		UiNode()
		{
		}

		~UiNode()
		{
		}

	private:

	};
}
#endif 

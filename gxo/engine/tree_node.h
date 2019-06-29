#ifndef ENGINE_NODE_H
#define ENGINE_NODE_H
#include<list>
#include"entity.h"

namespace gxo {
	class TreeNode:public Entity
	{
	public:
		//enum Status
		//{
		//	CRWEATED,
		//	INITED,
		//	ACTIVE,
		//	NOT_ACTIVE,
		//	DESTORIED,
		//};
		//Status status;
		
		TreeNode* parent;
		std::list<TreeNode*> children;
		
		TreeNode()
		{
		}

		virtual ~TreeNode()
		{
		}

		void add_child(TreeNode * node) {
			children.push_back(node);
		}


		virtual bool on_render() {

			return true;
		}

	private:

	};
}
#endif // !ENGINE_NODE_H

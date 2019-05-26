#ifndef ENGINE_NODE_H
#define ENGINE_NODE_H
#include<vector>
namespace gxo {
	class TreeNode
	{
	public:
		enum Status
		{
			CRWEATED,
			INITED,
			ACTIVE,
			NOT_ACTIVE,
			DESTORIED,
		};
		Status status;
		TreeNode* parent;
		std::vector<TreeNode*> children;
		
		TreeNode()
		{
		}

		~TreeNode()
		{
		}

	private:

	};
}
#endif // !ENGINE_NODE_H

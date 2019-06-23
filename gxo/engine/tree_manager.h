#ifndef _GXO_TREE_MANAGER_H
#define _GXO_TREE_MANAGER_H
#include "tree_node.h"
#include"ui_node.h"
namespace gxo {
	class TreeManager
	{
	public:
		//bool visit_break; //遍历过程可以中断整个过程
		TreeNode tree;
		TreeManager() {}
		~TreeManager() {}
		bool init() {

			return true;
		}

		
		void visit_preorder(std::function<bool (TreeNode*)> visitor, TreeNode * root) {
			if (root == nullptr) return;
			if (visitor(root)) {
				for (auto child : root->children) {
					visit_preorder(visitor, child);
				}
			}
		}
		void visit_preorder(std::function<bool(TreeNode*)> visitor) {
			visit_preorder(visitor, &tree);
		}

		
		enum VisitContinue {

		};
		//search()

	private:
		
	};

}
#endif
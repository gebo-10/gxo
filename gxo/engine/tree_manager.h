#ifndef GXO_TREE_MANAGER_H
#define GXO_TREE_MANAGER_H
#include "tree_node.h"
#include"ui_screen.h"
namespace gxo {
	class TreeManager
	{
	public:
		//bool visit_break; //遍历过程可以中断整个过程
		UiScreen screen;
		TreeManager(){}
		~TreeManager() {}
		void init() {
			screen.init();
			return;
		}

		void update();


		
		void visit_preorder(std::function<bool (Node*)> visitor, Node * root) {
			if (root == nullptr) return;
			if (visitor(root)) {
				for (auto child : root->children) {
					visit_preorder(visitor, child.get());
				}
			}
		}
		void visit_preorder(std::function<bool(Node*)> visitor) {
			visit_preorder(visitor, &screen);
		}

		
		enum VisitContinue {

		};
		//search()
		UiScreen* get_screen() {
			return &screen;
		}
	private:
		
	};

}
#endif
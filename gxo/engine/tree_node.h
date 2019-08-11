#ifndef GXO_ENGINE_NODE_H
#define GXO_ENGINE_NODE_H
#include<list>
#include"entity.h"
#include "gxo_type.h"
#include "node_ref.h"

#define REG_NODE(NAME) \
	typedef NAME* NAME##Pointer; \
	typedef shared_ptr<NAME> NAME##Ptr; \
	typedef Ref<NAME> NAME##Ref; \

namespace gxo {
	class Node:public Entity
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
		//Status status
		uint32 id; //TODO: how copy and son copy
		Node * parent;
		std::list< shared_ptr<Node> > children;
		
		Node()
		{
			id = ++id_count;
		}

		virtual ~Node()
		{
			id = -1;
		}

		void add_child(shared_ptr<Node> node) {
			node->parent = this;
			children.push_back(node);
		}
		void add_child(Node * node) {
			node->parent = this;
			
			children.push_back(shared_ptr<Node>(node));
		}

		virtual bool on_render() {

			return true;
		}

	private:
		static uint32 id_count;
	};
	REG_NODE(Node)

}
#endif // !ENGINE_NODE_H

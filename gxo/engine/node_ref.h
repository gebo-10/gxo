#ifndef GXO_NODE_REF_H
#define GXO_NODE_REF_H
namespace gxo {
	template<class T>
	class Ref {
	public:
		uint32 id = 0;
		T* node = nullptr;
		Ref(){}
		Ref(T* pnode) {
			node = pnode;
			node== nullptr ? id=0: id = pnode->id;
		}

		operator T* () const{
			return node;
		}

		void reset() {
			id = 0;
			node = nullptr;
		}

		T* get() {
			return node;
		}

		bool available() {
			return node && node->id == id;
		}

		void operator =(T* pnode) {
			node = pnode;
			node == nullptr ? id = 0 : id = pnode->id;
		}

		void operator =(Ref& ref) {
			node = ref.node;
			id = ref.id;
		}

		void operator =(shared_ptr<T> &ptr) {
			node = ptr.get();
			id = ptr->id;
		}

		T* operator -> () {
			return node->id == id ? node : nullptr;
		}

		bool operator ==(T* pnode) {
			return node == pnode;
		}

		bool operator ==(Ref &ref) {
			return node == ref.node;
		}
	};
}
#endif

#ifndef _GXO_ID_H
#define _GXO_ID_H
#include"type.h"
namespace gxo {
	typedef unsigned int UID;
	class IDManager
	{
	public:
		UID id;
	public:
		IDManager()
		{
			id = 0;
		}

		~IDManager()
		{
		}
		UID gen_uid(){
			return ++id;
        }

	private:

	};
}
#endif

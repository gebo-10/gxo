//检查index实际跑的增加率 是否需要增加到 64位
#ifndef _GXO_ID_H
#define _GXO_ID_H
#include"type.h"
namespace gxo {
	class UID
	{
	public:
		static unsigned int index;
		unsigned int id;
		UID()
		{
			id = ++index;
		}
		UID(unsigned int id)
		{
			id = id;
		}
		unsigned int current() {
			return index;
		}

		static UID gen() {
			return UID();
		}

	};
}
#endif

//检查index实际跑的增加率 是否需要增加到 64位
#ifndef _GXO_ID_H
#define _GXO_ID_H
//#include"type.h"

namespace gxo {
	class UID
	{
	public:
		
		unsigned int id;
		UID()
		{
			id = gen().id;
		}
		UID(unsigned int id)
		{
			id = id;
		}

		static UID gen() {
			static unsigned int index = 0;
			return UID(index++);
		}

	};
}
#endif

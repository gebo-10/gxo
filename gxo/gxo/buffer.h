#ifndef _GXO_BUFFER_H
#define _GXO_BUFFER_H
#include "type.h"

namespace gxo {
	struct Buffer {
		Buffer() :data(nullptr), size(0){}
		byte * data;
		uint32_t size;
	};

}
#endif
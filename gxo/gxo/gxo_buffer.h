#ifndef GXO_BUFFER_H
#define GXO_BUFFER_H
#include "gxo_type.h"

namespace gxo {
	struct Buffer {
		Buffer() :data(nullptr), size(0){}
		byte * data;
		uint32_t size;
	};

}
#endif
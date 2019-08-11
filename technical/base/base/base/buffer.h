#ifndef GXO_BUFFER_H
#define GXO_BUFFER_H
#include "core_base.h"
#include <stdlib.h>
	class Buffer {
	public:
		byte* data;
		uint32 size;
		Buffer() :data(nullptr), size(0) {}
		void set(byte* in_data, uint32 in_size) {
			data = in_data;
			size = in_size;
		}
		void malloc(uint32 in_size) {
			data = (byte*)std::malloc(in_size);
			size = in_size;
		}
		void free() {
			std::free((void*)data);
			data = nullptr;
			size = 0;
		}
		void reset() {
			if (size != 0) {
				free();
			}
		}
	};

#endif
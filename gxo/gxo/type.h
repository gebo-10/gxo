#ifndef _GXO_TYPE_H
#define _GXO_TYPE_H
#include <stdint.h>
#include<string>
#include<string_view>
namespace gxo {
	typedef unsigned char byte;
	typedef std::string string;
	typedef string_view string_view;
	typedef int16_t int16;
	typedef uint16_t uint16;
	typedef int32_t int32;
	typedef uint32_t uint32;
	typedef uint64_t uint64;
	typedef std::string URL;
}
#endif
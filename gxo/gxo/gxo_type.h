#ifndef _GXO_TYPE_H
#define _GXO_TYPE_H
#include<string>
#include<string_view>
#include<cstdint>
#include<vector>
#include<map>
#include<iostream>
#include<memory>
#include<any>
#include<stack>
#include<functional>
#include<cassert>
namespace gxo {
	typedef unsigned char byte;
	typedef std::string string;
	typedef std::string_view string_view;
	typedef int8_t int8;
	typedef uint8_t uint8;
	typedef int16_t int16;
	typedef uint16_t uint16;
	typedef int32_t int32;
	typedef uint32_t uint32;
	typedef uint32_t uint;
	typedef uint64_t uint64;
	typedef std::string URL;
	template <typename T> using shared_ptr=std::shared_ptr<T>;
}
#endif

#pragma warning ( disable : 4244 )
#ifndef CORE_BASE_H
#define CORE_BASE_H

#include<iostream>

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
typedef unsigned int GPUID;


template <typename T> using shared_ptr=std::shared_ptr<T>;
template <typename T> using weak_ptr=std::weak_ptr<T>;

#define make(T, ...) std::make_shared <T>(__VA_ARGS__)

#define REG(NAME) \
	typedef shared_ptr<NAME> NAME##Ptr; 

#include "log.h"

#include "color.h"

#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
using namespace glm;


enum CullFaceType {
	CULL_NULL,
	CULL_BACK,
	CULL_FRONT,
};

enum BlendMode {
	BLEND_NONE,
	BLEND_MIX,
	BLEND_PREBUILD,
};




template<class T>
class RectT
{
public:
	T x;
	T y;
	T width;
	T height;
	RectT() : x(0), y(0), width(0), height(0) {}
	RectT(T x, T y, T width, T height) : x(x), y(y), width(width), height(height) {}
	~RectT() {}
	void set(ivec2 pos, ivec2 size) {
		x = pos.x;
		y = pos.y;
		width = size.x;
		height = size.y;
	}
};
typedef RectT<int> Rect;
typedef RectT<float> Rectf;


class Transform3d
{
public:
	vec3  position{ 0 };
	vec3  rotate{ 0 };
	vec3  scale{ 1 };
	Transform3d() {}
	~Transform3d() {}
	mat4 matrix() {
		mat4 identity(1.f);
		mat4 matrix = translate(identity, position) * mat4_cast(quat(radians(rotate))) * glm::scale(identity, scale);
		return matrix;
	}
};

#endif
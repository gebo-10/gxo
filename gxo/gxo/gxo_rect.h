#ifndef GXO_RECT_H
#define GXO_RECT_H
#include"gxo_math.h"
namespace gxo {
	template<class T>
	class RectT
	{
	public:
		T x;
		T y;
		T width;
		T height;
		RectT(): x(0),y(0),width(0),height(0) {}
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

}
#endif
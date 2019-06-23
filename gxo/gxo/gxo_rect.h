#ifndef GXO_RECT_H
#define GXO_RECT_H
#include"gxo_math.h"
namespace gxo {
	class Rect
	{
	public:
		int x;
		int y;
		int width;
		int height;
		Rect(): x(0),y(0),width(0),height(0) {}
		Rect(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {}
		~Rect() {}
		void set(ivec2 pos, ivec2 size) {
			x = pos.x;
			y = pos.y;
			width = size.x;
			height = size.y;
		}
	private:

	};

}
#endif
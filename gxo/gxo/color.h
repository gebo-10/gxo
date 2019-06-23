#ifndef GXO_COLOR_H
#define GXO_COLOR_H
namespace gxo {
	class Color
	{
	public:
		char r;
		char g;
		char b;
		char a;
		Color() : r(0), g(0), b(0), a(0) {}
		~Color() {}
		void to_hsl(){}
	private:

	};

}
#endif
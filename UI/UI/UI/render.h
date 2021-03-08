#pragma once
#include"3rd.h"
#include<string>
class Render
{
public:
	Render(SkCanvas* c) { canvas = c; }
	~Render(){}
	void draw_rect(int x,int y,int w,int h, uint32_t color) {
		SkRect rect = SkRect::MakeXYWH(x,y,w,h);
		SkPaint p;
		p.setColor(SK_ColorCYAN);
		p.setStroke(true);
		canvas->drawRect(rect, p);
	}

	void draw_text(std::string s,int x, int y) {
		
		SkPaint paint2;
		paint2.setColor(SK_ColorWHITE);
		auto text = SkTextBlob::MakeFromString(s.c_str(), SkFont(nullptr, 30));
		canvas->drawTextBlob(text.get(), x, y, paint2);
	}

	void draw_image(std::string s, int x, int y,int w, int h) {
		auto data = SkData::MakeFromFileName(s.c_str() );
		
		auto img=SkImage::MakeFromEncoded(data);
		SkRect rect = SkRect::MakeXYWH(x, y, w, h);
		SkPaint p;
		canvas->drawImageRect(img,rect,&p);
	}
	void reg_canvas(sol::state &lua) {
		sol::usertype<SkCanvas> player_type = lua.new_usertype<SkCanvas>("Canvas",
			// 3 constructors
			sol::constructors<SkCanvas()>());

		// typical member function that returns a variable
		player_type["draw_rect"] = &SkCanvas::drawIRect;

	}
	static void reg_render(sol::state& lua) {
		sol::usertype<Render> type = lua.new_usertype<Render>("Render",
			// 3 constructors
			sol::constructors<>());

		// typical member function that returns a variable
		type["draw_rect"] = &Render::draw_rect;
		type["draw_text"] = &Render::draw_text;
		type["draw_image"] = &Render::draw_image;
	}
private:
	SkCanvas* canvas;
};


/*
void draw(SkCanvas* canvas) {
	SkScalar scale = 256.0f;
	SkScalar R = 0.45f * scale;
	SkScalar TAU = 6.2831853f;
	SkPath path;
	path.moveTo(R, 0.0f);
	for (int i = 1; i < 7; ++i) {
		SkScalar theta = 3 * i * TAU / 7;
		path.lineTo(R * cos(theta), R * sin(theta));
	}
	path.close();
	SkPaint p;
	p.setAntiAlias(true);
	canvas->clear(SK_ColorWHITE);
	canvas->translate(0.5f * scale, 0.5f * scale);
	canvas->drawPath(path, p);
}

void draw2(SkCanvas* canvas) {
	//canvas->save();
	//canvas->translate(SkIntToScalar(128), SkIntToScalar(128));
	//canvas->rotate(SkIntToScalar(45));
	SkRect rect = SkRect::MakeXYWH(-90.5f, -90.5f, 181.0f, 181.0f);
	SkPaint paint;
	paint.setColor(SK_ColorBLUE);
	canvas->drawRect(rect, paint);
	//canvas->restore();
}


*/
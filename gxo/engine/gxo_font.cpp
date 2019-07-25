#include "gxo_font.h"
#include "gxo_color.h"
#include "env.h"
using namespace gxo;
Font::Font()
{

}

Font::~Font()
{

}

bool Font::Init()
{
	error = FT_Init_FreeType(&library);
	return true;
}

void Font::SetFont(const char* font_file)
{
	error = FT_New_Face(library, "main\\font\\msyh.ttc", 0, &face);
}

void Font::SetFontSize(int size)
{
	error = FT_Set_Char_Size(face, size * 64, size * 64, 96, 96);
}

TexturePtr Font::GetStrTexture(string str)
{
	uint32 charIdx = FT_Get_Char_Index(face, L'哈哈');
	FT_Load_Glyph(face, charIdx, FT_LOAD_DEFAULT);

	TexturePtr texture = std::make_shared<Texture>();
	int width = 100;
	int height = 100;

	FT_Glyph glyph;
	FT_Get_Glyph(face->glyph, &glyph);

	//Convert the glyph to a bitmap.
	FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0, 1);
	FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;

	//This reference will make accessing the bitmap easier
	FT_Bitmap& bitmap = bitmap_glyph->bitmap;

	char* pBuf = new char[width * height * 4];
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			unsigned char _vl = (i >= bitmap.width || j >= bitmap.rows) ? 0 : bitmap.buffer[i + bitmap.width * j];
			pBuf[(4 * i + (height - j - 1) * width * 4)] = _vl*0.5;
			pBuf[(4 * i + (height - j - 1) * width * 4) + 1] = 0xFF;
			pBuf[(4 * i + (height - j - 1) * width * 4) + 2] = 0;
			pBuf[(4 * i + (height - j - 1) * width * 4) + 3] = _vl;
		}
	}
	Buffer buf;
	buf.data = (byte*)pBuf;
	buf.size = width * height * 4;
	texture->create("texture/font/me", buf);
	
	texture->width = width;
	texture->height = height;
	texture->format = GL_RGBA;

	env.render->gpu_load(texture);
	return texture;
}

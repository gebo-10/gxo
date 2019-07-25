#ifndef GXO_FONT_H
#define GXO_FONT_H

#include <ft2build.h>
#include <freetype/ftoutln.h>
#include <freetype/freetype.h>  
#include <freetype/ftglyph.h>  
#include <freetype/ftoutln.h>  
#include <freetype/fttrigon.h> 
#include FT_FREETYPE_H

#include "texture.h"
namespace gxo {
	class Font {
	public:
		FT_Library	library;
		FT_Face		face;
		FT_Error	error;

		int   size;

		Font();
		~Font();
		bool Init();
		void SetFont(const char* font_file);
		void SetFontSize(int size);
		TexturePtr GetStrTexture(string str);

	};
}
#endif
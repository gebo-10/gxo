#ifndef PROPERTY_NAME_DEF_H
#define PROPERTY_NAME_DEF_H
namespace gxo {
	enum PropertyNameDef {
		TAG=100,
		NAME,		//string
		LAYOUT_SIZE,		//ivec2
		POSITION,	//ivec2
		SCALE,		//vec2
		ROTATE,		//float
		RENDER_PASS, //RenderPass *

	};
}
#endif

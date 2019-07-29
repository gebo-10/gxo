#ifndef PROPERTY_NAME_DEF_H
#define PROPERTY_NAME_DEF_H
namespace gxo {
	enum PropertyNameDef {
		TAG = 100,
		NAME,		//string
		LAYOUT_SIZE,		//ivec2
		POSITION,	//ivec2
		SCALE,		//vec2
		ROTATE,		//float
		RENDER_PASS, //RenderPass *
		CLEAR_COLOR, //Color

		ALIGN_X,	//enum Align
		ALIGN_Y,	//enum Align

		REF, //TreeNode path
		PTR, //TreeNode *
		TRANSFORM2D,		//Transform2d
		TRANSFORM3D,			//Transform3d
		ANCHOR,				//vec2

		RESOURCE_PTR,
		TEXTURE_PTR,

	};
}
#endif

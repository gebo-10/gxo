#ifndef GXO_RENDER_COMMAND_H
#define GXO_RENDER_COMMAND_H
#include"mesh.h"
#include"gxo_math.h"
#include"material.h"
#include"render_target.h"
#include"gxo_rect.h"
#include"gxo_param.h"
namespace gxo {
	enum RenderCommandType
	{
		RCMD_INVALD,
		RCMD_SWAPBUFFER,
		RCMD_CLEAR,
		RCMD_SET_PIPELINE,
		RCMD_SET_PIPELINE_STATE,
		RCMD_CAMERA,
		RCMD_MESH,
		RCMD_MATERIAL,
		RCMD_RENDER_TARGET,
		RCMD_LIGHT,
		RCMD_UI_BEGIN,
		RCMD_UI_END,
		RCMD_IMAGE,
		RCMD_TEXT,
		RCMD_VG,
		RCMD_RECT,
	};

	class RenderCommand
	{
	public:
		RenderCommandType type;
		Params params;
		RenderCommand() :type(RCMD_INVALD) {}
		RenderCommand(RenderCommandType type) :type(type) {}
		RenderCommand(RenderCommandType type, Params &params) :type(type), params(params){}
	};
	typedef std::shared_ptr<RenderCommand> RenderCommandPtr;
}
#endif
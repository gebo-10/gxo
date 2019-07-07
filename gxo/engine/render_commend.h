#ifndef GXO_RENDER_COMMAND_H
#define GXO_RENDER_COMMAND_H
#include"gxo_type.h"
#include"gxo_param.h"
namespace gxo {
	enum RenderCommandType
	{
		RCMD_INVALD,
		RCMD_SWAPBUFFER,
		RCMD_CLEAR,
		RCMD_SET_PIPELINE,
		RCMD_SET_PIPELINE_STATE,
		RCMD_PUSH_PIPELINE,
		RCMD_POP_PIPELINE,
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
		RCMD_LOAD_RESOURCE_TO_GPU,
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
	typedef shared_ptr<RenderCommand> RenderCommandPtr;
}
#endif
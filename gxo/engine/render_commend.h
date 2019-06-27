#ifndef GXO_RENDER_COMMAND_H
#define GXO_RENDER_COMMAND_H
namespace gxo {
	class RenderEngine;
	class RenderCommand
	{
	public:
		enum RenderCommandType
		{
			RCMD_EMPTY,
			RCMD_BIND_VAO,
			RCMD_DRAW_MESH,
			RCMD_DRAW_LINES,
			RCMD_LIGHT,
			RCMD_GEOMETRY,
			RCMD_MATERIAL,
			RCMD_CAMERA,
		};
		int type;
		RenderCommand() :type(RCMD_EMPTY) {};
		RenderCommand(int type) :type(type) {};
		virtual ~RenderCommand() {};

		virtual void process(RenderEngine* render);
	};

}
#endif
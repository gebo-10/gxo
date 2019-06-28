#ifndef GXO_RENDER_COMMAND_H
#define GXO_RENDER_COMMAND_H
#include"mesh.h"
#include"gxo_math.h"
#include"material.h"
#include"render_target.h"
#include"gxo_rect.h"
namespace gxo {
	class Render;
	enum RenderCommandType
	{
		RCMD_INVALD,
		REMD_SWAPBUFFER,
		REMD_CLEAR,
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
////////////////////////////////////////////////////////////////////////
	class RenderCommand
	{
	public:
		int type;
		RenderCommand() :type(RCMD_INVALD) {}
		RenderCommand(int type) :type(type) {}
		virtual ~RenderCommand() {}
		virtual void process(Render* render);
	};
	typedef std::shared_ptr<RenderCommand> RenderCommandPtr;
////////////////////////////////////////////////////////////////////////
	class RcmdSwapBuffer :public RenderCommand
	{
	public:
		RcmdSwapBuffer(): RenderCommand(REMD_SWAPBUFFER) {}
		~RcmdSwapBuffer() { /*info("RcmdSwapBuffer: delete");*/ }
		virtual void process(Render* render);
	};
	typedef std::shared_ptr<RcmdSwapBuffer> RcmdSwapBufferPtr;
////////////////////////////////////////////////////////////////////////
	class RcmdClear :public RenderCommand
	{
	public:
		RcmdClear() : RenderCommand(REMD_CLEAR) {}
		~RcmdClear() { /*info("RcmdClear: delete");*/ }
		virtual void process(Render* render) {
			glClearColor(0.f, 1.f, 0.f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT| GL_STENCIL_BUFFER_BIT);
		}
	};
	typedef std::shared_ptr<RcmdClear> RcmdClearPtr;
	////////////////////////////////////////////////////////////////////////
	class RcmdMesh :public RenderCommand
	{
	public:
		int		shadow_type;//0 表示没阴影， 1 表示硬阴影，  2 表示软阴影
		MeshPtr	mesh;
		mat4	transform;

	public:
		RcmdMesh() :RenderCommand(RCMD_MESH) { }
		~RcmdMesh() {}

		void Init(MeshPtr mesh);
		virtual void process(Render* render);

	};
	typedef std::shared_ptr<RcmdMesh> RcmdMeshPtr;
///////////////////////////////////////////////////////////////////////////
	class RcmdMaterial :public RenderCommand
	{
	public:
		MaterialPtr	material;

	public:
		RcmdMaterial() :RenderCommand(RCMD_MATERIAL) { };
		~RcmdMaterial() {};

		void Init(MaterialPtr material);
		virtual void process(Render* render);

	};
	typedef std::shared_ptr<RcmdMaterial> RcmdMaterialPtr;
	///////////////////////////////////////////////////////////////////////////
	class RcmdRenderTarget :public RenderCommand
	{
	public:
		RenderTargetPtr	render_target;

	public:
		RcmdRenderTarget() :RenderCommand(RCMD_RENDER_TARGET) { };
		~RcmdRenderTarget() {};

		void Init(RenderTargetPtr render_target);
		virtual void process(Render* render);

	};
	typedef std::shared_ptr<RcmdRenderTarget> RcmdRenderTargetPtr;
	///////////////////////////////////////////////////////////////////////////
	class RcmdImage :public RenderCommand
	{
	public:
		string	path;

	public:
		RcmdImage() :RenderCommand(RCMD_IMAGE) { };
		~RcmdImage() {};

		void Init(string	path);
		virtual void process(Render* render);

	};
	typedef std::shared_ptr<RcmdImage> RcmdImagePtr;
	///////////////////////////////////////////////////////////////////////////
	class RcmdText :public RenderCommand
	{
	public:
		string	text;

	public:
		RcmdText() :RenderCommand(RCMD_TEXT) { };
		~RcmdText() {};

		void Init(string	text);
		virtual void process(Render* render);

	};
	typedef std::shared_ptr<RcmdText> RcmdTextPtr;
	///////////////////////////////////////////////////////////////////////////
	class RcmdRect :public RenderCommand
	{
	public:
		Rect rect;

	public:
		RcmdRect() :RenderCommand(RCMD_RECT) { };
		~RcmdRect() {};

		void Init(Rect rect);
		virtual void process(Render* render);

	};
	typedef std::shared_ptr<RcmdRect> RcmdRectPtr;
	///////////////////////////////////////////////////////////////////////////
}
#endif
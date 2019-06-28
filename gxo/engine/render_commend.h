#ifndef GXO_RENDER_COMMAND_H
#define GXO_RENDER_COMMAND_H
#include"mesh.h"
#include"gxo_math.h"
#include"material.h"
#include"render_target.h"
namespace gxo {
	class Renderer;
	enum RenderCommandType
	{
		RCMD_INVALD,
		RCMD_MESH,
		RCMD_MATERIAL,
		RCMD_RENDER_TARGET,
		RCMD_LIGHT,
		RCMD_UI_BEGIN,
		RCMD_UI_END,
		RCMD_CAMERA,
	};
////////////////////////////////////////////////////////////////////////
	class RenderCommand
	{
	public:
		int type;
		RenderCommand() :type(RCMD_INVALD) {};
		RenderCommand(int type) :type(type) {};
		virtual ~RenderCommand() {};
		virtual void process(Renderer* render);
	};
	typedef std::shared_ptr<RenderCommand> RenderCommandPtr;
////////////////////////////////////////////////////////////////////////
	class RcmdMesh :public RenderCommand
	{
	public:
		int		shadow_type;//0 表示没阴影， 1 表示硬阴影，  2 表示软阴影
		MeshPtr	mesh;
		mat4	transform;

	public:
		RcmdMesh() :RenderCommand(RCMD_MESH) { };
		~RcmdMesh() {};

		void Init(MeshPtr mesh);
		virtual void process(Renderer* render);

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
		virtual void process(Renderer* render);

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

		void Init(MaterialPtr material);
		virtual void process(Renderer* render);

	};
	typedef std::shared_ptr<RcmdRenderTarget> RcmdRenderTargetPtr;
	///////////////////////////////////////////////////////////////////////////

}
#endif
#ifndef GXO_PIPELINE_H
#define GXO_PIPELINE_H
#include"gxo_type.h"
#include"gxo_math.h"
#include"material.h"
#include"mesh.h"
#include"render_target.h"
namespace gxo {
	class Pipeline
	{
	public:
		RenderTargetPtr target=nullptr;
		MaterialPtr material=nullptr;
		vec2 viewport;
		mat4 V{1.0f};
		mat4 P{ 1.0f };

		int depth_type;
		int blend_type;
		int scenil_type;
		Rect scoissor;

		bool cull_face;

		Pipeline()
		{
		}

		~Pipeline()
		{
		}
		void use() {

		}
		void push(MeshPtr mesh, mat4 M ) {

		}
	};
	typedef shared_ptr<Pipeline> PipelinePtr;
}
#endif
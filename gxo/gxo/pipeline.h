#ifndef GXO_PIPELINE_H
#define GXO_PIPELINE_H
#include"gpu_concept.h"
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
		Material material;
		Rect viewport;
		mat4 V{1.0f};
		mat4 P{ 1.0f };
		CullFaceType cull_face;
		BlendMode blend_mode;
		Color clear_color;
		//int depth_type;
		//int blend_type;
		//int scenil_type;
		//Rect scoissor;

		Pipeline()
		{
		}

		~Pipeline()
		{
		}

		void use() {
			target->use();
			glViewport(viewport.x, viewport.y, viewport.width, viewport.height);
			if (material.shader != nullptr) {
				material.use();
			}	
		}
		void push(MeshPtr mesh, mat4 M ) {
			material.mvp(M,V,P);
			mesh->gpu_object.bind();
			glDrawElements(mesh->primitive, mesh->size, GL_UNSIGNED_SHORT, 0);
		}
		void set_clear_color(Color color) {
			clear_color = color;
			glClearColor(color.r, color.g, color.b, color.a);
		}

		void clear() {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		}
		void set_vp(mat4 V, mat4 P) {
			this->V = V;
			this->P = P;
		}

		void set_viewport(Rect viewport) {
			this->viewport = viewport;
			glViewport(viewport.x, viewport.y, viewport.width, viewport.height);
		}

		void set_target(RenderTargetPtr target) {
			this->target = target;
			target->use();
		}

		void set_material(Material& material) {
			this->material = material;
			this->material.use();
		}

		void set_cullface(CullFaceType type) {
			switch (type)
			{
			case gxo::CULL_NULL:
				glDisable(GL_CULL_FACE);
				break;
			case gxo::CULL_BACK:
				glEnable(GL_CULL_FACE);
				glCullFace(GL_BACK);
				break;
			case gxo::CULL_FRONT:
				glEnable(GL_CULL_FACE);
				glCullFace(GL_FRONT);
				break;
			default:
				break;
			}
		}


	};
	typedef shared_ptr<Pipeline> PipelinePtr;
}
#endif
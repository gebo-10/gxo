#ifndef GXO_PIPELINE_H
#define GXO_PIPELINE_H

#include"core_base.h"

#include"material.h"
#include"mesh.h"
#include"render_target.h"

	class Pipeline
	{
	public:
		RenderTargetPtr target = nullptr;
		Material material;
		Rect viewport;
		mat4 V{ 1.0f };
		mat4 P{ 1.0f };
		CullFaceType cull_face;
		BlendMode blend_mode;
		Color clear_color;
		bool depth_enable = false;
		//int blend_type;
		//int scenil_type;
		//Rect scoissor;

		Pipeline()
		{
		}

		~Pipeline()
		{
		}

		void bind() {
			target->bind();
			set_cullface(cull_face);
			set_depth_test(depth_enable);
			//glDepthRange(0.0, 1000.0);
			//glDepthFunc(GL_EQUAL);
			//glDepthMask(GL_FALSE);
			glViewport(viewport.x, viewport.y, viewport.width, viewport.height);
			if (material.shader != nullptr) {
				material.bind();
			}
		}
		void push(MeshPtr mesh, mat4 M) {
			material.mvp(M, V, P);
			mesh->bind();
			glDrawElements(mesh->primitive, mesh->element_size, GL_UNSIGNED_SHORT, 0);
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
			target->bind();
		}

		void set_material(Material& material) {
			this->material = material;
			this->material.bind();
		}

		void set_cullface(CullFaceType type) {
			switch (type)
			{
			case CULL_NULL:
				glDisable(GL_CULL_FACE);
				break;
			case CULL_BACK:
				glEnable(GL_CULL_FACE);
				glCullFace(GL_BACK);
				break;
			case CULL_FRONT:
				glEnable(GL_CULL_FACE);
				glCullFace(GL_FRONT);
				break;
			default:
				break;
			}
		}

		void set_depth_test(bool enable) {
			depth_enable = enable;
			if (depth_enable)
			{
				glEnable(GL_DEPTH_TEST);
			}
			else {
				glDisable(GL_DEPTH_TEST);
			}
		}


	};
	typedef shared_ptr<Pipeline> PipelinePtr;

#endif
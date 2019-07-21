#ifndef ENGINE_UI_NODE_H
#define ENGINE_UI_NODE_H
#include"tree_node.h"
#include"gxo_math.h"
#include"gxo_rect.h"
#include"resource.h"
#include"renderpass.h"
#include"gxo_log.h"
#include"gpu_api.h"
#include"gxo_concept.h"
class Render;
namespace gxo {
	class UiNode :public TreeNode
	{
	public:
		ivec2 size;
		ivec2  position;

		
		UiNode();

		~UiNode()
		{
		
		}
		virtual bool on_render() {
		/*	auto render_pass= get<RenderPass*>(RENDER_PASS);
			if (render_pass == nullptr) return true;
			switch (render_pass->type) {
			case 0: return true;
			case 1: draw_image(); break;
			case 2: draw_text(); break;
			case 3: draw_color(); break;
			}*/
			on_render_begin();
			for (auto child : children) {
				child->on_render();
			}
			on_rendre_end();
			return true;

		}


		virtual void on_render_begin() {
			draw_rect();
		}

		virtual void on_rendre_end() {
			//结束fbo（fboend 。。。）
		}

		virtual void on_layout_begin() {
			
		}

		virtual void on_layout_end() {
		
		}



		virtual Rect on_layout(Rect &rect_parent) {
			on_layout_begin();
			{
				position.x = rect_parent.x;
				position.y = rect_parent.y;
				size.x = rect_parent.width;
				size.y = rect_parent.height;

				ivec2 layout_size;
				if (get<ivec2>(LAYOUT_SIZE, layout_size)) {
					size = layout_size;
				}

				ivec2 pos;
				Align align_x;
				Align align_y;
				if (get<ivec2>(POSITION, pos)) {
					position = pos;
				}
				
				if (get<Align>(ALIGN_X, align_x)) {
					switch (align_x)
					{
					case gxo::ALIGN_LEFT:
						break;
					case gxo::ALIGN_CENTER:
						position.x += (int) (rect_parent.width/2.0f - size.x / 2.0f)+ pos.x;
						break;
					case gxo::ALIGN_REIGHT:
						position.x += rect_parent.width  - size.x + pos.x;
						break;
					}
				}

				if (get<Align>(ALIGN_Y, align_y)) {
					switch (align_y)
					{
					case gxo::ALIGN_CENTER:
						position.y += (int)(rect_parent.height / 2.0f - size.y / 2.0f) + pos.y;
						break;
					case gxo::ALIGN_TOP:
						break;
					case gxo::ALIGN_BOTTOM:
						position.x += rect_parent.height - size.y + pos.y;
						break;
					default:
						break;
					}
				}
			}
			
			on_layout_end();

			Rect rect_self;
			rect_self.set(position, size);
			for (auto child : children) {
				auto ui_node = dynamic_cast<UiNode*>(child);
				ui_node->on_layout(rect_self);
			}
			return rect_self;
		}
/////////////////////////////////////////////////////////////////////////////////
		void draw_text() {
			info("draw_text");
		}

		void draw_image() {
			info("draw_image");
		}

		void draw_color() {
	/*		info("draw_color");
			glEnable(GL_SCISSOR_TEST);
			glScissor(position.x, position.y, size.x, size.y);
			glClearColor(position.x/ 1000.0f, 0.5f, size.y/1000.0f,1.0f);
			glClear(GL_COLOR_BUFFER_BIT);*/

	//		glDisable(GL_DEPTH_TEST);
	//		glClearDepth(1.0);
	//		glEnable(GL_BLEND);
	//		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//		glEnable(GL_SCISSOR_TEST);
	//		glScissor(50, 50, 400, 400);
	//		
	//		glClearColor(0.2f, 0.5f, 0.6f, 0.5f);
	//		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
	//		//glDepthMask(GL_FALSE);

	//		glScissor(200, 350, 100, 100);
	//		glClearColor(0.8f, 0.5f, 0.6f, 0.50f);
	//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//		//glDepthMask(GL_TRUE);
	//		glScissor(0, 0, 800, 800);
	//		glBegin(GL_TRIANGLES);

	//glColor4f(1.0, 0.0, 0.0,0.5);    // Red
	//glVertex3f(0.0, 1.0, 0.0);

	//glColor3f(0.0, 1.0, 0.0);    // Green
	//glVertex3f(-1.0, -1.0, 0.0);

	//glColor3f(0.0, 0.0, 1.0);    // Blue
	//glVertex3f(1.0, -1.0, 0.0);

	//glEnd();
		}


		void draw_rect();

/////////////////////////////////////////////////////////////////////
		void on_pre_render() {

		}

		void on_render_start() {
			//判断renderer 属性是用了哪种渲染器
			//结合renderpass属性 使用renderscript

			//给渲染器发送命令  如  
			//绘制图片（image , ptr , x,y width, height）
			//绘制文本 （text , texturePtr , x,y width, height）
			//开始绘制到fbo （fbostart 。。）
			
			

			//render pass script

			//todo 解决渲染的fbo依赖问题 

			//可以给渲染器 添加自定义或系统自带的渲染工作
		}
		//void on_rendre_end() {
		//	//结束fbo（fboend 。。。）
		//}

		void on_post_render() { //性能  todo 把post render整合进render过程

		}
	private:

	};
}
#endif 

#ifndef ENGINE_UI_NODE_H
#define ENGINE_UI_NODE_H
#include"tree_node.h"
#include"gxo_math.h"
namespace gxo {
	class UiNode :public TreeNode
	{
	public:
		vec2  size;
		vec2  position;
		vec2  rotate;
		vec2  scale;

		UiNode()
		{
		}

		~UiNode()
		{
		}

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
		void on_rendre_end() {
			//结束fbo（fboend 。。。）
		}

		void on_post_render() { //性能  todo 把post render整合进render过程

		}
	private:

	};
}
#endif 

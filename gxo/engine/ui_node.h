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
			//�ж�renderer ����������������Ⱦ��
			//���renderpass���� ʹ��renderscript

			//����Ⱦ����������  ��  
			//����ͼƬ��image , ptr , x,y width, height��
			//�����ı� ��text , texturePtr , x,y width, height��
			//��ʼ���Ƶ�fbo ��fbostart ������
			
			

			//render pass script

			//todo �����Ⱦ��fbo�������� 

			//���Ը���Ⱦ�� ����Զ����ϵͳ�Դ�����Ⱦ����
		}
		void on_rendre_end() {
			//����fbo��fboend ��������
		}

		void on_post_render() { //����  todo ��post render���Ͻ�render����

		}
	private:

	};
}
#endif 

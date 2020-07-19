#ifndef GXO_KEY_ANIMATION_H
#define GXO_KEY_ANIMATION_H
namespace gxo {
	class KeyAnimation
	{
	public:
		enum status;
		int times;
		float during;
		
		enum mode; //loop reserve pingpong
		enum easing;
		AnimationListenerPtr listener;

		//Evaluator
		std::vector< Channel> Channels;

	public:
		KeyAnimation() {}

		virtual void start() {}
		virtual void restart() {}
		virtual void pause() {}
		virtual void stop() {}
		virtual void process(TreeNode *){}
		
	private:
		float time_pass;
	};
}
#endif
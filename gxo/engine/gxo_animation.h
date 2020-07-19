#ifndef GXO_ANIMATION_H
#define GXO_ANIMATION_H
namespace gxo {
	class Animation 
	{
	public:
		int times;

		AnimationListenerPtr listener;
	public:
		Animation() {}

		virtual void start(){}
		virtual void restart(){}
		virtual void pause(){}
		virtual void stop(){}
	private:

	};
}
#endif
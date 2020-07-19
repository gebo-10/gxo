#ifndef GXO_CHANNEL_H
#define GXO_CHANNEL_H
namespace gxo {
	class Key {
		float time;
		std::any value;
	};
	class Channel
	{
	public:
		PropertyNmae property;
		Sampler sampler;//int float color vec2 vec3 vec4  quat transform  path curve
		std::vector< Key> keys;
	public:
		Channel() {}
		virtual void process(TreeNode* node, percent,easing) {
			percent=easing.get(percent);
			sampler.get(node,percent);

		
		}

		

	private:

	};
}
#endif
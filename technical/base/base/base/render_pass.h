#ifndef RENDER_PASS_H
#define RENDER_PASS_H
#include<vector>
#include"pass.h"
class RenderPass
{
public:
	std::vector<Pass> subpass;
	//resource
	RenderPass()
	{
	}

	~RenderPass()
	{
	}

	void process() {}
	void parse() {}
private:

};

#endif

#ifndef PASS_H
#define PASS_H
#include<vector>
class Pass
{
public:
	std::vector<Pass> subpass;
	void* input;
	void* output;
	Pass()
	{
	}

	~Pass()
	{
	}
	
	virtual void process() {}
private:

};

#endif

#ifndef CLEARCOLOR
#define CLEARCOLOR
#include "module.h"
class ClearColor :public Module
{
public:
	ClearColor()
	{
	}

	~ClearColor()
	{
	}

	virtual void init() {
		glClearColor(1.0, 0.5, 0.2, 1.0);
	}
	virtual void render() {
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

	}

	virtual void key(int key) {}

	virtual void mouse(int button, int x, int y) {}

private:

};

#endif
#include<iostream>
#pragma comment(lib,"OpenGL32.lib")

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include"gxo.h"
int main(void) {
	gxo::init();
	gxo::run();
	system("pause");
	return 0;
}


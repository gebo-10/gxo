#include<iostream>
#pragma comment(lib,"OpenGL32.lib")
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"Iphlpapi.lib")
#pragma  comment(lib,"Psapi.lib")
#pragma  comment(lib,"Userenv.lib")
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include"gxo.h"
int main(void) {
	gxo::init();
	gxo::run();
	gxo::clear();
	return 0;
}


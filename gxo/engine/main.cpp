#pragma comment(lib,"OpenGL32.lib")
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"Iphlpapi.lib")
#pragma  comment(lib,"Psapi.lib")
#pragma  comment(lib,"Userenv.lib")

#pragma comment(lib, "libuv.lib")
#pragma comment(lib, "glew32sd.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "kernel32.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "winspool.lib")
#pragma comment(lib, "comdlg32.lib")
#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "oleaut32.lib")
#pragma comment(lib, "uuid.lib")
#pragma comment(lib, "odbc32.lib")
#pragma comment(lib, "odbccp32.lib")

#include<iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include"gxo.h"
int main(void) {
	gxo::init();
	gxo::run();
	gxo::clear();
	return 0;
}


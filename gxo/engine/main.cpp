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
#pragma comment(lib, "freetype.lib")

#include"gxo.h"
using namespace gxo;
bool init() {
	std::cout << "gxo::init" << std::endl;
	Engine::instacne().init();
	return true;
}

bool run() {
	std::cout << "gxo::run" << std::endl;
	Engine::instacne().start();
	return true;
}
bool clear() {
	std::cout << "gxo::clear" << std::endl;
	Engine::instacne().clear();
	return true;
}

int main(void) {
	init();
	run();
	clear();
	return 0;
}


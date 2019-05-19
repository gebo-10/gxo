#ifndef _GXO_GXO_H
#define _GXO_GXO_H
#include"engine.h"
#include<iostream>
namespace gxo {
	static bool init() {
		std::cout << "gxo::init" << std::endl;
		return true;
	}

	static bool run() {
		std::cout << "gxo::run" << std::endl;
		Engine::instacne().init();
		return true;
	}

};
#endif
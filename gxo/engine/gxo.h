#ifndef _GXO_GXO_H
#define _GXO_GXO_H
#include"engine.h"
#include<iostream>
namespace gxo {
	static bool init() {
		std::cout << "gxo::init" << std::endl;
		Engine::instacne().init();
		return true;
	}

	static bool run() {
		std::cout << "gxo::run" << std::endl;
		Engine::instacne().start();
		return true;
	}
	static bool clear() {
		std::cout << "gxo::clear" << std::endl;
		Engine::instacne().clear();
		return true;
	}
};
#endif
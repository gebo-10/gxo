// ptr_deleter.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <memory>
#include<iostream>
#include<functional>
std::shared_ptr<int> c;
void deleter(int* ptr) {
	std::cout << "clcllclcl";
	c=std::shared_ptr<int> (ptr);
}

void fun(std::function<int(float)> fun2) {
	fun2(3.0);
}

struct a
{
	int &b;
	int x;
};
int main()
{
	float c = sizeof(a);
	auto pc = new int(c);
	std::shared_ptr<int> spi(pc, deleter);
	std::weak_ptr<int> wpi = spi;

	auto p2 = spi;
	spi.~shared_ptr();
	p2.~shared_ptr();

	
	auto tg = wpi.lock();
	std::shared_ptr<int> tg2(tg.get(), deleter);
	tg.~shared_ptr();
	tg2.~shared_ptr();
	fun([&](float a)->int {
		return a+ c;
	});

	auto i = *pc;
	getchar();
    return i;
}


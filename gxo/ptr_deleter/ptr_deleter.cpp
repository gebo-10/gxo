// ptr_deleter.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <memory>
#include<iostream>
#include<functional>
void deleter(int* ptr) {
	std::cout << "clcllclcl";
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
	std::shared_ptr<int> spi(new int(c), deleter);
	auto p2 = spi;
	spi.~shared_ptr();
	p2.~shared_ptr();
	fun([&](float a)->int {
		return a+ c;
	});
    return 0;
}


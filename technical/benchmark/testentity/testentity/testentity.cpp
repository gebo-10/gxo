// testentity.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <stdio.h>
#include <intrin.h>
#include <iostream>
#include<Windows.h>
#pragma intrinsic(__rdtsc)
int data[10] = { 0,9,8,3,2,5,1,7,6,4 };
size_t test(int aim) {
	for (size_t i = 0; i < 10; i++)
	{
		if (data[i] == aim) {
			return i;
		}
	}
}

size_t test2(int aim) {
	for (size_t i = 0; i < 10; i++)
	{
		return data[aim];
	}
}

int main()
{
	unsigned __int64 start;
	unsigned __int64 second;
	start = __rdtsc();
	std::cout << "Hello World!\n";
	printf_s("%I64d ticks\n", __rdtsc() - start);

	start = __rdtsc();
	Sleep(1000);
	second = __rdtsc() - start;
	printf_s("%I64d ticks\n", second);


	start = __rdtsc();
	for (size_t i = 0; i < 1000000; i++)
	{   
		test2(rand() % 10);
	}
	unsigned __int64 now=__rdtsc() - start;
	printf_s("%I64d ticks\n", now);
	std::cout << (now / (double)second);
}

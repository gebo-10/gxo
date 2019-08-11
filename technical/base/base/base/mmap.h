#ifndef MMAP_H
#define MMAP_H
#include "core_base.h"
#include <windows.h>
class Mmap
{
public:
	LPSTR memery;
	DWORD filesize;
	HANDLE hMap;
	HANDLE hFile = INVALID_HANDLE_VALUE;

	Mmap(string_view filename)
	{
		//LPCWSTR file = TEXT(filename.c_str());
		hFile = CreateFile(     //创建或打开文件内核对象
			filename.data(),
			GENERIC_WRITE | GENERIC_READ,
			FILE_SHARE_WRITE | FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL
		);

		if (hFile == INVALID_HANDLE_VALUE)
		{
			error("CreateFile error:{}", filename);
			return ;
		}

		filesize = GetFileSize(hFile, NULL);
		//创建一个文件映射内核对象
		hMap = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, filesize, NULL);
		if (hMap == INVALID_HANDLE_VALUE)
		{
			error("CreateFileMapping error:{}", filename);
			return;
		}

		//将文件数据映射到进程的地址空间
		memery = (LPSTR)MapViewOfFile(hMap, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, filesize);
		if (memery == NULL)
		{
			error("MapViewOfFile error:{}", filename);
			return ;
		}

	}

	~Mmap()
	{

		UnmapViewOfFile(memery);
		CloseHandle(hMap);
		CloseHandle(hFile);
	}


};

#endif
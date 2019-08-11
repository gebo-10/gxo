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
		hFile = CreateFile(     //��������ļ��ں˶���
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
		//����һ���ļ�ӳ���ں˶���
		hMap = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, filesize, NULL);
		if (hMap == INVALID_HANDLE_VALUE)
		{
			error("CreateFileMapping error:{}", filename);
			return;
		}

		//���ļ�����ӳ�䵽���̵ĵ�ַ�ռ�
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
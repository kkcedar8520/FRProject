#pragma once

#include"JH_DXStd.h"
class BinaryReader
{
	FILE* m_fp;
public:
	bool Open(const std::string Path);
	bool Close();
public:
	std::string String();
	std::wstring WString();
	bool Bool();
	int Int();
	float Float();
	DWORD Dword();
	void Byte(void* Data, int size, int length);
};


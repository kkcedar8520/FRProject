#pragma once

#include"JH_DXStd.h"

class BinaryWriter
{
	FILE* m_fp;
public:
	bool Open(const std::string Path);
	bool Close();
public:
	bool String(const std::string Str);
	bool Bool();
	bool Int(int iData);
	bool Float(float f);
	void Byte(void* Data, int size,int length);
};


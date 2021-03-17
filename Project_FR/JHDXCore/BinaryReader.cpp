#include "BinaryReader.h"

bool BinaryReader::Open(const std::string Path)
{
	m_fp = fopen(Path.c_str(), "rb");
	
	if (m_fp == nullptr) { return false; }
	return true;
}
bool BinaryReader::Close()
{
	fclose(m_fp);
	return true;
}


std::string BinaryReader::String()
{
	int ibuf=0;
	char Temp[255];
	char cbuf[255];
	fread(&ibuf, sizeof(int), 1, m_fp);
	fread((void*)cbuf, sizeof(char), ibuf, m_fp);

	strncpy_s(Temp, cbuf, sizeof(char)*ibuf);
	memset(cbuf, 0, sizeof(char) * 255);
	
	std::string sbuf = Temp;
	return sbuf;
}
std::wstring BinaryReader::WString()
{
	int ibuf = 0;
	TCHAR Temp[255] = {};
	TCHAR cbuf[255] = {};

	std::wstring sbuf;
	fread(&ibuf, sizeof(int), 1, m_fp);
	fread((void*)cbuf, sizeof(TCHAR), ibuf, m_fp);


	_tcsncpy(Temp, cbuf, sizeof(TCHAR)*ibuf);
	

	sbuf= Temp;



	return sbuf;
}
bool BinaryReader::Bool()
{
	bool b;
	fread(&b, sizeof(bool), 1, m_fp);
	return b;

}
DWORD BinaryReader::Dword()
{
	DWORD d;
	fread(&d, sizeof(DWORD), 1, m_fp);
	return d;
}
int BinaryReader::Int()
{
	int ibuf;
	fread(&ibuf, sizeof(int), 1, m_fp);
	return ibuf;
}
float BinaryReader::Float()
{
	float fbuf = 0;
	fread(&fbuf, sizeof(float), 1, m_fp);
	return fbuf;
}
void BinaryReader::Byte(void* Data, int size, int length)
{
	fread(Data, size, length,m_fp);
}
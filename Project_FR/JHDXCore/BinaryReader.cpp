#include "BinaryReader.h"

bool BinaryReader::Open(const std::string Path)
{
	m_fp = fopen(Path.c_str(), "rb");
	
	
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
	std::string sbuf;
	fread(&ibuf, sizeof(int), 1, m_fp);
	fread((void*)sbuf.c_str(), sizeof(char), ibuf, m_fp);
	
	return sbuf;
}
bool BinaryReader::Bool()
{
	return true;
}
int BinaryReader::Int()
{
	int ibuf[6] = {};
	fread(&ibuf[0], sizeof(int), 1, m_fp);
	return ibuf[0];
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
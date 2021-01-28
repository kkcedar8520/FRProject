#include"BinaryWriter.h"


bool BinaryWriter::Open(const std::string Path)
{
	m_fp = fopen(Path.c_str(), "wt");
	return true;
}
bool BinaryWriter::Close()
{

	fclose(m_fp);
	return true;
}

bool BinaryWriter::String(const std::string Str)
{

	int ibuf = strlen(Str.c_str());
	fwrite(&ibuf, sizeof(int), 1, m_fp);
	fwrite((void*)Str.c_str(), sizeof(char), strlen(Str.c_str()), m_fp);
	return true;
}
bool BinaryWriter::Bool()
{
	return true;
}
bool BinaryWriter::Int(int iData)
{
	int ibuf[3];
	ibuf[0] = iData;
	fwrite(&ibuf[0], sizeof(int), 1, m_fp);
	return true;
}
bool BinaryWriter::Float(float f)
{
	return true;
}

void BinaryWriter::Byte(void* Data, int size,int length)
{
	fwrite(Data, size, length, m_fp);
}
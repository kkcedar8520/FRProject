#include"BinaryWriter.h"


bool BinaryWriter::Open(const std::string Path)
{
	m_fp = fopen(Path.c_str(), "wb");
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
bool BinaryWriter::String(const std::wstring Str)
{

	int ibuf = lstrlenW(Str.c_str());
	fwrite(&ibuf, sizeof(int), 1, m_fp);
	fwrite((void*)Str.data(), sizeof(TCHAR), ibuf, m_fp);
	return true;
}
bool BinaryWriter::Bool(bool b)
{
	fwrite(&b, sizeof(bool), 1, m_fp);
	return true;
}
bool BinaryWriter::Int(int iData)
{
	int ibuf = iData;

	fwrite(&ibuf, sizeof(int), 1, m_fp);
	return true;
}
bool BinaryWriter::Float(float f)
{

	fwrite(&f, sizeof(float), 1, m_fp);
	return true;
}

void BinaryWriter::Byte(void* Data, int size,int length)
{
	fwrite(Data, size, length, m_fp);
}
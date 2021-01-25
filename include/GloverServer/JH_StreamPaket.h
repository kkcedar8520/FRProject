#pragma once

#include"ObjectPool.h"
#include"Protocol.h"

#define MAX_RECV_STREAM_SIZE 2048
class User;
enum Mode
{
	MODE_ZERORECV = 0,
	MODE_RECV,
	MODE_SEND,
};
struct  OVERLAPPED_EX
{

	OVERLAPPED OV;
	int iMode;
	OVERLAPPED_EX(int iMode)
	{
		ZeroMemory(&OV, sizeof(OVERLAPPED));
		iMode = iMode;
	}
	OVERLAPPED_EX()
	{
		ZeroMemory(&OV, sizeof(OVERLAPPED));
		iMode = MODE_ZERORECV;
	}
};
struct JPACKET
{

	UPACKET uPacket;
	User*	pUser; 
	WSABUF			buffer;
	OVERLAPPED_EX*	ov;
	SOCKET          sock;
	
};
class JH_StreamPacket
{
public:
	UPACKET*    m_pPacketStart;
	PVOID       m_pWritePos;
	PVOID 		m_pPacket;
	char		m_RecvBuffer[MAX_RECV_STREAM_SIZE];
	long long volatile	m_iStartPos;
	long long volatile	m_iWritePos;
	long long volatile	m_iReadPos;
public:
	bool    Put(char* redvBuffer, int iSize, User* = NULL);
	bool    GetPacket(User* pUser);
	bool	ParityCheck(User* pUser);
	void    Reset();
	bool AddPacket(const char* RecvBuffer, int DataSize);
	bool RecvData();
public:
	JH_StreamPacket();
	virtual ~JH_StreamPacket();
};


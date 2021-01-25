#pragma once

#include"ObjectPool.h"
#include"Protocol.h"

#define MAX_RECV_DATA_SIZE 4096


class User;
struct  OVERLAPPED_EX : ObjectPool<OVERLAPPED_EX>
{
	OVERLAPPED OV;
	int iMode;
	OVERLAPPED_EX()
	{
		ZeroMemory(&OV, sizeof(OVERLAPPED));
		iMode = MODE_ZERORECV;
	}
	OVERLAPPED_EX(int iMode)
	{
		ZeroMemory(&OV, sizeof(OVERLAPPED));
		iMode = iMode;
	}

};
struct JPACKET
{
	UPACKET Packet;
	User*	pUser;
	OVERLAPPED_EX OV;
};
class StreamPacket:public ServerObj
{
public:

	UPACKET*	m_pPacketStart;
	void*		m_pPacket;
	void*		m_pWritePos;
	void*		m_pReadPos;
	char		m_RecvBuffer[MAX_RECV_DATA_SIZE];
	long long volatile m_iStartPos;
	long long volatile m_iWritePos;
	long long volatile m_iReadPos;

public:
	bool ParityCheck(User*pUser);
	bool GetPacket(User *pUser);
	bool Put(const User& pUser,char*recvBuffer,int iRecvSize);
public:
	StreamPacket();
	virtual ~StreamPacket();
};


#pragma once
#include"NetStd.h"

class StreamPacket
{
public:
	char Recvbuffer[PACKET_MAX_SIZE];
	int iWritePos;
	char* pWritePos;
	UPACKET* m_pRecvPacket;
public:
	bool AddBuffer(SOCKET sock);
	bool RecvData();
public:
	StreamPacket();
	virtual ~StreamPacket();
};


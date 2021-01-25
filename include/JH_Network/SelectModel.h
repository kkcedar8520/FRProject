#pragma once
#include"NetStd.h"

class SelectModel
{
public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
public:
	SOCKET m_Socket;
	int m_iWritePos;
	char* m_pWritePos;
	char m_Recvbuffer[PACKET_MAX_SIZE];
public:
	 bool SendMsg(SOCKET sock, UPACKET&Packet);
	 bool SendMsg(SOCKET sock, const char*buf, int iLength);
	 bool RecvData(SOCKET sock);
	 bool RecvMsg(SOCKET sock,char* Buffer,int iSize);
public:
	SelectModel();
	virtual ~SelectModel();
};


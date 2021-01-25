#pragma once
#include"StreamPacket.h"
#include"JH_Thread.h"
#include"Lock.h"
#include"SelectModel.h"

typedef void(*CallFuction)(UPACKET&t);

class Network:public JH_Thread
{
public:
	std::shared_ptr<SelectModel> m_pModel;
	SOCKET m_Socket;
	SOCKADDR_IN m_sockaddr;
	StreamPacket m_StreamPacket;
	int m_PortNumber;

public:
	static bool m_bConnect;
	static std::list<UPACKET>m_Recvlist;
	static std::list<UPACKET>m_Sendlist;
	static std::map<int, CallFuction> m_funtionExcute;

public:
	void PacketProcess();
	void CloseSocket();
	bool CreateSocket(int iSocketType, u_long Mode);
	bool SetModel(std::shared_ptr<SelectModel> pModel);
	bool ShutDown();
	virtual bool Init();
	virtual bool Frame();
	virtual bool Release();
	virtual bool Run()override;
public:
	static bool SendMsg(SOCKET sock, UPACKET&Packet);
	static bool SendMsg(SOCKET sock, const char*buf, int iLength); // ±¸¹öÀü
public:
	Network();
	virtual ~Network();
};


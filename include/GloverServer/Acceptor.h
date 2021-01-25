#pragma once
#include"JH_Thread.h"
#include"SessionMgr.h"
class Acceptor:public JH_Thread
{
public:
	SOCKET m_listenSock;
	
public:
	bool Run()override;
	bool Setting(int iPort, const char* addr=0 );
public:
	Acceptor();
	virtual ~Acceptor();
};


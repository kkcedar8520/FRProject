#pragma once
#include"Network.h"
class User
{
public:
	SOCKET m_Socket;
	SOCKADDR_IN m_SocketAddrIn;
	bool m_Connect;
public:
	User();
	virtual ~User();
};


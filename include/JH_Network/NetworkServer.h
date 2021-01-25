#pragma once
#include"Network.h"
#include"User.h"

class NetworkServer:public Network
{
public:
	bool Run()override;
	static std::list<User>userList;
public:
	bool CreateServer(const char* addr, int iSocketType, int PortNumber, u_long Mode = 0);
	void GreetMessage(SOCKET sock, SOCKADDR_IN sock_addr);
	bool StdSelectRun();
public:
	NetworkServer();
	virtual ~NetworkServer();
};


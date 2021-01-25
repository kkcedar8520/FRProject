#pragma once
#include"Network.h"
class NetworkClient :public Network
{
public:
	bool Connect(const char* addr, int iSocketType, int PortNumber, u_long Mode = 0);
	bool RunClient();
	bool Frame();
	bool Run()override;
public:

	NetworkClient();
	virtual ~NetworkClient();
};


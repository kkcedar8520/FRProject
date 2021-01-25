#pragma once
#include"ServerObj.h"
class Lock
{
public:
	ServerObj* m_ServerObj;
public:
	Lock(ServerObj*Obj);
	virtual ~Lock();
};


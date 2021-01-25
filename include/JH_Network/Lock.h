#pragma once
#include"NetworkBase.h"
class Lock
{
	NetworkBase* m_pObj;
public:
	Lock(NetworkBase*obj);
	virtual ~Lock();
};


#pragma once
#include"Lock.h"
class Queue:public ServerObj
{
public:
	std::queue<ServerObj*> m_ObjList;
	void Push(ServerObj* pObj);
	ServerObj* Pop();
public:
	Queue();
	virtual ~Queue();
};


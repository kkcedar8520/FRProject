#pragma once
#include"ServerObj.h"
#include"WorkerThread.h"
#define MAX_THREAD_COUNT 3
class JH_IOCP:public Singleton<JH_IOCP>
{
private:
	friend class  Singleton<JH_IOCP>;
public:
	WorkerThread m_WorkerThreadHandle[MAX_THREAD_COUNT];
	HANDLE m_hIOCP;
public:
	bool Init();
	void AddSocket(HANDLE hSock, ULONG_PTR Key);
public:

	JH_IOCP();
	virtual ~JH_IOCP();
};

#define I_IOCP JH_IOCP::GetInstance()
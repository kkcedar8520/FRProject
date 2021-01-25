#pragma once
#include<process.h>
#include"NetworkBase.h"
class JH_Thread:public NetworkBase
{
public:
	unsigned int m_ThreadHandle;
	unsigned int m_ID;

public:
	virtual bool Run();
	void CreateThread();
	static unsigned int WINAPI RunHandle(LPVOID arg);
public:
	JH_Thread();
	virtual ~JH_Thread();
};


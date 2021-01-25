#pragma once
#include<process.h>
#include"ServerObj.h"

class JH_Thread :public ServerObj
{
public:
	unsigned int m_ThreadHandle;
	unsigned int m_ID;
	bool bStart;
public:
	virtual bool Run();
	void CreateThread();
	static unsigned int WINAPI RunHandle(LPVOID arg);
public:
	JH_Thread();
	virtual ~JH_Thread();
};


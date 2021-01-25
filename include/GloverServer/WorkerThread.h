#pragma once
#include"JH_Thread.h"
class WorkerThread:public JH_Thread
{
public:
	bool bLoop;
public:
	bool Run()override;
public:
	WorkerThread();
	virtual ~WorkerThread();
};


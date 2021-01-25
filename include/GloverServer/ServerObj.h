#pragma once
#include"JH_ServerStd.h"

#define RUNTIME_CLASS(s) &s::class##s;
#define DECLARE_DYNCREATE static ServerObj* CreateObj();
#define DECLARE_DYNMIC(s) static RuntimeClass class##s;

#define IMPLEMENT_DYNCREATE(s) ServerObj* s::CreateObj(){return new s;};
#define IMPLEMENT_DYNMIC(s) RuntimeClass s::class##s={#s,sizeof(s),s::CreateObj};
class ServerObj;

struct RuntimeClass
{
	char m_lpszClassName[30];
	int ClassSZ;
	ServerObj* (*ptrfunction)();
	
	ServerObj* CreateObj()
	{
		return (*ptrfunction)();
	}
};
class ServerObj
{
public:
	CRITICAL_SECTION m_CS;
public:
	ServerObj();
	virtual ~ServerObj();
};


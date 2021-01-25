#pragma once
#include"Queue.h"
#include"JH_ServerStd.h"
#include"User.h"


#define MAX_QUEUE_COUNT 1000
typedef std::map<DWORD, User*> UserList;
typedef std::map<DWORD, User*>::iterator UserIter;

class SessionMgr:public Singleton<SessionMgr>
{
private:
	friend class  Singleton< SessionMgr>;
public:
	HANDLE m_hMutex;
	UserList m_UserList;
	Queue m_QueueList;
public:
	UserList GetUserList();
	void RemoveSession(ServerObj*pSession);
	void CreateSession(SOCKET SOCK, SOCKADDR_IN sockaddr);
	void AddUser(User*pUser);
	void Create(RuntimeClass* Rt);
	void Lock();
	void UnLock();
	void ReleaseAll();
	void DeleteUser(SOCKET sock);
	void DeleteUser(User*pUser);
	
public:

	SessionMgr();
	virtual ~SessionMgr();
};

#define I_Session SessionMgr::GetInstance()
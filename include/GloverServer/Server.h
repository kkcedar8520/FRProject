#pragma once
#include"Acceptor.h"
#include"PacketPool.h"


typedef std::list<JPACKET>::iterator JPacketIter;
class Server:public JH_Thread,public Singleton<Server>
{
private:


	friend class  Singleton<Server>;
public:
	Acceptor m_Acceptor;
	PacketPool			m_SendBroadcastPool;
	PacketPool			m_RecvPacketPool;
	PacketPool			m_SendPacketPool;


	typedef void(Server::*CallFuction)(JPACKET& t);
	std::map<int, CallFuction>				m_fnExecutePacket;
	typedef std::map<int, CallFuction>::iterator FunctionIterator;
public:
	bool Init();
	bool Release();
	bool Run()override;
	bool SendPacket(User* pUser,std::stringstream& Data);
	int  SendPacket(User* pUser, UPACKET& sendmsg);
	void SendPacket(User * pUser, size_t iSendByte);
	void AddRecvPacket(JPACKET pack);
	void SendBroadcastPool(UPACKET& sendmsg);
	void SendBroadcastPool(std::stringstream & SendStream);
	void SendBroadcastPacket();
	void BroadcastNewPlayer(JH_Character& player);
	void Broadcast(std::stringstream & SendStream);
public:
	//CallFunction
	void GameStart(JPACKET& t);

public:
	friend std::ostream& operator<<(std::ostream& stream, Server& sv_Info);
	
	static Server& Get()
	{
		static Server sev;
		return sev;
	}
public:
	Server();
	virtual ~Server();
};


#define I_Server Server::Get()
#pragma once
#include"JH_StreamPaket.h"
class PacketPool
{
public:
	HANDLE m_hMutex;
	std::list<JPACKET> m_PacketList;
	volatile long 		m_iLockCheck;
public:
	bool AddPacket(JPACKET Packet);
	bool PacketClear();
public:
	void Lock();
	void Unlock();
	std::list<JPACKET>& Get();

	PacketPool();
	virtual ~PacketPool();
};


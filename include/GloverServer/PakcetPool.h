#pragma once
#include"StreamPacket.h"
class PakcetPool
{
public:
	HANDLE m_hMutex;
	std::list<JPACKET> m_PaketList;
public:
	bool AddPacket(JPACKET Packet);
	bool PacketClear();
public:

	PakcetPool();
	virtual ~PakcetPool();
};


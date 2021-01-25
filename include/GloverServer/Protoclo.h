#pragma once

#include"JH_ServerStd.h"
#define PACKET_HEADER_SIZE 4
#define PACKET_MAX_MSGSZ 2048

#define PACKET_MAX_SIZE PACKET_MAX_MSGSZ+PACKET_HEADER_SIZE
#define PACKET_CHAT_MSG 1000
#pragma pack(push,1)

struct PACKETHEADER
{
	WORD len;
	WORD type;
};

struct UPACKET
{
	PACKETHEADER ph;
	char Msg[PACKET_MAX_SIZE];
};

#pragma pack(pop)


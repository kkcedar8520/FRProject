#pragma once

#include<Windows.h>
#include<map>
#include<sstream>


#define PACKET_HEADER_SIZE 10
#define PACKET_MAX_MSGSZ 2048

#define PACKET_MAX_SIZE PACKET_MAX_MSGSZ+PACKET_HEADER_SIZE

#pragma pack(push,1)

typedef struct
{
	uint16_t        iotype;	// 패킷 입출력 종류
	uint16_t    	len;	// msg 바이트 크기
	uint16_t    	type;	// 어떤 패킷이다.	
	uint32_t        time;   // 패킷 전송 시간 
}PACKET_HEADER;

struct UPACKET
{
	PACKET_HEADER ph;
	char Msg[PACKET_MAX_SIZE];
};


typedef struct {
	int   iID;
	char  name[10];
}USER_INFO;

typedef struct {
	DWORD    dwID;
	/*F  vPos;
	F  vVelocity;
	F  vRotation;*/
	float	 fHealth;
	int      iType;
	bool     bAlive;
} JPACKET_CHARACTER_INFO;


#pragma pack(pop)

enum JPACKET_TYPE
{
	PACKET_CHAT_MSG = 1000,

};

static std::ostream& operator <<(std::ostream& stream, PACKET_HEADER& h)
{
	stream.write(reinterpret_cast<char*>(&h), sizeof(PACKET_HEADER));
	return stream;
}

static std::ostream& operator <<(std::ostream& stream, JPACKET_CHARACTER_INFO& c_Info)
{
	stream.write(reinterpret_cast<char*>(&c_Info), sizeof(JPACKET_CHARACTER_INFO));
	return stream;
}

static std::ostream& operator <<(std::ostream& stream, USER_INFO& u_Info)
{
	stream.write(reinterpret_cast<char*>(&u_Info), sizeof(USER_INFO));
	return stream;
}



template<typename T>
std::istream & tBlockRead(std::istream& stream, T& value)
{
	return stream.read(reinterpret_cast<char*>(&value), sizeof(T));
}
template<typename T>
std::ostream & tBlockWrite(std::ostream& stream, T& value)
{
	return stream.write(reinterpret_cast<char*>(&value), sizeof(T));
}

static std::stringstream MakePacket(int iType, std::stringstream& Data)
{
	std::stringstream sstream;
	PACKET_HEADER Pheader;
	Pheader.iotype = 0;
	Pheader.type = iType;
	Pheader.len = (PACKET_HEADER_SIZE + Data.str().length());

	sstream << Pheader << Data.str().c_str();

	return move(sstream);
}
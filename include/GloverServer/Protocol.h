#pragma once


#include"TMath.h"

#define PACKET_HEADER_SIZE 10
#define PACKET_MAX_MSGSZ 2048

#define PACKET_MAX_SIZE PACKET_MAX_MSGSZ+PACKET_HEADER_SIZE

#pragma pack(push,1)

struct PACKETHEADER
{
	uint16_t        iotype;	// 패킷 입출력 종류
	uint16_t    	len;	// msg 바이트 크기
	uint16_t    	type;	// 어떤 패킷이다.	
	uint32_t        time;   // 패킷 전송 시간 
};

struct UPACKET
{
	PACKETHEADER ph;
	char Msg[PACKET_MAX_SIZE];
};


typedef struct {
	int   iID;
	char  name[10];
}USER_INFO;

typedef struct {
	//DWORD    dwID;
	TCHAR    dwID[10] = {0};
	FVector  vPos;
	FVector  vVelocity;
	FRotator  vRotation;
	float	 fHealth;
	int      iType;
	bool     bAlive;
}JPACKET_CHARACTER_INFO;


#pragma pack(pop)



static std::ostream& operator <<(std::ostream& stream, PACKETHEADER& h)
{
	stream.write(reinterpret_cast<char*>(&h), sizeof(PACKETHEADER));
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

static std::stringstream MakePacket( int iType,std::stringstream& Data)
{
	std::stringstream sstream;
	PACKETHEADER Pheader;
	Pheader.iotype = 777;
	Pheader.type = iType;
	Pheader.len = (uint16_t)(PACKET_HEADER_SIZE + Data.str().length());

	sstream << Pheader << Data.str().c_str();

	return move(sstream);
}

enum Character
{
	ROCK_MAN=0,
	MEGA_MAN,
};
enum JPACKET_TYPE
{


	//채팅
	PACKET_CHAT_MSG = 1000,
	//로그인
	PACKET_LOGIN_MSG = 2000,
	PACKET_GAME_START=2001,
	//플레이어 행동
	PACKET_PLAYER_MOVE=3000,
	PACKET_PLAYER_ATTACK=3001,
	PACKET_PLAYER_JUMP=3002,

	PACKET_HIT_CHARACTER = 4000, // 케릭터 피격 받음
	PACKET_HIT_NPC, // NPC 피격 받음
	PACKET_ATTACK_CHARACTER, // 케릭터 공격 시작
	PACKET_ATTACK_NPC, // NPC 공격 시작
	PACKET_DEAD_CHARACTER, // 케릭터 죽음
	PACKET_DEAD_NPC, // NPC 죽음
	PACKET_DAMAGE_CHARACTER, // 케릭터 데미지 받음
	PACKET_DAMAGE_NPC, // NPC 데미지 받음
	PACKET_SPAWN_CHARACTER, // 케릭터 스폰
	PACKET_SPAWN_NPC, // NPC 스폰
	PACKET_SPAWN_NPC_LIST, // 
	PACKET_SYNC_CHARACTER, // 케릭터 동기화
	PACKET_SYNC_NPC_LIST, // NPC 동기화	
	PACKET_NPC_TARGETMOVE,  // NPC 타켓이동

	//
	PACKET_SELECT_CHARACTER_REQ = 5000,
	PACKET_SELECT_CHARACTER_ACK = 5001,



	//게임 
	PACKET_ZONE_ENTRY_REQ = 6000,//게임존 입장 요청
	PACKET_ZONE_ENTRY_ACK, // 게임 존 입장 응답
	PACKET_ZONE_NEW_PLAYER, // 게임 존 입장 케릭터 정보 전송
	PACKET_ZONE_PLAYERS_INFO, // 게임 존에 입장한 유저들의 플레이 케릭터 정보 전송 
	PACKET_ZONE_USER_INFO,// 게임존 유저리스트 정보(플레이어+기타(옵저버 등))
	PACKET_ZONE_TARGET_REQ, // 존 타켓 위치 요청  
	PACKET_ZONE_TARGET_ACK, // 존 타켓 위치 응답
};

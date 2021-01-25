#pragma once

#include"JH_Character.h"
#include"JH_StreamPaket.h"

#define MAX_WSA_BUFFER 1028
#define MAX_USER_RECVSIZE 4096
#define	MAX_USER_RECV_SIZE 2048

class User:public ServerObj
{
public:
	JH_StreamPacket					m_StreamPacket;
	std::map<DWORD, JH_Character>	m_CharacterList;
	OVERLAPPED_EX					m_OV;
	OVERLAPPED_EX					m_ZeroOV;
	SOCKET							m_Sock;
	SOCKADDR_IN						m_SockAddr;
	WSABUF							m_WSARecvBuf;
	WSABUF							m_WSASendBuf;
	int								m_iRecvData;
	char							m_RecvBuffer[MAX_USER_RECVSIZE];
	char							m_sendBuffer[MAX_USER_RECV_SIZE];
	DWORD							m_dwCharacter;
public:
	DWORD m_dwID;
	std::string m_strName;
public:
	DECLARE_DYNCREATE
	DECLARE_DYNMIC(User)
public:
	friend std::ostream& operator<<(std::ostream& stream, User& u_Info);
public:
	bool Dispatch(DWORD dByteSize,OVERLAPPED_EX* OV);
	bool WaitRecv();
	bool WaitZeroRecv();
	void Disconnect();
	OVERLAPPED_EX* Overlapped();
	OVERLAPPED_EX* OverlappedZero();
	User();
	virtual ~User();
};


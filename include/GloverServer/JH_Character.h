#pragma once
#include"ServerObj.h"
#include"Protocol.h"
class JH_Character:public ServerObj
{
public:
	JPACKET_CHARACTER_INFO m_Character;
public:
	friend std::ostream& operator<<(std::ostream&stream, JH_Character& C_Info);
	//friend std::ostream& operator>>(std::ostream&stream, JH_Character& C_Info);
public:
	JH_Character();
	virtual ~JH_Character();
};


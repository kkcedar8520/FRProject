#pragma once
#include"NetStd.h"
class NetworkBase
{
public:
	CRITICAL_SECTION m_CS;
public:
	NetworkBase();
	virtual ~NetworkBase();
};


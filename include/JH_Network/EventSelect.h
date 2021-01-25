#pragma once
#include"SelectModel.h"
class EventSelect:public SelectModel
{
public:
	HANDLE m_hEvent;
public:
	bool Init();
	bool Frame();
public:
	EventSelect(SOCKET sock);
	virtual ~EventSelect();
};


#pragma once
#include"SelectModel.h"
class AsyncSelect:public SelectModel
{
public:
	HWND m_hwnd;
public:
	LRESULT MsgProc(HWND hwnd, UINT Msg, WPARAM wpram, LPARAM lparam);
	bool Init();
	bool Frame();
public:
	AsyncSelect();
	virtual ~AsyncSelect();
};


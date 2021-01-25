#pragma once
#include"JH_DXStd.h"


enum KEY_ORDER
{
	KEY_FREE,
	KEY_PUSH,
	KEY_HOLD,
	KEY_UP
};
class JH_Input
{
public:

	SHORT m_KEY;
	DWORD m_StateKey[256];
	POINT m_MousePos;
	
public:
	static JH_Input&Get()
	{
		static JH_Input mgr;
		return mgr;
	}
	DWORD KeyCheck(DWORD inputkey);
	bool Init();
	bool Render();
	bool Frame();
	bool Release();
	JH_Input();
	~JH_Input();
};

#define G_Input JH_Input::Get()
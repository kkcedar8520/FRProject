#pragma once
#include"JH_DXStd.h"
extern float g_SecondPerFrame;
class JHTimer
{
public:
	TCHAR m_SzBuffer[256];
	DWORD m_DWStartTime;
	float m_fProgramTime;
	float m_SecondPerFrame;
	int m_iFPS;
public:
	int	GetFPS();
	bool Init();
	bool Render();
	bool Frame();
	bool Release();
public:
	JHTimer();
	~JHTimer();
};



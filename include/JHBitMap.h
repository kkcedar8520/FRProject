#pragma once
#include"JH_Std.h"
#include "HWindow.h"

class JHBitMap
{
public:
	std::wstring m_szName;
public:
	HBITMAP m_hBitMap;
	HDC		m_TempScreenDC;
	BITMAP  m_BMInfo;
	HWND	m_hwnd;
	RECT	m_rtDest;
	RECT	m_rtSrc;
	
public:
	void Set(RECT&rtDesk,RECT&rtSrc);

	bool LoadBitMap(const TCHAR* pFileName);
	bool Draw(RECT m_rtDest,RECT m_rtSrc);
	bool Init();
	bool Render();
	bool Frame();
	bool Release();
	JHBitMap();
	~JHBitMap();
};


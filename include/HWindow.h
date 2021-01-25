#pragma once
#include <Windows.h>
#include <tchar.h>
extern HINSTANCE g_hInstance;
extern HWND g_hwnd;
class HWindow
{
public:
	RECT m_rtClient;
	HINSTANCE m_hinstance;
	HWND m_hwnd;
	


public:
	bool initWindow(const TCHAR* pTitleName,RECT rtClient);

public:
	virtual bool init();
	virtual bool Render();
	virtual bool Release();
	virtual bool Frame();
	virtual LRESULT JWndProc(HWND,UINT, WPARAM, LPARAM);
public:
	HWindow();
		virtual ~HWindow();
};


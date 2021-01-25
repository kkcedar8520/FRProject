#pragma once
#include <Windows.h>
#include <tchar.h>
extern HINSTANCE g_hInstance;
extern HWND g_hwnd;
class JHWindow
{
public:
	RECT m_rtClient;
	HINSTANCE m_hinstance;
	HWND m_hwnd;

public:
	bool InitWindow(const TCHAR* pTitleName, RECT rtClient);

public:
	virtual bool init();
	virtual bool Render();
	virtual bool Release();
	virtual bool Frame();
	virtual LRESULT JWndProc(HWND, UINT, WPARAM, LPARAM);
public:
	virtual bool ResizeDevice(UINT width, UINT height);
public:
	JHWindow();
	virtual ~JHWindow();
};


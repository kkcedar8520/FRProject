#include "JHWindow.h"



JHWindow* g_pWnd;
HINSTANCE g_hInstance;
HWND g_hwnd;
RECT g_rtClient;

bool JHWindow::ResizeDevice(UINT width, UINT height)
{
	return true;
}
LRESULT CALLBACK S_JWndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM iparam)
{
	int iRET = g_pWnd->JWndProc(hwnd, message, wparam, iparam);
	if (iRET >= 0)
	{
		return 1;
	}
	switch (message)
	{
	case WM_SIZE:
	{
		if (SIZE_MINIMIZED!=wparam)
		{
			UINT width = LOWORD(iparam);
			UINT height = HIWORD(iparam);
			GetClientRect(g_hwnd, &g_pWnd->m_rtClient);
			g_rtClient = g_pWnd->m_rtClient;
			g_pWnd->ResizeDevice(width, height);
		}
	}break;
	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}break;
	}
	return DefWindowProc(hwnd, message, wparam, iparam);


}
JHWindow::JHWindow()
{
	g_pWnd = this;
}


JHWindow::~JHWindow()
{
}
bool JHWindow::InitWindow(const TCHAR* pTitleName, RECT rtClient)
{
	g_hInstance = m_hinstance;
	// 윈도우 클래스 레지스터 등록
	WNDCLASSEX wndcex;
	ZeroMemory(&wndcex, sizeof(WNDCLASSEX));
	wndcex.cbSize = sizeof(WNDCLASSEX);
	wndcex.style = CS_HREDRAW | CS_VREDRAW;
	wndcex.lpfnWndProc = S_JWndProc;
	wndcex.hInstance = m_hinstance;
	wndcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndcex.lpszClassName = L"H.WindowSample";
	wndcex.lpszMenuName = NULL;
	if (!RegisterClassEx(&wndcex))
		return false;


	AdjustWindowRect(&rtClient, WS_OVERLAPPEDWINDOW, FALSE);


	m_hwnd = CreateWindowEx(WS_EX_APPWINDOW,
		L"H.WindowSample",
		NULL,

		WS_OVERLAPPEDWINDOW,

		0, 0, rtClient.right - rtClient.left, rtClient.bottom - rtClient.top,
		NULL,
		NULL,
		m_hinstance,
		NULL);

	if (!m_hwnd)
	{
		return false;
	}
	GetClientRect(m_hwnd, &m_rtClient);

	g_hwnd = m_hwnd;
	g_rtClient = m_rtClient;
	ShowWindow(m_hwnd, SW_SHOW);
	return true;

}
LRESULT  JHWindow::JWndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	return -1;
}
bool  JHWindow::init()
{
	return true;
}
bool JHWindow::Render()
{
	return true;
}

bool JHWindow::Release()
{
	return true;
}
bool JHWindow::Frame()
{
	return true;
}
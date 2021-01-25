#pragma once
#include "JH_DxStd.h"
#include <d2d1.h>
#include <dwrite.h>
#include <queue>
#pragma comment( lib, "d2d1.lib")
#pragma comment( lib, "dwrite.lib")
struct tMsg
{
	RECT rt;
	wstring msg;
	D3DCOLORVALUE color;
	tMsg()
	{
		color = D2D1::ColorF(1, 0, 0, 1);
	}
};
class JH_DxWrite
{
public:
	ID2D1Factory*		m_pD2DFactory;
	IDWriteFactory*		m_pDWriteFactory;
	ID2D1RenderTarget*	m_pRT;
	IDWriteTextFormat*  m_pTextFormat;
	ID2D1SolidColorBrush*	m_pBlackBrush;
	float m_fdpiX;
	float m_fdpiY;
	float m_fDPIScaleX;
	float m_fDPIScaleY;
	std::list<tMsg> m_textList;
public:
	bool Release();
	bool Set(HWND hWnd, int iWidth,
		int iHeight, IDXGISurface* pSurface);
	HRESULT CreateDeviceIndependentResources();
	HRESULT CreateDeviceResources(IDXGISurface* pSurface);
	bool    DiscardDeviceResources();

	bool Begin();
	bool DrawText(RECT rt, const TCHAR* pText, D2D1::ColorF color);
	bool End();

	bool Render();
	void Add(const TCHAR* pMsg, D2D1::ColorF color = D2D1::ColorF(1, 0, 0, 1),
		RECT rt = g_rtClient);
	void OnResize(UINT with, UINT height, IDXGISurface* pSurface);
public:
	JH_DxWrite();
	virtual ~JH_DxWrite();
};


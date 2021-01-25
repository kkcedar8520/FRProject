#pragma once


#include"Device.h"
#include"JHTimer.h"
#include"JH_DebugCamera.h"
#include"JH_DxWrite.h"
#include"ModelView.h"
#include"JH_BackViewCamera.h"
class JHDXCore :public Device
{
public:
	bool m_bWireFrame;
	bool m_gamerun;
	JHCamera	m_DefaultCamera;
	JHCamera*	m_pMainCamera;
	JH_DxWrite	m_Write;
	shared_ptr<ModelView> m_ModelCamera;
	
	std::shared_ptr<JH_DebugCamera> m_DebugCamera;
	shared_ptr<JH_BackViewCamera> m_pBackViewCamera;
public:
	bool PostRender();
	bool PreRender();
	virtual bool Init();
	virtual bool Render();
	virtual bool Frame();
	virtual bool Release();
	virtual LRESULT  JWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	HRESULT DeleteDXResource();
	HRESULT	CreateDXResource();
	void DrawDebug();
	JHTimer	m_Timer;

public:
	bool CoreInit();
	bool CoreRender();
	bool CoreFrame();
	bool CoreRelease();
	bool Run();
public:
	JHDXCore();
	virtual ~JHDXCore();
};


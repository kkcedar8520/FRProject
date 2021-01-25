#pragma once
#include"JHTimer.h"
#include"JH_Input.h"
#include "HWindow.h"
#include "HLinkedList.h"
#include"JHBitMap.h"


class HCore :public HWindow
{
public:
	HDC m_hScreenDC;
	HDC m_hOffScreenDC;
	HBITMAP	 m_hOffScreenBM;
	JH_Input m_Input;
	JHTimer m_GameTimer;
	bool m_gamerun;
public:
	bool PostRender();
	bool PreRender();
	virtual bool Init();
	virtual bool Render();
	virtual bool Frame();
	virtual bool Release();
public:
	bool CoreInit();
	bool CoreRender();
	bool CoreFrame();
	bool CoreRelease();
	bool Run();
public:
	HCore();
	virtual ~HCore();
};


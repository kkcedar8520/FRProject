#pragma once
#include"JHCamera.h"
class JH_DebugCamera:public JHCamera
{
public:
	float m_fYaw;
	float m_fRoll;
	float m_fPitch;
	bool  m_bDrag;
	POINT m_LastPosition;
public:
	void Update(D3DXVECTOR4 value);
	virtual void UpdateCameraHeight(float Height);
	//void MsgProc(HWND hWnd,
	//	UINT msg,
	//	WPARAM wParam, LPARAM lParam)override;
public:
	bool Frame()override;

	JH_DebugCamera();
	virtual ~JH_DebugCamera();
};


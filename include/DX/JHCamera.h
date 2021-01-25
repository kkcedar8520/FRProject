#pragma once
#include"JH_Frustum.h"
#include "JH_DXStd.h"
#include"HArcBall.h"
class JHCamera
{
public:
	HArcBall  m_WorldArcBall;
	HArcBall  m_ViewArcBall;
	JH_Frustum m_Frustum;

	D3DXMATRIX m_matWorld;
	D3DXMATRIX m_matView;
	D3DXMATRIX m_matProj;
	D3DXMATRIX m_matOrthoProj;
	D3DXVECTOR3 m_vPos;
	D3DXVECTOR3 m_vAt;
	D3DXVECTOR3 m_vDefaultUp;
	D3DXVECTOR3 m_vBackPos;

	D3DXVECTOR3 m_vLookup;
	D3DXVECTOR3 m_vSide;
	D3DXVECTOR3 m_vUp;


	float m_fNear;
	float m_fFar;
	float m_fFovY;
	float m_fAspect; 

	float m_fYaw;
	float m_fPitch;
	float m_fRoll;
	float m_fRadius;
	bool  m_bDrag;
	POINT m_LastPos;
	int   m_nMouseWhellDelta;
	float m_fMaxRadius;
	float m_fMinRadius;
public:
	F_POSITION CheckOBBInPlane(BOUNDINGBOX& box);
public:
	virtual bool	UpdateBasisVector();
	virtual bool	SetViewProj();

	virtual bool	Init() { return true; };
	virtual bool	Frame();
	virtual bool	Render() { return true; };
	virtual bool	Release() { return true; };
	virtual void	Update(D3DXVECTOR3 value);

	virtual void MsgProc(HWND hWnd,
		UINT msg,
		WPARAM wParam, LPARAM lParam);
	virtual void	CreateViewMatrix(D3DXVECTOR3 pos,
		D3DXVECTOR3 target,
		D3DXVECTOR3 up = D3DXVECTOR3(0, 1, 0));
	virtual void	CreateProjMatrix(float fNear,
		float fFar,
		float fFovY,
		float fAspect);
public:
	JHCamera();
	virtual ~JHCamera();
};


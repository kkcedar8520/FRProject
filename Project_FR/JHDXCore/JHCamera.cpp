#include "JHCamera.h"
#include "JH_Input.h"

 void JHCamera::Update(D3DXVECTOR3 value)
{

}
void JHCamera::MsgProc(HWND hWnd,
	UINT msg,
	WPARAM wParam, LPARAM lParam)
{
	if (msg == WM_LBUTTONDOWN)
	{
		int iMouseX = LOWORD(lParam);
		int iMouseY = HIWORD(lParam);
		m_ViewArcBall.OnBegin(iMouseX, iMouseY);
	}
	if (msg == WM_RBUTTONDOWN)
	{
		int iMouseX = LOWORD(lParam);
		int iMouseY = HIWORD(lParam);
		m_WorldArcBall.OnBegin(iMouseX, iMouseY);
	}
	if (msg == WM_LBUTTONUP)
	{
		m_ViewArcBall.OnEnd();
	}
	if (msg == WM_RBUTTONUP)
	{
		m_WorldArcBall.OnEnd();
	}
	if (msg == WM_MOUSEMOVE)
	{
		int iMouseX = LOWORD(lParam);
		int iMouseY = HIWORD(lParam);
		m_WorldArcBall.OnMove(iMouseX, iMouseY);
		m_ViewArcBall.OnMove(iMouseX, iMouseY);
	}
	if (msg == WM_MOUSEWHEEL)
	{
		m_nMouseWhellDelta = (short)HIWORD(wParam);
	}
}
bool	JHCamera::SetViewProj()
{
	CreateViewMatrix(D3DXVECTOR3(0, 10.0f, -20.0f), D3DXVECTOR3(0, 0.0f, 0));
	float fAspect = (float)g_rtClient.right / (float)g_rtClient.bottom;
	CreateProjMatrix(1.0f, 1000.0f, D3DX_PI * 0.5f, fAspect);
	return true;
}
void JHCamera::CreateViewMatrix(D3DXVECTOR3 pos, D3DXVECTOR3 target, D3DXVECTOR3 up)
{
	m_vPos = pos;
	m_vAt = target;
	m_vDefaultUp = up;
	m_fRadius = D3DXVec3Length(&(m_vPos - m_vAt));
	D3DXVec3Normalize(&m_vBackPos, &(m_vPos - m_vAt));

	D3DXMatrixLookAtLH(&m_matView, &pos, &target, &up);
}
bool	 JHCamera::UpdateBasisVector()
{

	m_vSide.x = m_matView._11;
	m_vSide.y = m_matView._21;
	m_vSide.z = m_matView._31;

	m_vUp.x = m_matView._12;
	m_vUp.y = m_matView._22;
	m_vUp.z = m_matView._32;

	m_vLookup.x = m_matView._13;
	m_vLookup.y = m_matView._23;
	m_vLookup.z = m_matView._33;

	D3DXVec3Normalize(&m_vLookup, &m_vLookup);
	D3DXVec3Normalize(&m_vSide, &m_vSide);
	D3DXVec3Normalize(&m_vUp, &m_vUp);

	m_Frustum.SetMatrix(nullptr,&m_matView,&m_matProj);
	return true;
}

F_POSITION JHCamera::CheckOBBInPlane(BOUNDINGBOX& box)
{
	D3DXVECTOR3 vDir;
	
	float fDistance=0.0f;
	float fCenterDistance=0.0f;
	F_POSITION Pos = FRONT;


	for ( int iPlane = 0; iPlane < 6; iPlane++)
	{
		
		vDir = box.vAxis[0] * box.fExtent[0];
		fDistance = fabs(m_Frustum.m_Plane[iPlane].fA *
			vDir.x +
			m_Frustum.m_Plane[iPlane].fB *
			vDir.y +
			m_Frustum.m_Plane[iPlane].fC *
			vDir.z);

		vDir = box.vAxis[1] * box.fExtent[1];
		fDistance += fabs(m_Frustum.m_Plane[iPlane].fA *
			vDir.x +
			m_Frustum.m_Plane[iPlane].fB *
			vDir.y +
			m_Frustum.m_Plane[iPlane].fC *
			vDir.z);

		vDir = box.vAxis[2] * box.fExtent[2];
		fDistance += fabs(m_Frustum.m_Plane[iPlane].fA *
			vDir.x +
			m_Frustum.m_Plane[iPlane].fB *
			vDir.y +
			m_Frustum.m_Plane[iPlane].fC *
			vDir.z);

			fCenterDistance =
				m_Frustum.m_Plane[iPlane].fA *
				box.vCenter.x +
				m_Frustum.m_Plane[iPlane].fB *
				box.vCenter.y +
				m_Frustum.m_Plane[iPlane].fC *
				box.vCenter.z +
				m_Frustum.m_Plane[iPlane].fD;
		if (fCenterDistance<=fDistance)
		{
			Pos = SPANNING;
		}
		if (fCenterDistance<-fDistance)
		{
			Pos = BACK;
			return  Pos;
		}
	}
	return Pos;

}
void JHCamera::CreateProjMatrix(float fNear,
	float fFar,
	float fFovY,
	float fAspect)
{

	m_fNear = fNear;
	m_fFar = fFar;
	m_fFovY = fFovY;
	m_fAspect = fAspect;
	D3DXMatrixPerspectiveFovLH(&m_matProj, fFovY, fAspect, fNear, fFar);

	D3DXMatrixOrthoLH(&m_matOrthoProj,
		g_rtClient.right,
		g_rtClient.bottom,
		fNear, fFar);
	 
}
bool JHCamera::Frame()
{
	D3DXMatrixLookAtLH(&m_matView,
		&m_vPos,
		&m_vAt,
		&m_vDefaultUp);

	UpdateBasisVector();
	return true;
}
JHCamera::JHCamera()
{
	m_fYaw = 0;
	m_fPitch = 0;
	m_fRoll = 0;
	m_fRadius = 50;
	m_nMouseWhellDelta = 0;
	m_fMaxRadius = FLT_MAX;
	m_fMinRadius = 0.0f;
	D3DXMatrixIdentity(&m_matWorld);
	m_bDrag = false;
}


JHCamera::~JHCamera()
{
}

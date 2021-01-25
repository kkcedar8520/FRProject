#include "JH_DebugCamera.h"
#include"JH_Input.h"

void  JH_DebugCamera::UpdateCameraHeight(float Height)
{
	m_vPos.y = Height;
}
void JH_DebugCamera::Update(D3DXVECTOR4 value)
{
	//D3DXQUATERNION qRot;
	//D3DXMATRIX matRot;

	//D3DXQuaternionRotationYawPitchRoll(&qRot, value.x, value.y, value.z);
	//D3DXMatrixAffineTransformation(&matRot, 1.0f, NULL, &qRot, &m_vPos);
	//D3DXMatrixInverse(&m_matView, NULL, &matRot);

	D3DXQUATERNION qRot;
	D3DXMATRIX matRot;


	D3DXQuaternionRotationYawPitchRoll(&qRot, value.y, value.x, value.z);
	D3DXMatrixAffineTransformation(&matRot, 1.0f, NULL, &qRot, &m_vPos);
	D3DXMatrixInverse(&m_matView, NULL, &matRot);

}
//void JH_DebugCamera::MsgProc(HWND hWnd,
//	UINT msg,
//	WPARAM wParam, LPARAM lParam)
//{
//
//	if (msg == WM_LBUTTONDOWN)
//	{
//		int iMouseX = LOWORD(lParam);
//		int iMouseY = HIWORD(lParam);
//		m_LastPosition.x = iMouseX;
//		m_LastPosition.y = iMouseY;
//		m_bDrag = true;
//	}
//	if (msg==WM_LBUTTONUP)
//	{
//		m_bDrag = false;
//	}
//	if (msg==WM_MOUSEMOVE)
//	{
//		int iMouseX = LOWORD(lParam);
//		int iMouseY = HIWORD(lParam);
//		if (m_bDrag)
//		{
//			m_fYaw += (iMouseX - m_LastPosition.x)*g_SecondPerFrame*2;
//			m_fPitch += (iMouseY - m_LastPosition.y)*g_SecondPerFrame*2;
//
//			m_LastPosition.x = iMouseX;
//			m_LastPosition.y = iMouseY;
//		}
//
//
//	}
//	if (msg == WM_LBUTTONDOWN)
//	{
//		int iMouseX = LOWORD(lParam);
//		int iMouseY = HIWORD(lParam);
//		m_bDrag = true;
//		m_LastPosition.x = iMouseX;
//		m_LastPosition.y = iMouseY;
//	}
//	if (msg == WM_LBUTTONUP)
//	{
//		m_bDrag = false;
//	}
//	if (msg == WM_MOUSEMOVE)
//	{
//		int iMouseX = LOWORD(lParam);
//		int iMouseY = HIWORD(lParam);
//		if (m_bDrag)
//		{
//			m_fYaw += (iMouseX - m_LastPosition.x)*g_SecondPerFrame * 2;
//			m_fPitch += (iMouseY - m_LastPosition.y)*g_SecondPerFrame * 2;
//			m_LastPosition.x = iMouseX;
//			m_LastPosition.y = iMouseY;
//		}
//	}
//
//}
bool JH_DebugCamera::Frame()
{


	if (G_Input.KeyCheck('W'))
	{
		m_vPos += m_vLookup * g_SecondPerFrame*50;
	}
	
	if (G_Input.KeyCheck('S'))
	{
		m_vPos -= m_vLookup * g_SecondPerFrame * 50;
	}
	if (G_Input.KeyCheck('D'))
	{
		m_vPos += m_vSide * g_SecondPerFrame * 50;
	}

	if (G_Input.KeyCheck('A'))
	{
		m_vPos -= m_vSide * g_SecondPerFrame * 50;
	}
	Update(D3DXVECTOR4(m_fPitch, m_fYaw, m_fRoll, 0));


	UpdateBasisVector();
	
	

	return true;
}
JH_DebugCamera::JH_DebugCamera()
{
	m_bDrag = false;
	m_fYaw=0;
	m_fRoll=0;
	m_fPitch=0;
	
}


JH_DebugCamera::~JH_DebugCamera()
{

}

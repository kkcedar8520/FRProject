#include "JH_DebugCamera.h"
#include"JH_Input.h"

void  JH_DebugCamera::UpdateCameraHeight(float Height)
{
	m_vPos.y = Height;
}
void JH_DebugCamera::Update(D3DXVECTOR3 value)
{
	
	D3DXQUATERNION qRot;
	D3DXMATRIX matRot;
	D3DXQuaternionRotationYawPitchRoll(&qRot, value.y, value.x, value.z);	
	D3DXMatrixAffineTransformation(&matRot, 1.0f, NULL, &qRot, &m_vPos);
	D3DXMatrixInverse(&m_matView, NULL, &matRot);

}
void JH_DebugCamera::MsgProc(HWND hWnd,
	UINT msg,
	WPARAM wParam, LPARAM lParam)
{

	if (msg == WM_LBUTTONDOWN)
{
	int iMouseX = LOWORD(lParam);
	int iMouseY = HIWORD(lParam);
	m_bDrag = true;
	m_LastPos.x = iMouseX;
	m_LastPos.y = iMouseY;
}
if (msg == WM_LBUTTONUP)
{
	m_bDrag = false;
}
if (msg == WM_MOUSEMOVE)
{
	int iMouseX = LOWORD(lParam);
	int iMouseY = HIWORD(lParam);
	if (m_bDrag)
	{
		
		m_fYaw += RadianToDegree((iMouseX - m_LastPos.x)*g_SecondPerFrame * 0.2);
		m_fPitch += RadianToDegree((iMouseY - m_LastPos.y)*g_SecondPerFrame * 0.2);
		m_LastPos.x = iMouseX;
		m_LastPos.y = iMouseY;
	}
}

if (msg == WM_MOUSEWHEEL)
{
	SHORT sWHEEL = HIWORD(wParam);
	if (sWHEEL > 0)
	{
		m_vPos += m_vLookup * g_SecondPerFrame * 1500;
	}
	else
	{
		m_vPos -= m_vLookup * g_SecondPerFrame * 1500;
	}
}

}
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
	if (G_Input.KeyCheck(VK_RIGHT))
	{
		m_fYaw += g_SecondPerFrame * 2;
	}
	if (G_Input.KeyCheck(VK_LEFT))
	{
		m_fYaw -= g_SecondPerFrame *2;
	}
	if (G_Input.KeyCheck(VK_UP))
	{
		m_fPitch -= g_SecondPerFrame * 2;
	}
	if (G_Input.KeyCheck(VK_DOWN))
	{
		m_fPitch += g_SecondPerFrame * 2;
	}
	Update(D3DXVECTOR3(m_fPitch, m_fYaw, m_fRoll));


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

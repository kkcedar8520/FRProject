#include "JH_BackViewCamera.h"
#include"JH_Input.h"

void JH_BackViewCamera::Front(float Speed)
{
	m_vAt.z += Speed * g_SecondPerFrame;
}
void JH_BackViewCamera::Side(float Speed)
{
	m_vAt.x += Speed * g_SecondPerFrame;
}

bool JH_BackViewCamera::Frame()
{
	m_fRadius += m_nMouseWhellDelta * m_fRadius * 0.1f / 120.0f;
	m_fRadius = min(m_fMaxRadius, m_fRadius);
	m_fRadius = max(m_fMinRadius, m_fRadius);
	m_nMouseWhellDelta = 0;
	if (G_Input.KeyCheck('W'))
	{
		Front(10);
	}
	if (G_Input.KeyCheck('S'))
	{
		Front(-10);
	}
	if (G_Input.KeyCheck('A'))
	{
		Side(-10);
	}
	if (G_Input.KeyCheck('D'))
	{
		Side(10);
	}

	m_vPos = m_vAt+m_vBackPos * m_fRadius;

	D3DXMatrixLookAtLH(&m_matView, &m_vPos, &m_vAt, &m_vDefaultUp);
	
	UpdateBasisVector();
	return true;
}
JH_BackViewCamera::JH_BackViewCamera()
{
}


JH_BackViewCamera::~JH_BackViewCamera()
{
}

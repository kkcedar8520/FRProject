#include "HArcBall.h"



// 화면좌표계를 구좌표계로 변환
D3DXVECTOR3 HArcBall::ScreenToVector(
	float nX, float nY)
{
	float x = -(nX - (g_rtClient.right/2)) / (g_rtClient.right / 2);
	float y = (nY - (g_rtClient.bottom / 2)) / (g_rtClient.bottom / 2);
	float z = 0.0f;

	float mag = x * x + y*y;
	if (mag > 1.0f)
	{
		float scale = 1.0f / sqrtf(mag);
		x *= scale;
		y *= scale;
	}
	else
	{
		z = sqrtf(1.0f - mag);
	}
	return D3DXVECTOR3(x, y, z);
}
D3DXQUATERNION HArcBall::QuatFromBallPoints(
	const D3DXVECTOR3& vFrom,
	const D3DXVECTOR3& vTo)
{
	float fDot = D3DXVec3Dot(&vFrom, &vTo);
	D3DXVECTOR3 vAxis;
	D3DXVec3Cross(&vAxis, &vFrom, &vTo);
	return D3DXQUATERNION(vAxis.x, vAxis.y, vAxis.z,fDot);

}
void  HArcBall::OnBegin(int nX, int nY)
{
	m_bDrag = true;
	m_qDown = m_qNow;
	// 2D -> 3D
	m_vDownPt = ScreenToVector(nX, nY);
}
void  HArcBall::OnMove(int nX, int nY)
{
	if (m_bDrag)
	{
		m_vCurrentPt = ScreenToVector(nX, nY);
		m_qNow = m_qDown * 
			QuatFromBallPoints(m_vDownPt, m_vCurrentPt);
	}
}
void  HArcBall::OnEnd()
{
	m_bDrag = false;
}

HArcBall::HArcBall()
{
	m_bDrag = false;
	D3DXQuaternionIdentity(&m_qDown);
	D3DXQuaternionIdentity(&m_qNow);
}


HArcBall::~HArcBall()
{
}


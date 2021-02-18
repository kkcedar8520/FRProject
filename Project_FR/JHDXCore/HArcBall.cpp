#include "HArcBall.h"



// 화면좌표계를 구좌표계로 변환
D3DXVECTOR3 HArcBall::ScreenToVector(
	float nX, float nY)
{
	float x = (nX - (g_rtClient.right/2)) / (g_rtClient.right / 2);
	float y = -(nY - (g_rtClient.bottom / 2)) / (g_rtClient.bottom / 2);
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

// 전에 찍은점과 현재찍은점의 사이의 각도만큼 법선벡터를 축으로하여 회전
D3DXQUATERNION HArcBall::QuatFromBallPoints(
	const D3DXVECTOR3& vFrom,
	const D3DXVECTOR3& vTo)
{
	float fDot = D3DXVec3Dot(&vFrom, &vTo); //크기가둘다 1이므로 코사인각
	float Radian = acos(fDot);
	float Angle = Radian * (180.0f / D3DX_PI);
	D3DXVECTOR3 vAxis;

	D3DXVec3Cross(&vAxis, &vFrom, &vTo);
	D3DXMatrixRotationAxis(&m_matRotation,&vAxis,Angle);
	return D3DXQUATERNION(vAxis.x, vAxis.y, vAxis.z, fDot);

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


#include "JH_Frustum.h"

void JH_Frustum::SetMatrix(D3DXMATRIX* matWorld, D3DXMATRIX* matView, D3DXMATRIX* matProj)
{

	D3DXMATRIX MatFrustum = *matView * *matProj;

	D3DXMATRIX InverseFrustum;
	D3DXMatrixInverse(&InverseFrustum,NULL,&MatFrustum);
	//앞
	m_vFrustum[0] = D3DXVECTOR3(-1, 1, 0); 
	m_vFrustum[1] = D3DXVECTOR3(1, 1, 0);
	m_vFrustum[2] = D3DXVECTOR3(-1, -1, 0);
	m_vFrustum[3] = D3DXVECTOR3(1, -1, 0);
	//뒤

	m_vFrustum[4] = D3DXVECTOR3(-1, 1, 1);
	m_vFrustum[5] = D3DXVECTOR3(1, 1, 1);
	m_vFrustum[6] = D3DXVECTOR3(-1, -1, 1);
	m_vFrustum[7] = D3DXVECTOR3(1, -1, 1);

	for (int i = 0; i < 8; i++)
	{
		//NDC(동차공간)에서 세계공간으로 만들어줌 
		D3DXVec3TransformCoord(&m_vFrustum[i],
			&m_vFrustum[i], &InverseFrustum);
	}
	////  4    5 
	////  6    7

	////   0   1
	////   2   3

	m_Plane[0].CreatePlane(m_vFrustum[4], m_vFrustum[0], m_vFrustum[2]);//좌
	m_Plane[1].CreatePlane(m_vFrustum[5], m_vFrustum[3], m_vFrustum[1]);//우

	m_Plane[2].CreatePlane(m_vFrustum[1], m_vFrustum[2], m_vFrustum[0]);//앞
	m_Plane[3].CreatePlane(m_vFrustum[4], m_vFrustum[6], m_vFrustum[5]);//뒤

	m_Plane[4].CreatePlane(m_vFrustum[4],m_vFrustum[5], m_vFrustum[0]);//위
	m_Plane[5].CreatePlane(m_vFrustum[6], m_vFrustum[2], m_vFrustum[7]);//아래





}
JH_Frustum::JH_Frustum()
{
}


JH_Frustum::~JH_Frustum()
{
}

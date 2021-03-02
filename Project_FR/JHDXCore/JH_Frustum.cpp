#include "JH_Frustum.h"

void JH_Frustum::SetMatrix(D3DXMATRIX* matWorld, D3DXMATRIX* matView, D3DXMATRIX* matProj)
{

	D3DXMATRIX MatFrustum;
	D3DXMatrixMultiply(&MatFrustum,matView, matProj);
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

	ExtractPlanesD3D(m_Plane, MatFrustum);
	//m_Plane[0].CreatePlane(m_vFrustum[4], m_vFrustum[2], m_vFrustum[0]);//좌
	//m_Plane[1].CreatePlane(m_vFrustum[5], m_vFrustum[1], m_vFrustum[3]);//우

	//m_Plane[2].CreatePlane(m_vFrustum[4], m_vFrustum[0], m_vFrustum[5]);//위
	//m_Plane[3].CreatePlane(m_vFrustum[6], m_vFrustum[7], m_vFrustum[2]);//아래

	//m_Plane[5].CreatePlane(m_vFrustum[1], m_vFrustum[0], m_vFrustum[2]);//앞
	//m_Plane[4].CreatePlane(m_vFrustum[4], m_vFrustum[5], m_vFrustum[6]);//뒤







}
void JH_Frustum::ExtractPlanesD3D(JH_PLANE* pPlanes, const D3DXMATRIX & comboMatrix)
{
	if (pPlanes == NULL) return;
	// Left clipping plane
	pPlanes[0].fA = comboMatrix._14 + comboMatrix._11;
	pPlanes[0].fB = comboMatrix._24 + comboMatrix._21;
	pPlanes[0].fC = comboMatrix._34 + comboMatrix._31;
	pPlanes[0].fD = comboMatrix._44 + comboMatrix._41;
	// Right clipping plane
	pPlanes[1].fA = comboMatrix._14 - comboMatrix._11;
	pPlanes[1].fB = comboMatrix._24 - comboMatrix._21;
	pPlanes[1].fC = comboMatrix._34 - comboMatrix._31;
	pPlanes[1].fD = comboMatrix._44 - comboMatrix._41;
	// Top clipping plane
	pPlanes[2].fA = comboMatrix._14 - comboMatrix._12;
	pPlanes[2].fB = comboMatrix._24 - comboMatrix._22;
	pPlanes[2].fC = comboMatrix._34 - comboMatrix._32;
	pPlanes[2].fD = comboMatrix._44 - comboMatrix._42;
	// Bottom clipping plane
	pPlanes[3].fA = comboMatrix._14 + comboMatrix._12;
	pPlanes[3].fB = comboMatrix._24 + comboMatrix._22;
	pPlanes[3].fC = comboMatrix._34 + comboMatrix._32;
	pPlanes[3].fD = comboMatrix._44 + comboMatrix._42;
	// Near clipping plane
	pPlanes[4].fA = comboMatrix._13;
	pPlanes[4].fB = comboMatrix._23;
	pPlanes[4].fC = comboMatrix._33;
	pPlanes[4].fD = comboMatrix._43;
	// Far clipping plane
	pPlanes[5].fA = comboMatrix._14 - comboMatrix._13;
	pPlanes[5].fB = comboMatrix._24 - comboMatrix._23;
	pPlanes[5].fC = comboMatrix._34 - comboMatrix._33;
	pPlanes[5].fD = comboMatrix._44 - comboMatrix._43;

	pPlanes[0].Normalize();
	pPlanes[1].Normalize();
	pPlanes[2].Normalize();
	pPlanes[3].Normalize();
	pPlanes[4].Normalize();
	pPlanes[5].Normalize();
}
JH_Frustum::JH_Frustum()
{
}


JH_Frustum::~JH_Frustum()
{
}

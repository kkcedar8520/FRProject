#include "JH_Select.h"

void JH_Select::SetMatrix(D3DXMATRIX* pWorld,
	D3DXMATRIX* pView,
	D3DXMATRIX* pProj)
{
	if (pWorld != NULL)
	{
		m_matWorld = *pWorld;
	}
	if (pView != NULL)
	{
		m_matView = *pView;
	}
	if (pProj != NULL)
	{
		m_matProj = *pProj;
	}
	Update();
}
void JH_Select::Update()
{
	POINT Cursor;

	GetCursorPos(&Cursor);//win api
	ScreenToClient(g_hwnd, &Cursor); 

	D3DXVECTOR3 v;
	v.x = (((2.0f* Cursor.x) / (g_rtClient.right)) - 1) / m_matProj._11;
	v.y = -(((2.0f* Cursor.y) / (g_rtClient.bottom)) - 1) / m_matProj._22;
	v.z = 1.0f;
	
	m_Ray.vOrigin = D3DXVECTOR3(0, 0, 0);
	m_Ray.vDirection = v;
	m_Ray.vPoint = v;
	D3DXMATRIX matVW = m_matWorld * m_matView;
	D3DXMATRIX matViewInverse;

	D3DXMatrixInverse(&matViewInverse, NULL, &matVW);

	D3DXVec3TransformCoord(&m_Ray.vOrigin, &m_Ray.vOrigin,&matViewInverse);
	D3DXVec3TransformNormal(&m_Ray.vDirection, &m_Ray.vDirection, &matViewInverse);
	D3DXVec3Normalize(&m_Ray.vDirection, &m_Ray.vDirection);


}
bool JH_Select::AABBtoRay(BOUNDINGBOX* pBox,H_RAY* pRay)
{

	if (pRay == nullptr) pRay = &m_Ray;
	D3DXVECTOR3 tmin;
	tmin.x = (pBox->vMin.x - pRay->vOrigin.x) / pRay->vDirection.x + 0.001f;
	tmin.y = (pBox->vMin.y - pRay->vOrigin.y) / pRay->vDirection.y + 0.001f;
	tmin.z = (pBox->vMin.z - pRay->vOrigin.z) / pRay->vDirection.z + 0.001f;

	D3DXVECTOR3 tmax;
	tmax.x = (pBox->vMax.x - pRay->vOrigin.x) / pRay->vDirection.x + 0.001f;
	tmax.y = (pBox->vMax.y - pRay->vOrigin.y) / pRay->vDirection.y + 0.001f;
	tmax.z = (pBox->vMax.z - pRay->vOrigin.z) / pRay->vDirection.z + 0.001f;

	D3DXVECTOR3 real_min;
	real_min.x = min(tmin.x, tmax.x);
	real_min.y = min(tmin.y, tmax.y);
	real_min.z = min(tmin.z, tmax.z);
	D3DXVECTOR3 real_max;
	real_max.x = max(tmin.x, tmax.x);
	real_max.y = max(tmin.y, tmax.y);
	real_max.z = max(tmin.z, tmax.z);

	float minmax = min(min(real_max.x, real_max.y), real_max.z);
	float maxmin = max(max(real_min.x, real_min.y), real_min.z);

	if (minmax >= maxmin)
	{
		m_vIntersection = pRay->vOrigin + pRay->vDirection* maxmin;

		return true;
	}
	return false;

}
bool JH_Select::GetIntersection(
	D3DXVECTOR3 vStart,
	D3DXVECTOR3 vEnd,
	D3DXVECTOR3 vNormal,
	D3DXVECTOR3 v0,
	D3DXVECTOR3 v1,
	D3DXVECTOR3 v2)
{
	D3DXVECTOR3 vDir = vEnd - vStart;
	float d1 = D3DXVec3Dot(&vNormal, &vDir);
	float d2 = D3DXVec3Dot(&vNormal, &(v0 - vStart));
	float t = d2 / d1;
	if (t < 0.0f || t > 1.0f)
	{
		return false;
	}
	m_vIntersection = vStart + vDir * t;
	return true;
}
bool JH_Select::PointInPolygon(
	D3DXVECTOR3 vert,
	D3DXVECTOR3 vFaceNormal,
	D3DXVECTOR3 v0,
	D3DXVECTOR3 v1,
	D3DXVECTOR3 v2)
{
	//     v1

	//     i
	// v0     v2

	D3DXVECTOR3 e0, e1, vNormal;
	e0 = v1 - v0;
	e1 = vert - v0;
	D3DXVec3Cross(&vNormal, &e0, &e1);
	D3DXVec3Normalize(&vNormal, &vNormal);
	float fDot = D3DXVec3Dot(&vFaceNormal, &vNormal);
	if (fDot < 0.0f) return false;

	e0 = v2 - v1;
	e1 = vert - v1;
	D3DXVec3Cross(&vNormal, &e0, &e1);
	D3DXVec3Normalize(&vNormal, &vNormal);
	fDot = D3DXVec3Dot(&vFaceNormal, &vNormal);
	if (fDot < 0.0f) return false;

	e0 = v0 - v2;
	e1 = vert - v2;
	D3DXVec3Cross(&vNormal, &e0, &e1);
	D3DXVec3Normalize(&vNormal, &vNormal);
	fDot = D3DXVec3Dot(&vFaceNormal, &vNormal);
	if (fDot < 0.0f) return false;

	return true;
}
bool JH_Select::InterSectionTriAngle(D3DXVECTOR3 v0,
	D3DXVECTOR3 v1, 
	D3DXVECTOR3 v2)
{
	D3DXVECTOR3 e0, e1, T,tVec,uVec;
	float u, v;

	T = m_Ray.vDirection - v0;

	e0 = v1 - v0;
	e1 = v2 - v0;


	float fdet = 0.0f;
	
	D3DXVec3Cross(&tVec, &m_Ray.vDirection, &e1);
	fdet=D3DXVec3Dot(&e0,&tVec);

	float fInverseDet = 1.0f/ fdet;
	
	u = D3DXVec3Dot(&T, &tVec);
	if (u <= 0.0f || u > fdet) return false;

	u *= fInverseDet;

	D3DXVec3Cross(&uVec, &m_Ray.vDirection, &T);

	v = D3DXVec3Dot(&e1, &uVec);

	if (v <= 0.0f || u > fdet) return false;

	v *= fInverseDet;

	if (u + v <= 0 || u + v > 1)return false;


	m_vIntersection = u * (e0)+v * (e1);


	return true;

	
	

}

JH_Select::JH_Select()
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matView);
	D3DXMatrixIdentity(&m_matProj);
}


JH_Select::~JH_Select()
{
}
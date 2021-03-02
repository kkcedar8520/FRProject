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
	//스크린좌표를 투영좌표로 변환
	v.x = (((2.0f* Cursor.x) / (g_rtClient.right)) - 1) / m_matProj._11;
	v.y = -(((2.0f* Cursor.y) / (g_rtClient.bottom)) - 1) / m_matProj._22;
	v.z = 1.0f;
	
	m_Ray.vOrigin = D3DXVECTOR3(0, 0, 0);
	m_Ray.vDirection = v;
	m_Ray.vPoint = v;
	D3DXMATRIX matVW = m_matWorld * m_matView;
	D3DXMATRIX matViewInverse;

	D3DXMatrixInverse(&matViewInverse, NULL, &matVW);

	//반직선을 월드좌표로 
	D3DXVec3TransformCoord(&m_Ray.vOrigin, &m_Ray.vOrigin,&matViewInverse);
	D3DXVec3TransformNormal(&m_Ray.vDirection, &m_Ray.vDirection, &matViewInverse);
	D3DXVec3Normalize(&m_Ray.vDirection, &m_Ray.vDirection);


}

bool JH_Select::AABBtoRay(BOUNDINGBOX* pBox,JH_RAY* pRay)
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
bool JH_Select::OBBToRay(JH_Box* pBox)
{
	float t_min = -999999.0f;
	float t_max = 999999.0f;
	float  f[3], fa[3], s[3], sa[3];

	D3DXVECTOR3 vR = m_Ray.vOrigin - pBox->vCenter;

	//X,Y,Z OBB의 축에대한 검사
	for (int v = 0; v < 3; v++)
	{
		f[v] = D3DXVec3Dot(&pBox->vAxis[v], &m_Ray.vDirection);
		s[v] = D3DXVec3Dot(&pBox->vAxis[v], &vR);
		fa[v] = fabs(f[v]);
		sa[v] = fabs(s[v]);

		//OBB투영축 안에 시작점이있는지 판별하고 반직선의 방향성을 판별
		//둘다 불충족시 반직선은 지나지않음
		if (sa[v] > pBox->fExtent[v] && s[v] * f[v] >= 0.0f)
			return false;

		float t1 = (-s[v] - pBox->fExtent[v]) / f[v];
		float t2 = (-s[v] + pBox->fExtent[v]) / f[v];
		if (t1 > t2)
		{
			std::swap(t1, t2);
		}
		t_min = max(t_min, t1);
		t_max = min(t_max, t2);
		if (t_min > t_max)
			return false;
	}

	float  fCross[3], fRhs;
	D3DXVECTOR3 vDxR;
	D3DXVec3Cross(&vDxR, &m_Ray.vDirection, &vR);
	// D X pBox->vAxis[0]  분리축
	fCross[0] = fabs(D3DXVec3Dot(&vDxR, &pBox->vAxis[0]));
	float fAxis2 = pBox->fExtent[1] * fa[2];
	float fAxis1 = pBox->fExtent[2] * fa[1];
	fRhs = fAxis2 + fAxis1;
	if (fCross[0] > fRhs)
	{
		return false;
	}
	// D x pBox->vAxis[1]  분리축 R=O-C 투영축 투영
	fCross[1] = fabs(D3DXVec3Dot(&vDxR, &pBox->vAxis[1]));
	//OBB 투영
	fRhs = pBox->fExtent[0] * fa[2] + pBox->fExtent[2] * fa[0];
	if (fCross[1] > fRhs)
	{
		return false;
	}
	// D x pBox->vAxis[2]  분리축
	fCross[2] = fabs(D3DXVec3Dot(&vDxR, &pBox->vAxis[2]));
	fRhs = pBox->fExtent[0] * fa[1] + pBox->fExtent[1] * fa[0];
	if (fCross[2] > fRhs)
	{
		return false;
	}

	m_vIntersection = m_Ray.vOrigin + m_Ray.vDirection* t_min;
	return true;
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
bool JH_Select::PickCheck(D3DXVECTOR3 v0, D3DXVECTOR3 v1, D3DXVECTOR3 v2)
{
	float t, u, v;

	D3DXVECTOR3 vT = m_Ray.vOrigin - v0;
	D3DXVECTOR3 vE0 = v1 - v0;
	D3DXVECTOR3 vE1 = v2 - v0;

	D3DXVECTOR3 vP, vQ;
	D3DXVec3Cross(&vP, &m_Ray.vDirection, &vE1);
	D3DXVec3Cross(&vQ, &vT, &vE0);

	float dot = D3DXVec3Dot(&vP, &vE0);

	t = D3DXVec3Dot(&vQ, &vE1) / dot;
	u = D3DXVec3Dot(&vP, &vT) / dot;
	v = D3DXVec3Dot(&vQ, &m_Ray.vDirection) / dot;

	if (u<0 || u>1.0f || v<0 || v>1.0f || (u + v) > 1.0f)
	{
		return false;
	}


	m_vIntersection = m_Ray.vOrigin + m_Ray.vDirection*t;
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
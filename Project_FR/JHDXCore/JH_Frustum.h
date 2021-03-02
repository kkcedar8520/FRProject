#pragma once
#include"JH_ShapePlane.h"


class JH_Frustum
{
public:
	JH_PLANE	m_Plane[6];
	D3DXVECTOR3 m_vFrustum[8];
public:
	void SetMatrix(D3DXMATRIX* matWorld, D3DXMATRIX* matView, D3DXMATRIX* matProj);
	void ExtractPlanesD3D(JH_PLANE* pPlanes, const D3DXMATRIX & comboMatrix);
public:
	JH_Frustum();
	virtual ~JH_Frustum();
};


#pragma once
#include"JH_ShapePlane.h"


class JH_Frustum
{
public:
	FT_PLANE	m_Plane[6];
	D3DXVECTOR3 m_vFrustum[8];
public:
	void SetMatrix(D3DXMATRIX* matWorld, D3DXMATRIX* matView, D3DXMATRIX* matProj);

public:
	JH_Frustum();
	virtual ~JH_Frustum();
};


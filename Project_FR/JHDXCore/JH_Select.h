#pragma once
#include"JH_DXStd.h"


class JH_Select
{
public:
	H_RAY	m_Ray;
	D3DXVECTOR3 m_vIntersection;

public:
	D3DXMATRIX m_matWorld;
	D3DXMATRIX m_matView;
	D3DXMATRIX m_matProj;
public:
	static JH_Select& GetInstance()
	{
		static JH_Select Sel;

		return Sel;
	}
public:
	void SetMatrix(D3DXMATRIX* pWorld,
		D3DXMATRIX* pView,
		D3DXMATRIX* pProj);
	void Update();
	bool AABBtoRay(BOUNDINGBOX* pBox, H_RAY* Ray=nullptr);
	bool GetIntersection(
		D3DXVECTOR3 vStart,
		D3DXVECTOR3 vEnd,
		D3DXVECTOR3 vNormal,
		D3DXVECTOR3 v0,
		D3DXVECTOR3 v1,
		D3DXVECTOR3 v2);
	bool PointInPolygon(
		D3DXVECTOR3 vert,
		D3DXVECTOR3 vFaceNormal,
		D3DXVECTOR3 v0,
		D3DXVECTOR3 v1,
		D3DXVECTOR3 v2);
	bool InterSectionTriAngle(D3DXVECTOR3 v0,D3DXVECTOR3 v1,D3DXVECTOR3 v2);
public:
	~JH_Select();
	JH_Select();

private:


};

#define I_Select JH_Select::GetInstance()

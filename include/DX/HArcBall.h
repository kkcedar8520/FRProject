#pragma once

#include "JH_DxStd.h"
class HArcBall
{
public:
	bool			m_bDrag;
	D3DXQUATERNION	m_qDown;
	D3DXQUATERNION	m_qNow;

	D3DXVECTOR3		m_vDownPt;
	D3DXVECTOR3		m_vCurrentPt;

	D3DXMATRIX      m_matRotation;

public:
	void  OnBegin(int nX, int nY);
	void  OnMove(int nX, int nY);
	void  OnEnd();
	D3DXVECTOR3 ScreenToVector(float nX, float nY);
	D3DXQUATERNION QuatFromBallPoints(
		const D3DXVECTOR3& vFrom,
		const D3DXVECTOR3& vTo);
	D3DXMATRIX* GetRotationMatrix()
	{
		return D3DXMatrixRotationQuaternion(&m_matRotation, &m_qNow);
	}
public:
	HArcBall();
	virtual ~HArcBall();
};


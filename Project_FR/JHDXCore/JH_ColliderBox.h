#pragma once
#include"JH_DXStd.h"
#include"JH_ShapeBox.h"
class JH_ColliderBox:public JH_ShapeBox
{
public:
	void	SetWorld(D3DXMATRIX& Mat);
	void	SetTransform(D3DXMATRIX& Mat)override;
	void	SetPos(D3DXVECTOR3 vPos)override;
	void	SetScale(D3DXVECTOR3 vScale)override;
	void	SetRotation(D3DXMATRIX Mat)override;
public:
	bool	Frame()override;
	HRESULT CreateVertexData()override;
	void UpdateBox();
	void UpdateVB();
};


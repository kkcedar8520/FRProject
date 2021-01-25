#pragma once
#include"JH_Select.h"
class JH_BaseObj
{
	BOUNDINGBOX m_Box;
	SPHERE		m_Sphere;
public:
	D3DXMATRIX m_matWorld;
public:
	JH_BaseObj();
	virtual ~JH_BaseObj();
};


#pragma once
#include"JH_DXStd.h"
#include"JH_Model.h"
class JH_ShapeBox:public JH_Model
{
public:
	vector<PNCT_VERTEX>		m_VertexData;
public:
	HRESULT CreateVertexData();
	HRESULT CreateIndexData();
public:
	JH_ShapeBox();
	virtual ~JH_ShapeBox();
};


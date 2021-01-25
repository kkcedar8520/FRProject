#pragma once
#include"JH_DXStd.h"
#include"JH_Model.h"
class JHShapeBox:public JH_Model
{
public:
	HRESULT CreateVertexData();
	HRESULT CreateIndexData();
public:
	JHShapeBox();
	virtual ~JHShapeBox();
};


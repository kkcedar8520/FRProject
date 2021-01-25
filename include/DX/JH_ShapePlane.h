#pragma once
#include"JH_Model.h"
class JH_ShapePlane:public JH_Model
{
public:
	HRESULT CreateVertexData();
	HRESULT CreateIndexData();
public:
	JH_ShapePlane();
	virtual ~JH_ShapePlane();
};


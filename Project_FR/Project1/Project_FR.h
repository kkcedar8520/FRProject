#pragma once
#include"JHDXCore.h"
#include"ModelLoader.h"
#include"JH_Obj.h"
#include"JH_ShapePlane.h"

class Project_FR:public JHDXCore
{
public:
	ModelLoader			m_ModleLoader;
	JH_Obj				 TestObj;
	JH_ShapePlane	   test;
	
public:
	bool Init() override;
	bool Frame()override;
	bool Render()override;
	bool Release()override;
	Project_FR();
	virtual ~Project_FR();
};


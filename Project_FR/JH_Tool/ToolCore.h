#pragma once
#include"JHDXCore.h"
#include"JH_MapMgr.h"
#include"JH_Input.h"
enum class TOOLSTATE
{
	BASE=0,
	HEIGHT=1,
};
class ToolCore:public JHDXCore
{
public:
	JH_Map*		 m_Map;
	JH_ShapeLine m_DebugLine;
public:
	// Flag
	TOOLSTATE	m_eState= TOOLSTATE::BASE;
	SPHERE		m_Sphere;
public:
	bool MapUpDown();
public:
	virtual bool Init()override;
	virtual bool Frame()override;
	virtual bool Render()override;
	virtual bool Release()override;
};


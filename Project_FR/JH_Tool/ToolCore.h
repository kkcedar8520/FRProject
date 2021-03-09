#pragma once
#include"JHDXCore.h"
#include"JH_MapMgr.h"
#include"JH_Input.h"
#include"ComputeShader.h"
#include"JH_ObjMgr.h"
struct CSBUFF
{
	D3DXVECTOR3 vPickPos;
	float		fRadius;
	float		Alpha[4];
	int			iIndex;
	int			iCol;
	int			iRow;

};
enum class TOOLSTATE
{
	BASE=0,
	HEIGHT,
	SPLATTING,
	FLATTING,
	OBJECTNEW,
	OBJECTEDIT,
	COLLIDERBOX,

};
class ToolCore:public JHDXCore
{
public:
	JH_ShapeLine	m_DebugLine;
	ComputeShader   m_CS;
	CSBUFF			m_CSBuf;
public:
	// Flag
	TOOLSTATE	m_eState= TOOLSTATE::BASE;
	
	SPHERE		m_Sphere;

	//
	std::string	m_ObjFileName;
public:
	bool MapUpDown();
	bool MapSplatting();
	void MapFlatting();
	void ObjectCollocate();
	JH_Node* ClikNode();
public:

public:
	virtual bool Init()override;
	virtual bool Frame()override;
	virtual bool Render()override;
	virtual bool Release()override;
};


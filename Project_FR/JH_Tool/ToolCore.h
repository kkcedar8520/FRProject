#pragma once
#include"JHDXCore.h"
#include"JH_MapMgr.h"
#include"JH_Input.h"
#include"ComputeShader.h"
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
public:
	bool MapUpDown();
	bool MapSplatting();
	void MapFlatting();
	JH_Node* ClikNode();
public:

public:
	virtual bool Init()override;
	virtual bool Frame()override;
	virtual bool Render()override;
	virtual bool Release()override;
};


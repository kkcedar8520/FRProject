#pragma once
#include"JHDXCore.h"
#include"JH_MapMgr.h"
class ToolCore:public JHDXCore
{
public:
	JH_Map*		 m_Map;
	JH_ShapeLine m_DebugLine;
public:

public:
	bool CreateMap(int iWidth,
		int iHeight,
		int iCellCount,
		int iCellSize,
		const TCHAR* pTexturFileName,
		const TCHAR* pNormalMapFileName = nullptr,
		const TCHAR* pHeightMapFileName = nullptr,
		const TCHAR* pLightShaderName = nullptr);
public:
	virtual bool Init()override;
	virtual bool Frame()override;
	virtual bool Render()override;
	virtual bool Release()override;
};


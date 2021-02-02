#pragma once
#include "JH_DXStd.h"

class Texture
{
public:
	T_STR		m_szName;
	T_STR		m_szPath;
	//--------------------------------------------------------------------------------------
	// 텍스쳐 로딩 및 리소스버퍼 생성
	//--------------------------------------------------------------------------------------
	ID3D11ShaderResourceView*	m_pTextureRV;
	ID3D11SamplerState*			m_pSamplerState;
	D3D11_SAMPLER_DESC			m_SampleDesc;
public:
	HRESULT						Load(ID3D11Device* pDevice, const TCHAR* strFilePath);
	bool						Apply(ID3D11DeviceContext*    pImmediateContext);
	bool						Release();
	void						SetPath(const TCHAR* pPath);

public:
	Texture(void);
	virtual ~Texture(void);
};

class TextureMgr : public Singleton < TextureMgr >
{
private:
	friend class Singleton<TextureMgr>;
	ID3D11Device*			m_pd3dDevice;
	ID3D11DeviceContext*    m_pImmediateContext;
public:
	typedef unordered_map <INT, Texture*>		TemplateMap;
	typedef TemplateMap::iterator				TemplateMapItor;
	TemplateMapItor								TItor;
	TemplateMap									TMap;
	INT											m_iCurIndex;
public:
	INT				Add(ID3D11Device*	 pDevice, const TCHAR *pFileName);
	INT				Add(ID3D11Device*	 pDevice, const TCHAR *pFileName, const TCHAR* szPath);

	Texture* const	GetPtr(INT iIndex);
	Texture* const	GetPtr(T_STR strFindName);

	const TCHAR*			SplitPath(const TCHAR* FileName);
	bool			Release();
public:
	TextureMgr();
	virtual ~TextureMgr();
};
#define I_Texture TextureMgr::GetInstance()


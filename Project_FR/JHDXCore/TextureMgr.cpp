#include "TextureMgr.h"

HRESULT		Texture::Load(ID3D11Device* pDevice,
	const TCHAR* strFilePath)
{
	if (strFilePath == NULL) return S_OK;
	HRESULT hr = S_OK;
	TCHAR szFileName[MAX_PATH] = { 0, };
	_stprintf_s(szFileName, _T("%s%s"), m_szPath.c_str(), strFilePath);
	m_szName = strFilePath;

	D3DX11_IMAGE_LOAD_INFO loadInfo;
	ZeroMemory(&loadInfo, sizeof(D3DX11_IMAGE_LOAD_INFO));
	loadInfo.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	loadInfo.Format = DXGI_FORMAT_FROM_FILE;//DXGI_FORMAT_BC1_UNORM;

											// Load the Texture
	hr = D3DX11CreateShaderResourceViewFromFile(pDevice, szFileName, &loadInfo, NULL, &m_pTextureRV, NULL);
	if (FAILED(hr))
	{
		//ErrorQuit(szFileName);
		return hr;
	}
	return hr;
}
bool Texture::Apply(ID3D11DeviceContext*    pImmediateContext)
{
	assert(pImmediateContext);
	if (!m_pTextureRV)
	{
		return false;
	}
	pImmediateContext->PSSetShaderResources(0, 1, &m_pTextureRV);
	//pImmediateContext->PSSetSamplers(0, 1, &m_pSamplerState);
	return true;
}

bool Texture::Release()
{
	SAFE_RELEASE(m_pTextureRV);
	SAFE_RELEASE(m_pSamplerState);
	return true;
}
Texture::Texture(void)
{
	SAFE_ZERO(m_pTextureRV);
	SAFE_ZERO(m_pSamplerState);
	m_szPath = _T("");
}

Texture::~Texture(void)
{
}
void Texture::SetPath(const TCHAR* pPath)
{
	m_szPath = pPath;
}

INT TextureMgr::Add(ID3D11Device*	 pDevice, const TCHAR *pFileName)
{
	TCHAR szFileName[MAX_PATH];
	TCHAR Drive[MAX_PATH];
	TCHAR Dir[MAX_PATH];
	TCHAR FName[MAX_PATH];
	TCHAR Ext[MAX_PATH];
	if (pFileName)
	{
		_tsplitpath(pFileName, Drive, Dir, FName, Ext);
		Ext[4] = 0;
		memset(szFileName, 0, sizeof(TCHAR) * MAX_PATH);
		//D3DX11_IMAGE_FILE_FORMAT 

		if (_tcsicmp(Ext, _T(".tga")) == 0)
		{
			_tcscpy(Ext, _T(".bmp"));
		}
		_stprintf_s(szFileName, _T("%s%s"), FName, Ext);

		for (TemplateMapItor itor = TMap.begin(); itor != TMap.end(); itor++)
		{
		Texture *pPoint = (Texture *)(*itor).second;
			if (!_tcsicmp(pPoint->m_szName.c_str(), szFileName))
			{
				return (*itor).first;
			}
		}
	}
	Texture *pPoint = NULL;
	SAFE_NEW(pPoint, Texture);

	TCHAR szPath[MAX_PATH] = { 0, };
	_stprintf_s(szPath, _T("%s%s"), Drive, Dir);
	pPoint->SetPath(szPath);

	if (FAILED(pPoint->Load(pDevice, szFileName)))
	{
		return 0;
	}
	TMap.insert(make_pair(++m_iCurIndex, pPoint));
	return m_iCurIndex;
}


INT TextureMgr::Add(ID3D11Device*	 pDevice, const TCHAR *pFileName, const TCHAR* szPath)
{
	TCHAR szFileName[MAX_PATH];
	TCHAR Drive[MAX_PATH];
	TCHAR Dir[MAX_PATH];
	TCHAR FName[MAX_PATH];
	TCHAR Ext[MAX_PATH];
	if (pFileName)
	{
		_tsplitpath(pFileName, Drive, Dir, FName, Ext);
		Ext[4] = 0;
		memset(szFileName, 0, sizeof(TCHAR) * MAX_PATH);
		if (_tcsicmp(Ext, _T(".tga")) == 0)
		{
			_tcscpy(Ext, _T(".dds"));
		}
		_stprintf_s(szFileName, _T("%s%s"), FName, Ext);

		for (TemplateMapItor itor = TMap.begin(); itor != TMap.end(); itor++)
		{
			Texture *pPoint = (Texture *)(*itor).second;
			if (!_tcsicmp(pPoint->m_szName.c_str(), szFileName))
			{
				return (*itor).first;
			}
		}
	}
	Texture *pPoint = nullptr;
	SAFE_NEW(pPoint, Texture);
	pPoint->SetPath(szPath);

	if (FAILED(pPoint->Load(pDevice, szFileName)))
	{
		return 0;
	}
	TMap.insert(make_pair(++m_iCurIndex, pPoint));
	return m_iCurIndex;
}
bool TextureMgr::Release()
{
	Texture *pPoint;
	for (TemplateMapItor itor = TMap.begin(); itor != TMap.end(); itor++)
	{
		pPoint = (Texture *)(*itor).second;
		pPoint->Release();
	}
	TMap.clear();
	return true;
}
Texture* const TextureMgr::GetPtr(INT iIndex)
{
	TemplateMapItor itor = TMap.find(iIndex);
	if (itor == TMap.end()) return nullptr;
	Texture *pPoint = (*itor).second;
	return pPoint;
}
Texture* const TextureMgr::GetPtr(T_STR strFindName)
{
	if (strFindName.c_str() == nullptr) { return nullptr; }
	for (TemplateMapItor itor = TMap.begin(); itor != TMap.end(); itor++)
	{
		Texture *pPoint = (Texture *)(*itor).second;
		if (pPoint->m_szName == strFindName)
		{
			return (*itor).second;
		}
	}
	return nullptr;
}
const TCHAR*	TextureMgr::SplitPath(const TCHAR* FileName)
{

	TCHAR szFileName[MAX_PATH];
	TCHAR Drive[MAX_PATH];
	TCHAR Dir[MAX_PATH];
	TCHAR FName[MAX_PATH];
	TCHAR Ext[MAX_PATH];
	if (FileName)
	{
		_tsplitpath(FileName, Drive, Dir, FName, Ext);
		Ext[4] = 0;
		memset(szFileName, 0, sizeof(TCHAR) * MAX_PATH);
		if (_tcsicmp(Ext, _T(".tga")) == 0)
		{
			_tcscpy(Ext, _T(".dds"));
		}
	}
	_stprintf_s(szFileName, _T("%s%s"), FName, Ext);
	

	return szFileName;
}

TextureMgr::TextureMgr(void)
{
	m_pd3dDevice = NULL;
	m_iCurIndex = 0;
	TMap.clear();
}

TextureMgr::~TextureMgr(void)
{
	Texture *pPoint;
	for (TemplateMapItor itor = TMap.begin(); itor != TMap.end(); itor++)
	{
		pPoint = (Texture *)(*itor).second;
		pPoint->Release();
		SAFE_DEL(pPoint);
	}
	TMap.clear();
	m_iCurIndex = 0;
}

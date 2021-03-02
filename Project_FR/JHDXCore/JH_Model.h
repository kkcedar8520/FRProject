#pragma once



#include"JH_DXStd.h"
#include"TextureMgr.h"


#pragma warning( disable:4005 )

struct P_VERTEX
{
	D3DXVECTOR3 p;
};
struct PC_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR4 c;
};
struct PCT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR4 c;
	D3DXVECTOR2 t;
	bool operator == (const PCT_VERTEX& v)
	{
		if (p == v.p && c == v.c && t == v.t)
		{
			return true;
		}
		return false;
	}
	PCT_VERTEX() {}
	PCT_VERTEX(D3DXVECTOR3 p, D3DXVECTOR4 c, D3DXVECTOR2 t)
	{
		this->p = p;
		this->c = c;
		this->t = t;
	}
};
struct PNCT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	D3DXVECTOR4 c;
	D3DXVECTOR2 t;
	bool operator == (const PNCT_VERTEX& v)
	{
		if (p == v.p && c == v.c && t == v.t&&n==v.n)
		{
			return true;
		}
		return false;
	}
	PNCT_VERTEX() {}
	PNCT_VERTEX(D3DXVECTOR3 p, D3DXVECTOR3 n, D3DXVECTOR4 c, D3DXVECTOR2 t)
	{
		this->p = p;
		this->n = n;
		this->c = c;
		this->t = t;
	}
};
struct PNCT2T3_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	D3DXVECTOR4 c;
	D3DXVECTOR2 t;
	D3DXVECTOR3 t3;
	bool operator == (const PNCT2T3_VERTEX& v)
	{
		if (p == v.p && c == v.c && t == v.t&&n == v.n&&n == v.t3)
		{
			return true;
		}
		return false;
	}
	PNCT2T3_VERTEX() {}
	PNCT2T3_VERTEX(D3DXVECTOR3 p, D3DXVECTOR3 n, D3DXVECTOR4 c, D3DXVECTOR2 t, D3DXVECTOR3 t3)
	{
		this->p = p;
		this->n = n;
		this->c = c;
		this->t = t;
		this->t3 = t3;
	}
};
struct PNCTIW_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	D3DXVECTOR4 c;
	D3DXVECTOR2 t;
	D3DXVECTOR4 i;
	D3DXVECTOR4 w;
	bool operator == (const PNCTIW_VERTEX& v)
	{
		if (p == v.p && c == v.c && t == v.t&&n == v.n)
		{
			return true;
		}
		return false;
	}
	PNCTIW_VERTEX() {}
	PNCTIW_VERTEX(D3DXVECTOR3 p, D3DXVECTOR3 n, D3DXVECTOR4 c, D3DXVECTOR2 t, D3DXVECTOR4 i, D3DXVECTOR4 w)
	{
		this->p = p;
		this->n = n;
		this->c = c;
		this->t = t;
		this->i = i;
		this->w = w;
	}
};
struct CB_TF
{
	D3DXMATRIX matWorld;
	D3DXMATRIX matView;
	D3DXMATRIX matProj;
	D3DXMATRIX matNormal;
	D3DXVECTOR4 d;
};

class JH_Model
{
public:
	D3DXMATRIX	m_matNormal;
	D3DXMATRIX	m_matWorld;
	D3DXMATRIX	m_matView;
	D3DXMATRIX  m_matProj;
public:
	std::vector<PNCT_VERTEX>	m_VertexData;
	std::vector<DWORD>			m_IndexData;
	CB_TF						m_cbData;
	//Light ContanBuffer;
	ComPtr<ID3D11Buffer>		m_pLightConstBuffer;
	D3DXVECTOR3 m_Pos;

	//Normal
	std::vector<D3DXVECTOR3>										 m_TangentList;
	Microsoft::WRL::ComPtr<ID3D11Buffer>							 m_pTangentVB;
	ID3D11ShaderResourceView*										 m_pNormSrv=nullptr;
	int																 m_iTexNum;
	T_STR															 m_pNormMapFileName;
public:
	void CreateTangentSpaceVectors(D3DXVECTOR3 *v1, D3DXVECTOR3 *v2, D3DXVECTOR3 *v3,
		float v1u, float v1v,
		float v2u, float v2v,
		float v3u, float v3v,
		D3DXVECTOR3 *vTangent);
	void SetLightConstantBuffer(ID3D11Buffer* Buffer);
public:
	virtual void    SetMatrix(D3DXMATRIX* matWorld, D3DXMATRIX* matView, D3DXMATRIX* matProj);
	bool    Create(ID3D11Device*,
		ID3D11DeviceContext*,
		const TCHAR* pszShaderFileName,
		const TCHAR* pszTexFileName,
		const TCHAR* pszNormalTexName=nullptr,
		const CHAR* pszVSName = "VS",
		const CHAR* pszPSName = "PS");
	virtual HRESULT CreateVertexData();
	virtual HRESULT CreateIndexData();
	virtual HRESULT CreateVertexBuffer();
	virtual HRESULT CreateIndexBuffer();
	virtual HRESULT CreateConstantBuffer();
	virtual HRESULT LoadShader(const TCHAR* pszShaderFileName,
		const CHAR* pszVSName = "VS",
		const CHAR* pszPSName = "PS");
	virtual HRESULT CreateInputLayout();
	virtual HRESULT	LoadTexture(const TCHAR* pszTexFileName,const TCHAR* pszNormalTexName=nullptr);
	virtual bool	UpdateBuffer();
	virtual bool	UpdateTangentBuffer();
public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
	virtual	bool PostRender();
	virtual bool PreRender();
public:
	JH_DXHelperEX	m_dxHelper;
public:
	JH_Model();
	virtual ~JH_Model();
};


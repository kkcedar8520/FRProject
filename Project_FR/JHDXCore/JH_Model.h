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
struct PNCTIW_VERTEX:public PNCT_VERTEX
{

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
};

class JH_Model
{
public:
	UINT	m_iVertexSize;
	UINT	m_iNumVertex;
	UINT	m_iNumIndex;
protected:
	//DX
	ComPtr<ID3D11Device>		m_pd3dDevice;
	ComPtr<ID3D11DeviceContext>	m_pContext;

	ComPtr<ID3D11Buffer>				m_pVertexBuffer;
	ComPtr<ID3D11Buffer>				m_pIndexBuffer;
	ComPtr<	ID3D11Buffer>				m_pConstantBuffer;
	ComPtr<ID3D11InputLayout>			m_pVertexLayout;


	ComPtr<ID3D11VertexShader>			m_pVS;
	ComPtr<ID3D11PixelShader>			m_pPS;
	ComPtr<ID3D11ShaderResourceView>	m_pSRV;



	ComPtr<ID3DBlob>					m_pVertexCode;
	ComPtr<ID3DBlob>					m_pPixelCode;
public:
	//Transform
	D3DXMATRIX							m_matFinal;
	D3DXMATRIX							m_matTransform;
	D3DXMATRIX							m_matNormal;
	D3DXMATRIX							m_matWorld;
	D3DXMATRIX							m_matView;
	D3DXMATRIX							m_matProj;
public:
	std::vector<PNCT_VERTEX>			m_VertexData;
	std::vector<DWORD>					m_IndexData;
	CB_TF								m_cbData;
	//Light ContanBuffer;
	ComPtr<ID3D11Buffer>				m_pLightConstBuffer;
	//Instance
	ComPtr<ID3D11Buffer>				m_pInstancingBuffer;
	vector<D3DXMATRIX>					m_matInstanceWorld;

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
	virtual void    SetMatrix(D3DXMATRIX* matWorld=nullptr, D3DXMATRIX* matView=nullptr, D3DXMATRIX* matProj=nullptr);
	bool			Create(ID3D11Device*,
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
	virtual HRESULT CreateInstancingBuffer();
	virtual HRESULT LoadShader(const TCHAR* pszShaderFileName,
		const CHAR* pszVSName = "VS",
		const CHAR* pszPSName = "PS");
	virtual HRESULT CreateInputLayout();
	virtual HRESULT	LoadTexture(const TCHAR* pszTexFileName,const TCHAR* pszNormalTexName=nullptr);
	virtual bool	UpdateBuffer(ID3D11Buffer* pBuffer, void* Data);
	virtual bool	UpdateTangentBuffer();
	virtual void	UpdateConstantBuffer(ID3D11Buffer* pConstantBuffer, void* Data);
	virtual void	SetTransform(D3DXMATRIX& Mat);
	virtual void	SetPos(D3DXVECTOR3 vPos);
	virtual void	SetScale(D3DXVECTOR3 vScale);
	virtual void	SetRotation(D3DXMATRIX Mat);
public:


	ID3D11Device*		 GetDevice() { return m_pd3dDevice.Get(); }
	ID3D11DeviceContext* GetDeviceContext() { return m_pContext.Get(); }
	ID3D11Buffer*		 GetConstantBuffer() { return m_pConstantBuffer.Get(); }
	ID3D11Buffer*		 GetVertexBuffer() { return m_pVertexBuffer.Get(); }
	ID3D11Buffer**		 GetVertexBufferAddress() { return m_pVertexBuffer.GetAddressOf(); }

	ID3D11Buffer*		 GetIndexBuffer() { return m_pIndexBuffer.Get(); }
	ID3D11Buffer**		 GetIndexBufferAddress() { return m_pIndexBuffer.GetAddressOf(); }

	ID3D11Buffer*		 GetInstanceBuffer() { return m_pInstancingBuffer.Get(); }
	ID3D11Buffer**		 GetInstanceBufferAddress() { return m_pInstancingBuffer.GetAddressOf(); }

	vector<D3DXMATRIX>&	 GetInstanceMatrix() { return m_matInstanceWorld; }


	ID3DBlob*			 GetVertexCode() { return m_pVertexCode.Get(); }
	ID3DBlob*		     GetPixelCode() { return m_pPixelCode.Get(); }

	ID3DBlob**			 GetVertexCodeAddress() { return m_pVertexCode.GetAddressOf(); }
	ID3DBlob**		     GetPixelCodeAddress() { return m_pPixelCode.GetAddressOf(); }

	ID3D11VertexShader*	 GetVertexShader() { return m_pVS.Get(); }
	ID3D11PixelShader*   GetPixelShader() { return m_pPS.Get(); }

	ID3D11VertexShader** GetVertexShaderAddress() { return m_pVS.GetAddressOf(); }
	ID3D11PixelShader**  GetPixelShaderAddress() { return m_pPS.GetAddressOf(); }

	ID3D11InputLayout**  GetLayoutAdress() { return m_pVertexLayout.GetAddressOf(); }


	ID3D11ShaderResourceView*  GetShaderResourceView() { return m_pSRV.Get(); }
	ID3D11ShaderResourceView** GetShaderResourceViewAddress() { return m_pSRV.GetAddressOf(); }

	//Set
	void	SetConstantBuffer(ID3D11Buffer* ConstantBuffer) { m_pConstantBuffer = ConstantBuffer; }
	void	SetDevice(ID3D11Device* pDevice) { m_pd3dDevice = pDevice; }
	void	SetDeviceContext(ID3D11DeviceContext* pContext) { m_pContext = pContext; }
	void	SetShaderResourceView(ID3D11ShaderResourceView* srv) { m_pSRV = srv; }

	//

public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
	virtual	bool PostRender();
	virtual bool PreRender();
	
public:
	JH_Model();
	virtual ~JH_Model();
};


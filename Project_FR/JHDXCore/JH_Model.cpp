#include "JH_Model.h"
#include"TextureMgr.h"
void    JH_Model::SetMatrix(D3DXMATRIX* matWorld,
	D3DXMATRIX* matView,
	D3DXMATRIX* matProj)
{
	if (matWorld != nullptr)
	{
		m_matWorld = *matWorld;
	}
	if (matView != nullptr)
	{
		m_matView = *matView;
	}
	if (matProj != nullptr)
	{
		m_matProj = *matProj;
	}
	m_dxHelper.GetDeviceContext()->UpdateSubresource(
		m_dxHelper.GetConstantBuffer(),
		0, NULL, &m_cbData, 0, 0);

	D3DXMatrixTranspose(&m_cbData.matWorld, &m_matWorld);//GPU의축과 다이렉트의 축이다름
	D3DXMatrixTranspose(&m_cbData.matView, &m_matView);//
	D3DXMatrixTranspose(&m_cbData.matProj, &m_matProj);//
	
	m_cbData.d.x = cosf(g_fProgramTime) *0.5f + 0.5f;
	D3D11_MAPPED_SUBRESOURCE mss;

	m_dxHelper.GetDeviceContext()->UpdateSubresource(
		m_dxHelper.GetConstantBuffer(),
		0, NULL, &m_cbData, 0, 0);

}
void JH_Model::SetLightBuffer(ID3D11Buffer* buffer)
{

	m_pLightConstBuffer.Attach(buffer);
}


HRESULT JH_Model::CreateVertexData()
{
	return S_OK;
}
HRESULT JH_Model::CreateIndexData()
{
	return S_OK;
}

HRESULT JH_Model::CreateVertexBuffer()
{
	HRESULT hr = S_OK;
	if (m_VertexData.size() <= 0) return E_FAIL;

	m_dxHelper.m_iNumVertex = m_VertexData.size();
	D3D11_BUFFER_DESC pDesc;
	ZeroMemory(&pDesc, sizeof(D3D11_BUFFER_DESC));
	pDesc.Usage = D3D11_USAGE_DEFAULT;
	pDesc.ByteWidth = m_dxHelper.m_iVertexSize * m_VertexData.size();
	pDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA pInitialData;
	ZeroMemory(&pInitialData,
		sizeof(D3D11_SUBRESOURCE_DATA));
	pInitialData.pSysMem = &m_VertexData.at(0);

	hr = m_dxHelper.GetDevice()->CreateBuffer(&pDesc,
		&pInitialData,
		m_dxHelper.GetVertexBufferAddress());
	return hr;
}
HRESULT JH_Model::CreateIndexBuffer()
{
	HRESULT hr = S_OK;
	if (m_IndexData.size() <= 0) return S_OK;
	m_dxHelper.m_iNumIndex = m_IndexData.size();

	D3D11_BUFFER_DESC pDesc;
	ZeroMemory(&pDesc, sizeof(D3D11_BUFFER_DESC));
	pDesc.Usage = D3D11_USAGE_DEFAULT;
	pDesc.ByteWidth = sizeof(DWORD) * m_IndexData.size();
	pDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	D3D11_SUBRESOURCE_DATA pInitialData;
	ZeroMemory(&pInitialData,
		sizeof(D3D11_SUBRESOURCE_DATA));
	pInitialData.pSysMem = &m_IndexData.at(0);

	hr = m_dxHelper.GetDevice()->CreateBuffer(&pDesc,
		&pInitialData,
		m_dxHelper.GetIndexBufferAddress());
	return hr;
}
HRESULT JH_Model::CreateConstantBuffer()
{
	HRESULT hr=S_OK;
	ZeroMemory(&m_cbData, sizeof(CB_TF));
	m_cbData.d = D3DXVECTOR4(1, 1, 1, 1);
	m_cbData.d.x = g_fProgramTime;

	ComPtr<ID3D11Buffer> tcp; 
	tcp.Attach(DX::MakeConstantBuffer(m_dxHelper.GetDevice(), nullptr, 1, sizeof(CB_TF
		)));

	m_dxHelper.SetConstantBuffer(tcp.Get());

	//MAP_UNMAP CPU 개입할수있는 버퍼
	//D3D11_BUFFER_DESC pDesc;
	//ZeroMemory(&pDesc, sizeof(D3D11_BUFFER_DESC));
	//pDesc.Usage = D3D11_USAGE_DYNAMIC;
	//pDesc.ByteWidth = sizeof(CB_TF);
	//pDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//pDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	//D3D11_SUBRESOURCE_DATA pInitialData;
	//ZeroMemory(&pInitialData,
	//	sizeof(D3D11_SUBRESOURCE_DATA));
	//pInitialData.pSysMem = &m_cbData;

	//hr = m_dxHelper.m_pd3dDevice->CreateBuffer(&pDesc,
	//	&pInitialData,
	//	&m_dxHelper.m_pConstantBuffer);
	return hr;
}

HRESULT JH_Model::LoadShader(const TCHAR* pszShaderFileName,
	const CHAR* pszVSName,
	const CHAR* pszPSName)
{
	HRESULT hr = S_OK;
	ID3DBlob* pErrorMsgs;
	//if (FAILED(hr = D3DCompileFromFile(L"vertexshader.hlsl",
	if (FAILED(hr = D3DX11CompileFromFile(
		pszShaderFileName,
		NULL,
		NULL,
		pszVSName,// pEntrypoint,
		"vs_5_0",
		0,
		0,
		NULL,
		m_dxHelper.GetVertexCodeAddress(),
		&pErrorMsgs,
		NULL)))
	{
		MessageBoxA(NULL, (char*)pErrorMsgs->GetBufferPointer(), "Error", MB_OK);
		return hr;
	}

	m_dxHelper.GetDevice()->CreateVertexShader(
		m_dxHelper.GetVertexCode()->GetBufferPointer(),
		m_dxHelper.GetVertexCode()->GetBufferSize(),
		NULL,
		m_dxHelper.GetVertexShaderAddress());

	if (FAILED(hr = D3DX11CompileFromFile(
		pszShaderFileName,
		NULL,
		NULL,
		pszPSName,// pEntrypoint,
		"ps_5_0",
		0,
		0,
		NULL,
		m_dxHelper.GetPixelCodeAddress(),
		&pErrorMsgs, NULL)))
	{
		MessageBoxA(NULL, (char*)pErrorMsgs->GetBufferPointer(), "Error", MB_OK);
		return hr;
	}
		m_dxHelper.GetDevice()->CreatePixelShader(
		m_dxHelper.GetPixelCode()->GetBufferPointer(),
		m_dxHelper.GetPixelCode()->GetBufferSize(),
		NULL,
		m_dxHelper.GetPixelShaderAddress());
	return hr;
}
HRESULT JH_Model::CreateInputLayout()
{
	HRESULT hr = S_OK;
	const D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",  0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEX",  0, DXGI_FORMAT_R32G32_FLOAT, 0, 40,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		/*{"TANGENT",0,DXGI_FORMAT_R32G32B32_FLOAT,0,48,D3D11_INPUT_PER_VERTEX_DATA,0},*/
		// 가중치 인덱스 
		/*{ "TEX",  1, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 48,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEX",  2, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 64,  D3D11_INPUT_PER_VERTEX_DATA, 0 },*/
	};
	UINT iElementCount = sizeof(layout) /
		sizeof(layout[0]);
	m_dxHelper.GetDevice()->CreateInputLayout(
		layout,
		iElementCount,
		m_dxHelper.GetVertexCode()->GetBufferPointer(),
		m_dxHelper.GetVertexCode()->GetBufferSize(),
		m_dxHelper.GetLayoutAdress());
	return hr;
}
bool    JH_Model::Create(
	ID3D11Device* pd3dDevice,
	ID3D11DeviceContext* pContext,
	const TCHAR* pszShaderFileName,
	const TCHAR* pszTexFileName,
	const CHAR* pszVSName,
	const CHAR* pszPSName)
{
	m_dxHelper.SetDevice(pd3dDevice);
	m_dxHelper.SetDeviceContext( pContext);
	if (!Init())
	{
		return false;
	}
	if (FAILED(LoadShader(pszShaderFileName, pszVSName, pszPSName)))
	{
		return false;
	}
	if (FAILED(CreateVertexData()))
	{
		return false;
	}
	if (FAILED(CreateIndexData()))
	{
		return false;
	}
	if (FAILED(CreateVertexBuffer()))
	{
		return false;

	}
	if (FAILED(CreateIndexBuffer()))
	{
		return false;
	}
	if (FAILED(CreateConstantBuffer()))
	{
		return false;
	}
	if (FAILED(UpdateBuffer()))
	{
		return false;
	}
	if (FAILED(CreateInputLayout()))
	{
		return false;
	}
	if (FAILED(LoadTexture(pszTexFileName)))
	{
		return false;
	}
	return true;
}
HRESULT	JH_Model::LoadTexture(const TCHAR* pszTexFileName)
{
	if (pszTexFileName == nullptr) { return S_FALSE; }
	HRESULT hr = S_OK;
	//if (pszTexFileName == NULL) return S_OK;
	//hr = D3DX11CreateShaderResourceViewFromFile(
	//	m_dxHelper.GetDevice(),
	//	pszTexFileName,
	//	NULL,
	//	NULL,
	//	m_dxHelper.GetShaderResourceViewAddress(),
	//	NULL);

	I_Texture.Add(m_dxHelper.GetDevice(), pszTexFileName,L"../../data/Texture/");
	if(I_Texture.GetPtr(pszTexFileName)!=nullptr)
	m_dxHelper.SetShaderResourceView(I_Texture.GetPtr(pszTexFileName)->m_pTextureRV);


	return hr;
}
bool	JH_Model::UpdateBuffer()
{
	return true;
}
bool	JH_Model::Init()
{
	return true;
}
bool	JH_Model::Frame()
{
	return true;
}
bool	JH_Model::PreRender()
{
	m_dxHelper.PreRender();
	return true;
}
bool	JH_Model::Render()
{
	PreRender();
	PostRender();
	return true;
}
bool	JH_Model::PostRender()
{
	m_dxHelper.PostRender();
	return true;
}
bool	JH_Model::Release()
{
	m_VertexData.clear();
	m_IndexData.clear();
	return true;
}

JH_Model::JH_Model()
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matView);
	D3DXMatrixIdentity(&m_matProj);
	D3DXMatrixIdentity(&m_matNormal);
	m_cbData.d = D3DXVECTOR4(1, 1, 1, 1);
	m_Pos= D3DXVECTOR3(0,0,0);
}


JH_Model::~JH_Model()
{
	Release();
}

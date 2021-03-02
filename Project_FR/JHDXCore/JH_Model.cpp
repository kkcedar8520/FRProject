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
void JH_Model::SetLightConstantBuffer(ID3D11Buffer* Buffer)
{
	m_pLightConstBuffer=Buffer;
}

void JH_Model::CreateTangentSpaceVectors(D3DXVECTOR3 *v1, D3DXVECTOR3 *v2, D3DXVECTOR3 *v3,
	float v1u, float v1v,
	float v2u, float v2v,
	float v3u, float v3v,
	D3DXVECTOR3 *vTangent)
{
	D3DXVECTOR3 vEdge1 = *v2 - *v1;
	D3DXVECTOR3 vEdge2 = *v3 - *v1;

	//접선공간의 좌표를 텍스쳐좌표로 활용하여 표현
	// 접선공간의 벡터 Q-P1=(u-u1)T+(v-v1)B; Q(u,v) P1은 정점  이공식을 이용하여 탄젠트벡터와 바이노말벡터를 구함
	float fEdge1U = v2u - v1u;//s1
	float fEdge1V = v2v - v1v;//t1

	float fEdge2U = v3u - v1u;//s2
	float fEdge2V = v3v - v1v;//t2


	float fDenominator = fEdge1U * fEdge2V - fEdge1V * fEdge2U;
	float fScale = 1.0f / fDenominator;

	D3DXVECTOR3 T;//t2 -t1   (vEdge1.x,y,z)
				  //-s2  s1	(vEdge2.x,y,z)
	T.x = fScale * (fEdge2V*vEdge1.x + (-fEdge1V * vEdge2.x));
	T.y = fEdge2V * vEdge1.y + (-fEdge1V * vEdge2.y);
	T.z = fEdge2V * vEdge1.z + (-fEdge1V * vEdge2.z);

	D3DXVec3Normalize(&T, &T);
	vTangent = &T;


}

bool	JH_Model::UpdateTangentBuffer()
{
	D3DXVECTOR3 vTangent, vBiNormal, vNormal;
	int iIndex = 0;
	int i0, i1, i2, i3, i4, i5;

	if (m_VertexData.size() <= 0) { return false; }
	m_TangentList.resize(m_VertexData.size());
	for (int iIndex = 0; iIndex < m_dxHelper.m_iNumIndex; iIndex += 3)
	{

		i0 = m_IndexData[iIndex + 0];
		i1 = m_IndexData[iIndex + 1];
		i2 = m_IndexData[iIndex + 2];

		CreateTangentSpaceVectors(&m_VertexData[i0].p, &m_VertexData[i1].p, &m_VertexData[i2].p,
			m_VertexData[i0].t.x, m_VertexData[i0].t.y,
			m_VertexData[i1].t.x, m_VertexData[i1].t.y,
			m_VertexData[i2].t.x, m_VertexData[i2].t.y,
			&vTangent);

		m_TangentList[i0] += vTangent;

		i0 = m_IndexData[iIndex + 1];
		i1 = m_IndexData[iIndex + 2];
		i2 = m_IndexData[iIndex + 0];

		CreateTangentSpaceVectors(&m_VertexData[i0].p, &m_VertexData[i1].p, &m_VertexData[i2].p,
			m_VertexData[i0].t.x, m_VertexData[i0].t.y,
			m_VertexData[i1].t.x, m_VertexData[i1].t.y,
			m_VertexData[i2].t.x, m_VertexData[i2].t.y,
			&vTangent);

		m_TangentList[i0] += vTangent;

		i0 = m_IndexData[iIndex + 2];
		i1 = m_IndexData[iIndex + 0];
		i2 = m_IndexData[iIndex + 1];

		CreateTangentSpaceVectors(&m_VertexData[i0].p, &m_VertexData[i1].p, &m_VertexData[i2].p,
			m_VertexData[i0].t.x, m_VertexData[i0].t.y,
			m_VertexData[i1].t.x, m_VertexData[i1].t.y,
			m_VertexData[i2].t.x, m_VertexData[i2].t.y,
			&vTangent);

		m_TangentList[i0] += vTangent;

	}
	for (int i = 0; i < m_TangentList.size(); i++)
	{
		D3DXVec3Normalize(&m_TangentList[i0], &m_TangentList[i0]);
	}


	m_pTangentVB.Attach(DX::CreateVertexBuffer(m_dxHelper.GetDevice(), &m_TangentList.at(0), m_TangentList.size(), sizeof(D3DXVECTOR3)));


	return true;
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
	const TCHAR* pszNormalTexName,
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

	if (FAILED(LoadTexture(pszTexFileName,pszNormalTexName)))
	{
		return false;
	}
	if (!UpdateTangentBuffer())
	{
		return false;
	}
	return true;
}
HRESULT	JH_Model::LoadTexture(const TCHAR* pszTexFileName, const TCHAR* pszNormalTexName)
{
	if (pszTexFileName == nullptr) { return S_FALSE; }
	HRESULT hr = S_OK;


	int iTex=I_Texture.Add(m_dxHelper.GetDevice(), pszTexFileName);
	if(I_Texture.GetPtr(iTex)!=nullptr)
	m_dxHelper.SetShaderResourceView(I_Texture.GetPtr(iTex)->m_pTextureRV);

	if (pszNormalTexName == nullptr) return S_OK;

	iTex=I_Texture.Add(m_dxHelper.GetDevice(), pszNormalTexName);
	if (I_Texture.GetPtr(iTex) != nullptr)
		m_pNormSrv=I_Texture.GetPtr(iTex)->m_pTextureRV;

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

	UINT offset = 0;
	UINT stride = sizeof(D3DXVECTOR3);
	if (m_pNormSrv != nullptr)
	{
		m_dxHelper.GetDeviceContext()->PSSetShaderResources(1, 1, &m_pNormSrv);
		m_dxHelper.GetDeviceContext()->IASetVertexBuffers(1, 1, m_pTangentVB.GetAddressOf(), &stride, &offset);
	}
	if (m_pLightConstBuffer != nullptr)
	{
		m_dxHelper.GetDeviceContext()->VSSetConstantBuffers(1, 1, m_pLightConstBuffer.GetAddressOf());
		m_dxHelper.GetDeviceContext()->PSSetConstantBuffers(1, 1, m_pLightConstBuffer.GetAddressOf());
	}
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

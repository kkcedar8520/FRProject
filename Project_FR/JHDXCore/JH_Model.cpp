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
	DX::GetContext()->UpdateSubresource(
		GetConstantBuffer(),
		0, NULL, &m_cbData, 0, 0);
	
	D3DXVECTOR3 vS, vP;
	D3DXQUATERNION qR;
	D3DXMATRIX mR, mS;
	D3DXMatrixDecompose(&vS, &qR, &vP, &m_matTransform);


	D3DXMatrixRotationQuaternion(&mR, &qR);
	D3DXMatrixScaling(&mS, vS.x, vS.y, vS.z);
	m_matTransform = mS * mR;
	m_matTransform._41 = vP.x;
	m_matTransform._42 = vP.y;
	m_matTransform._43 = vP.z;

	D3DXMatrixDecompose(&vS, &qR, &vP, &m_matWorld);


	D3DXMatrixRotationQuaternion(&mR, &qR);
	D3DXMatrixScaling(&mS, vS.x, vS.y, vS.z);
	m_matWorld = mS * mR;
	m_matWorld._41 = vP.x;
	m_matWorld._42 = vP.y;
	m_matWorld._43 = vP.z;
	m_matFinal= m_matTransform*m_matWorld;
	
	D3DXMatrixTranspose(&m_cbData.matWorld, &m_matFinal);//GPU의축과 다이렉트의 축이다름
	D3DXMatrixTranspose(&m_cbData.matView, &m_matView);//
	D3DXMatrixTranspose(&m_cbData.matProj, &m_matProj);//
	
	m_cbData.d.x = cosf(g_fProgramTime) *0.5f + 0.5f;
	D3D11_MAPPED_SUBRESOURCE mss;

	GetDeviceContext()->UpdateSubresource(
		GetConstantBuffer(),
		0, NULL, &m_cbData, 0, 0);

}
void JH_Model::SetTransform(D3DXMATRIX& Mat)
{
	m_matTransform = Mat;
}
void JH_Model::SetPos(D3DXVECTOR3 vPos)
{
	m_matTransform._41 = vPos.x;
	m_matTransform._42 = vPos.y;
	m_matTransform._43 = vPos.z;
}
void JH_Model::SetScale(D3DXVECTOR3 vScale)
{
	D3DXVECTOR3 vS, vP;
	D3DXQUATERNION qR;
	D3DXMATRIX mR,mS;
	D3DXMatrixDecompose(&vS, &qR, &vP, &m_matTransform);
	vS = vScale;
	
	D3DXMatrixRotationQuaternion(&mR, &qR);
	D3DXMatrixScaling(&mS, vS.x, vS.y, vS.z);
	m_matTransform = mS * mR;
	m_matTransform._41 = vP.x;
	m_matTransform._42 = vP.y;
	m_matTransform._43 = vP.z;
	
}
void JH_Model::SetRotation(D3DXMATRIX Mat)
{
	D3DXVECTOR3 vS, vP;
	D3DXQUATERNION qR;
	D3DXMATRIX mR, mS;
	D3DXMatrixDecompose(&vS, &qR, &vP, &m_matTransform);
	
	mR = Mat;
	D3DXMatrixScaling(&mS, vS.x, vS.y, vS.z);
	m_matTransform = mS * mR;
	m_matTransform._41 = vP.x;
	m_matTransform._42 = vP.y;
	m_matTransform._43 = vP.z;
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
	for (int iIndex = 0; iIndex < m_iNumIndex; iIndex += 3)
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


	m_pTangentVB.Attach(DX::CreateVertexBuffer(GetDevice(), &m_TangentList.at(0), m_TangentList.size(), sizeof(D3DXVECTOR3)));


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

	m_iNumVertex = m_VertexData.size();
	D3D11_BUFFER_DESC pDesc;
	ZeroMemory(&pDesc, sizeof(D3D11_BUFFER_DESC));
	pDesc.Usage = D3D11_USAGE_DEFAULT;
	pDesc.ByteWidth = m_iVertexSize * m_VertexData.size();
	pDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA pInitialData;
	ZeroMemory(&pInitialData,
		sizeof(D3D11_SUBRESOURCE_DATA));
	pInitialData.pSysMem = &m_VertexData.at(0);

	hr = GetDevice()->CreateBuffer(&pDesc,
		&pInitialData,
		GetVertexBufferAddress());
	return hr;
}
HRESULT JH_Model::CreateIndexBuffer()
{
	HRESULT hr = S_OK;
	if (m_IndexData.size() <= 0) return S_OK;
	m_iNumIndex = m_IndexData.size();

	D3D11_BUFFER_DESC pDesc;
	ZeroMemory(&pDesc, sizeof(D3D11_BUFFER_DESC));
	pDesc.Usage = D3D11_USAGE_IMMUTABLE;
	pDesc.ByteWidth = sizeof(DWORD) * m_IndexData.size();
	pDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	D3D11_SUBRESOURCE_DATA pInitialData;
	ZeroMemory(&pInitialData,
		sizeof(D3D11_SUBRESOURCE_DATA));
	pInitialData.pSysMem = &m_IndexData.at(0);

	hr = GetDevice()->CreateBuffer(&pDesc,
		&pInitialData,
		GetIndexBufferAddress());
	return hr;
}
HRESULT JH_Model::CreateConstantBuffer()
{
	HRESULT hr=S_OK;
	ZeroMemory(&m_cbData, sizeof(CB_TF));
	m_cbData.d = D3DXVECTOR4(1, 1, 1, 1);
	m_cbData.d.x = g_fProgramTime;

	ComPtr<ID3D11Buffer> tcp; 
	tcp.Attach(DX::MakeConstantBuffer(GetDevice(), nullptr, 1, sizeof(CB_TF
		)));

	SetConstantBuffer(tcp.Get());

	
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

	//hr = m_pd3dDevice->CreateBuffer(&pDesc,
	//	&pInitialData,
	//	&m_pConstantBuffer);
	return hr;
}
HRESULT JH_Model::CreateInstancingBuffer()
{

	
	HRESULT hr = S_OK;
	if (GetInstanceMatrix().size() <= 0) { return S_FALSE; }
	
	D3D11_BUFFER_DESC pDesc;
	ZeroMemory(&pDesc, sizeof(D3D11_BUFFER_DESC));
	pDesc.Usage = D3D11_USAGE_DEFAULT;
	pDesc.ByteWidth = sizeof(D3DXMATRIX) *GetInstanceMatrix().size();
	pDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA pInitialData;
	ZeroMemory(&pInitialData,
		sizeof(D3D11_SUBRESOURCE_DATA));
	pInitialData.pSysMem = GetInstanceMatrix().at(0);

	hr = GetDevice()->CreateBuffer(&pDesc,
		&pInitialData,
		GetVertexBufferAddress());
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
		GetVertexCodeAddress(),
		&pErrorMsgs,
		NULL)))
	{
		MessageBoxA(NULL, (char*)pErrorMsgs->GetBufferPointer(), "Error", MB_OK);
		return hr;
	}

	GetDevice()->CreateVertexShader(
		GetVertexCode()->GetBufferPointer(),
		GetVertexCode()->GetBufferSize(),
		NULL,
		GetVertexShaderAddress());

	if (FAILED(hr = D3DX11CompileFromFile(
		pszShaderFileName,
		NULL,
		NULL,
		pszPSName,// pEntrypoint,
		"ps_5_0",
		0,
		0,
		NULL,
		GetPixelCodeAddress(),
		&pErrorMsgs, NULL)))
	{
		MessageBoxA(NULL, (char*)pErrorMsgs->GetBufferPointer(), "Error", MB_OK);
		return hr;
	}
		GetDevice()->CreatePixelShader(
		GetPixelCode()->GetBufferPointer(),
		GetPixelCode()->GetBufferSize(),
		NULL,
		GetPixelShaderAddress());
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
		{"TANGENT",0,DXGI_FORMAT_R32G32B32_FLOAT,1,0,D3D11_INPUT_PER_VERTEX_DATA,0},

		{"INSTANCEWORLD",0,DXGI_FORMAT_R32G32B32_FLOAT,2,0,D3D11_INPUT_PER_INSTANCE_DATA,1},
		{"INSTANCEWORLD",1,DXGI_FORMAT_R32G32B32_FLOAT,2,16,D3D11_INPUT_PER_INSTANCE_DATA,1},
		{"INSTANCEWORLD",2,DXGI_FORMAT_R32G32B32_FLOAT,2,32,D3D11_INPUT_PER_INSTANCE_DATA,1},
		{"INSTANCEWORLD",3,DXGI_FORMAT_R32G32B32_FLOAT,2,48,D3D11_INPUT_PER_INSTANCE_DATA,1},

		// 가중치 인덱스 
		/*{ "TEX",  1, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 48,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEX",  2, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 64,  D3D11_INPUT_PER_VERTEX_DATA, 0 },*/
	};
	UINT iElementCount = sizeof(layout) /
		sizeof(layout[0]);
	GetDevice()->CreateInputLayout(
		layout,
		iElementCount,
		GetVertexCode()->GetBufferPointer(),
		GetVertexCode()->GetBufferSize(),
		GetLayoutAdress());
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
	SetDevice(pd3dDevice);
	SetDeviceContext( pContext);
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


	int iTex=I_Texture.Add(GetDevice(), pszTexFileName,L"../../data/Texture/");
	if(I_Texture.GetPtr(iTex)!=nullptr)
	SetShaderResourceView(I_Texture.GetPtr(iTex)->m_pTextureRV);

	if (pszNormalTexName == nullptr) return S_OK;

	iTex=I_Texture.Add(GetDevice(), pszNormalTexName, L"../../data/Texture/");
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
		GetDeviceContext()->PSSetShaderResources(1, 1, &m_pNormSrv);
		GetDeviceContext()->IASetVertexBuffers(1, 1, m_pTangentVB.GetAddressOf(), &stride, &offset);
	}
	if (m_pLightConstBuffer != nullptr)
	{
		GetDeviceContext()->VSSetConstantBuffers(1, 1, m_pLightConstBuffer.GetAddressOf());
		GetDeviceContext()->PSSetConstantBuffers(1, 1, m_pLightConstBuffer.GetAddressOf());
	}

	stride = m_iVertexSize;

	m_pContext->IASetVertexBuffers(
		0, 1, m_pVertexBuffer.GetAddressOf(), &stride, &offset);

	m_pContext->IASetIndexBuffer(m_pIndexBuffer.Get(),
		DXGI_FORMAT_R32_UINT, 0);

	m_pContext->VSSetShader(m_pVS.Get(), NULL, 0);
	m_pContext->PSSetShader(m_pPS.Get(), NULL, 0);

	m_pContext->VSSetConstantBuffers(0, 1, m_pConstantBuffer.GetAddressOf());
	m_pContext->PSSetConstantBuffers(0, 1, m_pConstantBuffer.GetAddressOf());
	m_pContext->IASetInputLayout(m_pVertexLayout.Get());
	m_pContext->PSSetShaderResources(0, 1, m_pSRV.GetAddressOf());
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

	if (m_matInstanceWorld.size() > 0 && m_iNumIndex > 0)
	{
		m_pContext->DrawIndexedInstanced(m_iNumIndex, m_matInstanceWorld.size(), 0, 0, 0);
	}
	else if (m_iNumIndex > 0)
	{
		m_pContext->DrawIndexed(m_iNumIndex, 0, 0);
	}
	else
	{
		m_pContext->Draw(m_iNumVertex, 0);
	}
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
	m_iVertexSize = 0;
	m_iNumVertex = 0;
	m_iNumIndex = 0;
	m_pVertexBuffer = nullptr;
	m_pIndexBuffer = nullptr;
	m_pVertexLayout = nullptr;
	m_pConstantBuffer = nullptr;
	m_pVS = nullptr;
	m_pPS = nullptr;
	m_pSRV = nullptr;

	D3DXMatrixIdentity(&m_matFinal);
	D3DXMatrixIdentity(&m_matTransform);
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

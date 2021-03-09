#include "JH_Mesh.h"
#include"JH_Obj.h"

JH_Mesh::JH_Mesh()
{


	m_iTexIndex = 0;
	m_iBaseVertex = 0;
	m_iNumVertex = 0;
	m_iBoneIndex = -1;


	D3DXMatrixIdentity(&m_matWorld);
}

JH_Mesh::~JH_Mesh()
{

}

//void JH_Mesh::SetTransform(D3DXMATRIX* world, D3DXMATRIX* view, D3DXMATRIX* proj)
//{
//	if (world!=nullptr)
//	{
//		m_matWorld *= *world;
//	}
//	if (world != nullptr)
//	{
//		m_matWorld = *world;
//	}
//	if (world != nullptr)
//	{
//		m_matWorld = *world;
//	}
//
//}
HRESULT JH_Mesh::CreateVertexData()
{
	JH_Model::m_iVertexSize = sizeof(PNCTIW_VERTEX);
	return S_OK;
}
HRESULT JH_Mesh::CreateVertexBuffer()
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
HRESULT	JH_Mesh::LoadTexture(const TCHAR* pszTexFileName, const TCHAR* pszNormalTexName)
{
	if (pszTexFileName == nullptr) { return S_FALSE; }
	HRESULT hr = S_OK;


	int iTex = I_Texture.Add(GetDevice(), pszTexFileName, L"../../data/Texture/");
	if (I_Texture.GetPtr(iTex) != nullptr)
		SetShaderResourceView(I_Texture.GetPtr(iTex)->m_pTextureRV);

	if (pszNormalTexName == nullptr) return S_OK;

	iTex = I_Texture.Add(GetDevice(), pszNormalTexName, L"../../data/Texture/");
	if (I_Texture.GetPtr(iTex) != nullptr)
		m_pNormSrv = I_Texture.GetPtr(iTex)->m_pTextureRV;

	return hr;
}

HRESULT JH_Mesh::CreateIndexData()
{
	return S_OK;
}

bool JH_Mesh::Init()
{
	return true;
}
bool JH_Mesh::Frame()
{
	return true;
}
bool JH_Mesh::Render()
{
	JH_Model::Render();
	
	return true;
}
bool JH_Mesh::Release()
{
	return true;
}

void JH_Mesh::Binding(JH_Obj* Obj)
{
	std::wstring tex=Obj->MaterialFindByName(m_MaterialName).Diffuse.c_str();
	JH_Model::Create(DX::GetDevice().Get(), DX::GetContext().Get(), L"../../data/shader/ObjShader.hlsl", tex.c_str());

	m_matWorld = m_Bone.GetWorld();
	m_matTransform= m_Bone.GetWorld();
}


#include "JH_Mesh.h"
#include"JH_Obj.h"

JH_Mesh::JH_Mesh()
{


	m_iTexIndex = 0;
	m_iBaseVertex = 0;
	m_iNumVertex = 0;
	m_iParentIndex = -1;


	D3DXMatrixIdentity(&m_matWorld);
}

JH_Mesh::~JH_Mesh()
{

}

HRESULT JH_Mesh::CreateVertexData()
{
	m_dxHelper.m_iVertexSize = sizeof(PNCTIW_VERTEX);
	return S_OK;
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
	UINT Stride = 0;
	UINT offset = 0;
	Stride = GetVertexSize();
	DX::GetContext()->IASetIndexBuffer(GetIndexBuffer(), DXGI_FORMAT_B8G8R8A8_UNORM, 0);
	DX::GetContext()->DrawIndexed(GetIndexData().size(), 0, 0);
	
	return true;
}
bool JH_Mesh::Release()
{
	return true;
}

void JH_Mesh::Binding(JH_Obj* Obj)
{

	//auto tex = Obj->MaterialFindByName(m_MaterialName).Diffuse.c_str();
//	JH_Model::Create(DX::GetDevice().Get(), DX::GetContext().Get(), L"../../data/shader/ObjShader.hlsl", tex);
	
}


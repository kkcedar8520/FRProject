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

bool JH_Mesh::Init()
{
	return true;
}
bool JH_Mesh::Frame()
{
	return true;
}
bool JH_Mesh::Render(ID3D11DeviceContext* pContext)
{
	UINT Stride = 0;
	UINT offset = 0;
	Stride = GetVertexSize();
	pContext->IASetIndexBuffer(GetIndexBuffer(), DXGI_FORMAT_B8G8R8A8_UNORM, 0);
	pContext->DrawIndexed(GetIndexData().size(), 0, 0);
	
	return true;
}
bool JH_Mesh::Release()
{
	return true;
}

void JH_Mesh::Binding(JH_Obj* Obj)
{
	m_iVertexSize = sizeof(PNCTIW_VERTEX);
	m_pVB = DX::CreateVertexBuffer(Obj->m_dxHelper.GetDevice(), &m_VertexData.at(0), m_VertexData.size(), sizeof(PNCTIW_VERTEX));
	m_pIB= DX::CreateIndexBuffer(Obj->m_dxHelper.GetDevice(), &m_IndicesData.at(0), m_IndicesData.size(), sizeof(int));

	m_Material;
}

void Binding(JH_Obj* Obj)
{

}
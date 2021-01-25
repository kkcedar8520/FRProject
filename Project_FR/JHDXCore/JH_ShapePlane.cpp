
#include"JH_Model.h"
#include "JH_ShapePlane.h"
#pragma warning( disable:4005 )
HRESULT JH_ShapePlane::CreateVertexData()
{
	HRESULT hr = S_OK;
	m_dxHelper.m_iVertexSize = sizeof(PNCT_VERTEX);
	m_VertexData.resize(4);
	m_VertexData[0].p = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
	m_VertexData[1].p = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	m_VertexData[2].p = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
	m_VertexData[3].p = D3DXVECTOR3(1.0f, -1.0f, 0.0f);

	m_VertexData[0].n = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_VertexData[1].n = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_VertexData[2].n = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_VertexData[3].n = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	m_VertexData[0].c = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	m_VertexData[1].c = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	m_VertexData[2].c = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	m_VertexData[3].c = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);

	m_VertexData[0].t = D3DXVECTOR2(0.0f, 0.0f);
	m_VertexData[1].t = D3DXVECTOR2(1.0f, 0.0f);
	m_VertexData[2].t = D3DXVECTOR2(0.0f, 1.0f);
	m_VertexData[3].t = D3DXVECTOR2(1.0f, 1.0f);
	//Convert(m_VertexData);	
	return hr;
}
HRESULT JH_ShapePlane::CreateIndexData()
{

	HRESULT hr = S_OK;
	m_IndexData.resize(6);
	m_IndexData[0] = 0;
	m_IndexData[1] = 1;
	m_IndexData[2] = 2;
	m_IndexData[3] = 2;
	m_IndexData[4] = 1;
	m_IndexData[5] = 3;
	return hr;
}
JH_ShapePlane::JH_ShapePlane()
{
}


JH_ShapePlane::~JH_ShapePlane()
{
}

#include "JH_ShapeLine.h"
#pragma warning( disable:4005 )
HRESULT JH_ShapeLine::CreateInputLayout()
{
	HRESULT hr = S_OK;
	const D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",  0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT iElementCount = sizeof(layout) /
		sizeof(layout[0]);
	hr = GetDevice()->CreateInputLayout(
		layout,
		iElementCount,
		GetVertexCode()->GetBufferPointer(),
		GetVertexCode()->GetBufferSize(),
		GetLayoutAdress());
	return hr;
}
HRESULT JH_ShapeLine::CreateVertexData()
{
	HRESULT hr = S_OK;
	m_iVertexSize = sizeof(PC_VERTEX);
	m_VertexLineData.resize(2);
	m_VertexLineData[0].p = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VertexLineData[1].p = D3DXVECTOR3(100.0f, 0.0f, 0.0f);
	m_VertexLineData[0].c = D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f);
	m_VertexLineData[1].c = D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f);
	//Convert(m_VertexData);	
	return hr;
}
HRESULT JH_ShapeLine::CreateIndexData()
{
	HRESULT hr = S_OK;
	/*m_IndexData.resize(2);
	m_IndexData[0] = 0;
	m_IndexData[1] = 1;*/
	return hr;
}
HRESULT JH_ShapeLine::CreateVertexBuffer()
{
	HRESULT hr = S_OK;
	if (m_VertexLineData.size() <= 0) return E_FAIL;
	m_iNumVertex = m_VertexLineData.size();
	D3D11_BUFFER_DESC pDesc;
	ZeroMemory(&pDesc, sizeof(D3D11_BUFFER_DESC));
	pDesc.Usage = D3D11_USAGE_DEFAULT;
	pDesc.ByteWidth = m_iVertexSize * m_VertexLineData.size();
	pDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA pInitialData;
	ZeroMemory(&pInitialData,
		sizeof(D3D11_SUBRESOURCE_DATA));
	pInitialData.pSysMem = &m_VertexLineData.at(0);

	hr = GetDevice()->CreateBuffer(&pDesc,
		&pInitialData,
		GetVertexBufferAddress());
	return hr;
}
bool JH_ShapeLine::PostRender()
{
	GetDeviceContext()->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	JH_Model::PostRender();

	GetDeviceContext()->IASetPrimitiveTopology(
		D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	return true;
}
bool	JH_ShapeLine::Draw(D3DXVECTOR3 v0, D3DXVECTOR3 v1, D3DXVECTOR4 color)
{
	m_VertexLineData[0].p = v0;
	m_VertexLineData[0].c = color;
	m_VertexLineData[1].p = v1;
	m_VertexLineData[1].c = color;
	GetDeviceContext()->UpdateSubresource(
		GetVertexBuffer(),
		0, NULL,
		&m_VertexLineData.at(0), 0, 0);
	return Render();
}


JH_ShapeLine::JH_ShapeLine()
{
}


JH_ShapeLine::~JH_ShapeLine()
{
}

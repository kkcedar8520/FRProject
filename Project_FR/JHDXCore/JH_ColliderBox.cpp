#include "JH_ColliderBox.h"
void JH_ColliderBox::UpdateBox()
{
	m_VertexData[0] = PNCT_VERTEX(D3DXVECTOR3(vMin.x, vMax.y, vMin.z), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexData[1] = PNCT_VERTEX(D3DXVECTOR3(vMax.x, vMax.y, vMin.z), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(1.0f, 0.0f));
	m_VertexData[2] = PNCT_VERTEX(D3DXVECTOR3(vMax.x, vMin.y, vMin.z), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(0.0f, 1.0f));
	m_VertexData[3] = PNCT_VERTEX(D3DXVECTOR3(vMin.x, vMin.y, vMin.z), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(1.0f, 1.0f));
	// Right
	m_VertexData[4] = PNCT_VERTEX(D3DXVECTOR3(vMax.x, vMax.y, vMax.z), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexData[5] = PNCT_VERTEX(D3DXVECTOR3(vMin.x, vMax.y, vMax.z), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(1.0f, 0.0f));
	m_VertexData[6] = PNCT_VERTEX(D3DXVECTOR3(vMin.x, vMin.y, vMax.z), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(0.0f, 1.0f));
	m_VertexData[7] = PNCT_VERTEX(D3DXVECTOR3(vMax.x, vMin.y, vMax.z), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(1.0f, 1.0f));
	// back
	m_VertexData[8] = PNCT_VERTEX(D3DXVECTOR3(vMax.x, vMax.y, vMin.z), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexData[9] = PNCT_VERTEX(D3DXVECTOR3(vMax.x, vMax.y, vMax.z), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(1.0f, 0.0f));
	m_VertexData[10] = PNCT_VERTEX(D3DXVECTOR3(vMax.x, vMin.y, vMax.z), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(0.0f, 1.0f));
	m_VertexData[11] = PNCT_VERTEX(D3DXVECTOR3(vMax.x, vMin.y, vMin.z), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(1.0f, 1.0f));
	// left
	m_VertexData[12] = PNCT_VERTEX(D3DXVECTOR3(vMin.x, vMax.y, vMax.z), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexData[13] = PNCT_VERTEX(D3DXVECTOR3(vMin.x, vMax.y, vMin.z), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(1.0f, 0.0f));
	m_VertexData[14] = PNCT_VERTEX(D3DXVECTOR3(vMin.x, vMin.y, vMin.z), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(0.0f, 1.0f));
	m_VertexData[15] = PNCT_VERTEX(D3DXVECTOR3(vMin.x, vMin.y, vMax.z), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(1.0f, 1.0f));
	// up
	m_VertexData[16] = PNCT_VERTEX(D3DXVECTOR3(vMin.x, vMax.y, vMax.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexData[17] = PNCT_VERTEX(D3DXVECTOR3(vMax.x, vMax.y, vMax.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(1.0f, 0.0f));
	m_VertexData[18] = PNCT_VERTEX(D3DXVECTOR3(vMax.x, vMax.y, vMin.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(0.0f, 1.0f));
	m_VertexData[19] = PNCT_VERTEX(D3DXVECTOR3(vMin.x, vMax.y, vMin.z), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(1.0f, 1.0f));
	// down
	m_VertexData[20] = PNCT_VERTEX(D3DXVECTOR3(vMin.x, vMin.y, vMin.z), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexData[21] = PNCT_VERTEX(D3DXVECTOR3(vMax.x, vMin.y, vMin.z), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(1.0f, 0.0f));
	m_VertexData[22] = PNCT_VERTEX(D3DXVECTOR3(vMax.x, vMin.y, vMax.z), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(0.0f, 1.0f));
	m_VertexData[23] = PNCT_VERTEX(D3DXVECTOR3(vMin.x, vMin.y, vMax.z), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(1.0f, 1.0f));





	UpdateVB();
}
HRESULT JH_ColliderBox::CreateVertexData()
{
	HRESULT hr = S_OK;
	m_iVertexSize = sizeof(PNCT_VERTEX);
	m_VertexData.resize(24);
	// front
	m_VertexData[0] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, 2.0f, -1.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexData[1] = PNCT_VERTEX(D3DXVECTOR3(1.0f, 2.0f, -1.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(1.0f, 0.0f));
	m_VertexData[2] = PNCT_VERTEX(D3DXVECTOR3(1.0f, 0.0f, -1.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(1.0f, 1.0f));
	m_VertexData[3] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, 0.0f, -1.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(0.0f, 1.0f));
	// back
	m_VertexData[4] = PNCT_VERTEX(D3DXVECTOR3(1.0f, 2.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexData[5] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, 2.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(1.0f, 0.0f));
	m_VertexData[6] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(1.0f, 1.0f));
	m_VertexData[7] = PNCT_VERTEX(D3DXVECTOR3(1.0f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(0.0f, 1.0f));
	// right
	m_VertexData[8] = PNCT_VERTEX(D3DXVECTOR3(1.0f, 2.0f, -1.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexData[9] = PNCT_VERTEX(D3DXVECTOR3(1.0f, 2.0f, 1.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(1.0f, 0.0f));
	m_VertexData[10] = PNCT_VERTEX(D3DXVECTOR3(1.0f, 0.0f, 1.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(1.0f, 1.0f));
	m_VertexData[11] = PNCT_VERTEX(D3DXVECTOR3(1.0f, 0.0f, -1.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(0.0f, 1.0f));
	// left
	m_VertexData[12] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, 2.0f, 1.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexData[13] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, 2.0f, -1.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(1.0f, 0.0f));
	m_VertexData[14] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, 0.0f, -1.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(1.0f, 1.0f));
	m_VertexData[15] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, 0.0f, 1.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(0.0f, 1.0f));
	// up
	m_VertexData[16] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, 2.0f, 1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexData[17] = PNCT_VERTEX(D3DXVECTOR3(1.0f, 2.0f, 1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(1.0f, 0.0f));
	m_VertexData[18] = PNCT_VERTEX(D3DXVECTOR3(1.0f, 2.0f, -1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(1.0f, 1.0f));
	m_VertexData[19] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, 2.0f, -1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(0.0f, 1.0f));
	// down
	m_VertexData[20] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, 0.0f, -1.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexData[21] = PNCT_VERTEX(D3DXVECTOR3(1.0f, 0.0f, -1.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(1.0f, 0.0f));
	m_VertexData[22] = PNCT_VERTEX(D3DXVECTOR3(1.0f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(1.0f, 1.0f));
	m_VertexData[23] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, 0.0f, 1.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.5f), D3DXVECTOR2(0.0f, 1.0f));

	return hr;
}
bool JH_ColliderBox::Frame()
{
	JH_Box::CreateBox(m_matFinal);
	return true;
}

void	JH_ColliderBox::SetTransform(D3DXMATRIX& Mat)
{
	m_matTransform = Mat;
	m_matFinal = DX::DecomposeMtrixMultiply(m_matWorld, m_matTransform);
	JH_Box::CreateBox(m_matFinal);
}
void	JH_ColliderBox::SetPos(D3DXVECTOR3 vPos)
{
	JH_Model::SetPos(vPos);
	m_matFinal =DX::DecomposeMtrixMultiply(m_matWorld, m_matTransform);
	JH_Box::CreateBox(m_matFinal);
}
void	JH_ColliderBox::SetScale(D3DXVECTOR3 vScale)
{
	JH_Model::SetScale(vScale);
	m_matFinal = DX::DecomposeMtrixMultiply(m_matWorld, m_matTransform);
	JH_Box::CreateBox(m_matFinal);
}
void	JH_ColliderBox::SetRotation(D3DXMATRIX Mat)
{
	JH_Model::SetRotation(Mat);
	m_matFinal = DX::DecomposeMtrixMultiply(m_matWorld, m_matTransform);
	JH_Box::CreateBox(m_matFinal);
}
void JH_ColliderBox::UpdateVB()
{
	DX::GetContext()->UpdateSubresource(m_pVertexBuffer.Get(), 0, 0, &m_VertexData.at(0), 0, 0);
}
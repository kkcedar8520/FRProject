#include "QuadTree.h"
#include"JH_Input.h"
bool HQuadTree::FindInterSection()
{
	D3DXVECTOR3 v0, v1, v2, vIntersection;
	m_fTimer += g_SecondPerFrame;
	if (G_Input.KeyCheck(VK_LBUTTON))//&& m_fTimer >=0.5)
	{

		m_fTimer = 0.0f;
		GetSelectNode(m_pRootNode);

		for (int iNode = 0; iNode <
			m_SelectNodeList.size(); iNode++)
		{
			DWORD dwFace = m_SelectNodeList[iNode]->m_IndexList.size() / 3;
			for (int iFace = 0; iFace < dwFace; iFace++)
			{
				DWORD i0 = m_SelectNodeList[iNode]->m_IndexList[iFace * 3 + 0];
				DWORD i1 = m_SelectNodeList[iNode]->m_IndexList[iFace * 3 + 1];
				DWORD i2 = m_SelectNodeList[iNode]->m_IndexList[iFace * 3 + 2];
				v0 = m_pMap->m_VertexData[i0].p;
				v1 = m_pMap->m_VertexData[i1].p;
				v2 = m_pMap->m_VertexData[i2].p;

				D3DXVECTOR3 vDIR = I_Select.m_Ray.vDirection;
				D3DXVECTOR3 vEnd = I_Select.m_Ray.vOrigin + vDIR * m_pCamera->m_fFar;

				D3DXVECTOR3 vNormal;
				D3DXVECTOR3 e0 = v1 - v0;
				D3DXVECTOR3 e1 = v2 - v0;
				D3DXVec3Cross(&vNormal, &e0, &e1);
				if (I_Select.InterSectionTriAngle(v0, v1, v2));
				{
					vIntersection = I_Select.m_vIntersection;
			

	

					if (m_pMap->m_bMapEdit)
					{
						SPHERE RangeSphere;
						RangeSphere.vCenter = vIntersection;
						RangeSphere.Radius = 10;
					}
				}
				/*	if (I_Select.GetIntersection(
						I_Select.m_Ray.vOrigin,
						vEnd,
						vNormal,
						v0, v1, v2))
					{
						if (I_Select.PointInPolygon(
							I_Select.m_vIntersection,
							vNormal,
							v0, v1, v2))
						{
							vIntersection = I_Select.m_vIntersection;
							TCHAR szBuffer[256] = { 0, };
							swprintf_s(szBuffer,
								L"전체[%02d],%10.4f:%10.4f:%10.4f:",
								m_QuadTree->m_SelectNodeList.size(),
								vIntersection.x,
								vIntersection.y,
								vIntersection.z);
							m_Write.Add(szBuffer);

						}
					}*/
			}
		}
	}
	return true;
}

void HQuadTree::Set()
{
	m_BoxLine= make_shared<JH_ShapeLine>();

	m_BoxLine->Create(m_pMap->m_dxHelper.m_pd3dDevice.Get(),
		m_pMap->m_dxHelper.m_pContext.Get(),
		L"../../data/shader/DefaultShader.txt", nullptr,
		"VSLine", "PSLine");
}
void HQuadTree::CreateBB(HNode* pNode)
{


	
	DWORD dwTL = pNode->m_dwCorner[0];
	DWORD dwTR = pNode->m_dwCorner[1];
	DWORD dwBL = pNode->m_dwCorner[2];
	DWORD dwBR = pNode->m_dwCorner[3];

	pNode->m_Box.vMin.x = m_pMap->m_VertexData[dwTL].p.x;
	pNode->m_Box.vMin.y = 999999999.0f;
	pNode->m_Box.vMin.z = m_pMap->m_VertexData[dwBL].p.z;
	pNode->m_Box.vMax.x = m_pMap->m_VertexData[dwTR].p.x;
	pNode->m_Box.vMax.y = -999999999.0f;
	pNode->m_Box.vMax.z = m_pMap->m_VertexData[dwTL].p.z;

	DWORD dwSize = (dwTR - dwTL)*(dwTR - dwTL) * 2 * 3;
	pNode->m_IndexList.resize(dwSize);

	DWORD dwStartRow = dwTL / m_pMap->m_iRowNum;
	DWORD dwEndRow = dwBL / m_pMap->m_iRowNum;;

	DWORD dwStartCol = dwTL % m_pMap->m_iRowNum;
	DWORD dwEndCol = dwTR % m_pMap->m_iRowNum;

	DWORD dwIndex = 0;
	for (DWORD dwRow = dwStartRow; dwRow < dwEndRow; dwRow++)
	{
		for (DWORD dwCol = dwStartCol; dwCol < dwEndCol; dwCol++)
		{
			dwIndex = dwRow * m_pMap->m_iRowNum + dwCol;
			if (pNode->m_Box.vMin.y > m_pMap->m_VertexData[dwIndex].p.y)
			{
				pNode->m_Box.vMin.y = m_pMap->m_VertexData[dwIndex].p.y;
			}
			if (pNode->m_Box.vMax.y < m_pMap->m_VertexData[dwIndex].p.y)
			{
				pNode->m_Box.vMax.y = m_pMap->m_VertexData[dwIndex].p.y;
			}
		}
	}

	pNode->m_Box.vCenter = (pNode->m_Box.vMax + pNode->m_Box.vMin) / 2;
	pNode->m_Box.vAxis[0] = D3DXVECTOR3(1, 0, 0);
	pNode->m_Box.vAxis[1] = D3DXVECTOR3(0, 1, 0);
	pNode->m_Box.vAxis[2] = D3DXVECTOR3(0, 0, 1);
	pNode->m_Box.fExtent[0] = pNode->m_Box.vMax.x - pNode->m_Box.vCenter.x;
	pNode->m_Box.fExtent[1] = pNode->m_Box.vMax.y - pNode->m_Box.vCenter.y;
	pNode->m_Box.fExtent[2] = pNode->m_Box.vMax.z - pNode->m_Box.vCenter.z;

	
}
HNode* HQuadTree::CreateNode(HNode* pParent, DWORD dwTL, DWORD dwTR, DWORD dwBL, DWORD dwBR)
{
	HNode* pNode = 0;
	SAFE_NEW(pNode, HNode);



	pNode->m_dwCorner[0] = dwTL;
	pNode->m_dwCorner[1] = dwTR;
	pNode->m_dwCorner[2] = dwBL;
	pNode->m_dwCorner[3] = dwBR;







	CreateBB(pNode);
	if (pParent != nullptr)
		pNode->m_dwDepth = pParent->m_dwDepth + 1;
	else
	{
		pNode->m_dwDepth = 0;
	}
	return pNode;
}

BOOL HQuadTree::Build(JH_Map* pMap, JHCamera* pCamera)
{
	m_pMap = pMap;
	m_pCamera = pCamera;
	Release();//전 데이터 삭제

	Set();
	DWORD dwTL = 0;
	DWORD dwTR = m_pMap->m_iColumNum-1;
	DWORD dwBL = m_pMap->m_iColumNum*(m_pMap->m_iRowNum - 1);
	DWORD dwBR = m_pMap->m_iColumNum*m_pMap->m_iRowNum - 1;
	m_pRootNode=CreateNode(nullptr, dwTL, dwTR, dwBL, dwBR);
	 
	BuildTree(m_pRootNode);


	return TRUE;
}
BOOL HQuadTree::BuildTree(HNode* pNode)
{
	if (DivideNode(pNode))
	{
		for (int iNode = 0; iNode < 4; iNode++)
		{
			BuildTree(pNode->m_pChild[iNode]);
		}
	}
	return TRUE;
}
BOOL HQuadTree::DivideNode(HNode*pNode)
{
	//dwTL		c0			dwTR
	

	

	//c1		c2			c3



	//dwBL		c4			dwBR
	if (pNode->m_dwDepth<3)
	{
		DWORD dwTL = pNode->m_dwCorner[0];
		DWORD dwTR = pNode->m_dwCorner[1];
		DWORD dwBL = pNode->m_dwCorner[2];
		DWORD dwBR = pNode->m_dwCorner[3];

		DWORD c0 = (dwTR + dwTL) / 2;
		DWORD c1 = (dwBL + dwTL) / 2;
		DWORD c2 = (dwBR + dwTL) / 2;
		DWORD c3 = (dwTR + dwBR) / 2;
		DWORD c4 = (dwBR + dwBL) / 2;

		pNode->m_pChild[0] = CreateNode(pNode, dwTL, c0, c1, c2);
		pNode->m_pChild[1] = CreateNode(pNode, c0, dwTR, c2, c3);
		pNode->m_pChild[2] = CreateNode(pNode, c1, c2, dwBL, c4);
		pNode->m_pChild[3] = CreateNode(pNode, c2, c3,c4, dwBR);
		
		return TRUE;
	}
	else
	{
		pNode->m_isLeaf = TRUE;
		CreateIndexList(pNode);
	}


	return FALSE;
	
}
void HQuadTree::DirectSelect(HNode* pNode)
{
	
}
void HQuadTree::DrawNodeLine(HNode* pNode)
{
	if (pNode == nullptr) { return ; }

	if (pNode->m_isLeaf == TRUE)
	{
		F_POSITION Pos = m_pCamera->CheckOBBInPlane(pNode->m_Box);
		if (Pos != BACK)
		{
			DrawLine(pNode);
		}

	}
	for (int iNode = 0; iNode < 4; iNode++)
	{
		
		DrawNodeLine(pNode->m_pChild[iNode]);
	}

}
void HQuadTree::DrawLine(HNode* pNode)
{
	m_BoxLine->SetMatrix(nullptr,
		&m_pCamera->m_matView,
		&m_pCamera->m_matProj);

	D3DXVECTOR3 vS;
	vS.x = pNode->m_Box.vMin.x;
	vS.y = pNode->m_Box.vMax.y;
	vS.z = pNode->m_Box.vMax.z;
	D3DXVECTOR3 vE;
	vE.x = pNode->m_Box.vMax.x;
	vE.y = pNode->m_Box.vMax.y;
	vE.z = pNode->m_Box.vMax.z;
	m_BoxLine->Draw(vE, vS, D3DXVECTOR4(1, 0, 0, 1));
	vS.x = pNode->m_Box.vMax.x;
	vS.y = pNode->m_Box.vMax.y;
	vS.z = pNode->m_Box.vMin.z;
	m_BoxLine->Draw(vE, vS, D3DXVECTOR4(1, 0, 0, 1));
	vE.x = pNode->m_Box.vMin.x;
	vE.y = pNode->m_Box.vMax.y;
	vE.z = pNode->m_Box.vMin.z;
	m_BoxLine->Draw(vS, vE, D3DXVECTOR4(1, 0, 0, 1));
	vS.x = pNode->m_Box.vMin.x;
	vS.y = pNode->m_Box.vMax.y;
	vS.z = pNode->m_Box.vMax.z;
	m_BoxLine->Draw(vS, vE, D3DXVECTOR4(1, 0, 0, 1));


	vS.x = pNode->m_Box.vMin.x;
	vS.y = pNode->m_Box.vMin.y;
	vS.z = pNode->m_Box.vMax.z;
	vE.x = pNode->m_Box.vMax.x;
	vE.y = pNode->m_Box.vMin.y;
	vE.z = pNode->m_Box.vMax.z;
	m_BoxLine->Draw(vE, vS, D3DXVECTOR4(1, 0, 0, 1));
	vS.x = pNode->m_Box.vMax.x;
	vS.y = pNode->m_Box.vMin.y;
	vS.z = pNode->m_Box.vMin.z;
	m_BoxLine->Draw(vE, vS, D3DXVECTOR4(1, 0, 0, 1));
	vE.x = pNode->m_Box.vMin.x;
	vE.y = pNode->m_Box.vMin.y;
	vE.z = pNode->m_Box.vMin.z;
	m_BoxLine->Draw(vS, vE, D3DXVECTOR4(1, 0, 0, 1));
	vS.x = pNode->m_Box.vMin.x;
	vS.y = pNode->m_Box.vMin.y;
	vS.z = pNode->m_Box.vMax.z;
	m_BoxLine->Draw(vS, vE, D3DXVECTOR4(1, 0, 0, 1));


	vS.x = pNode->m_Box.vMin.x;
	vS.y = pNode->m_Box.vMax.y;
	vS.z = pNode->m_Box.vMax.z;
	vE.x = pNode->m_Box.vMin.x;
	vE.y = pNode->m_Box.vMin.y;
	vE.z = pNode->m_Box.vMax.z;
	m_BoxLine->Draw(vE, vS, D3DXVECTOR4(1, 0, 0, 1));
	vS.x = pNode->m_Box.vMax.x;
	vS.y = pNode->m_Box.vMax.y;
	vS.z = pNode->m_Box.vMax.z;
	vE.x = pNode->m_Box.vMax.x;
	vE.y = pNode->m_Box.vMin.y;
	vE.z = pNode->m_Box.vMax.z;
	m_BoxLine->Draw(vE, vS, D3DXVECTOR4(1, 0, 0, 1));
	vS.x = pNode->m_Box.vMax.x;
	vS.y = pNode->m_Box.vMax.y;
	vS.z = pNode->m_Box.vMin.z;
	vE.x = pNode->m_Box.vMax.x;
	vE.y = pNode->m_Box.vMin.y;
	vE.z = pNode->m_Box.vMin.z;
	m_BoxLine->Draw(vS, vE, D3DXVECTOR4(1, 0, 0, 1));
	vS.x = pNode->m_Box.vMin.x;
	vS.y = pNode->m_Box.vMax.y;
	vS.z = pNode->m_Box.vMin.z;
	vE.x = pNode->m_Box.vMin.x;
	vE.y = pNode->m_Box.vMin.y;
	vE.z = pNode->m_Box.vMin.z;
	m_BoxLine->Draw(vS, vE, D3DXVECTOR4(1, 0, 0, 1));
}
void HQuadTree::GetSelectNode(HNode* pNode)
{
	if (pNode == nullptr) return;
	if (I_Select.AABBtoRay(&pNode->m_Box) == false) return;
	if (pNode->m_isLeaf)
	{
		m_SelectNodeList.push_back(pNode);
		return;
	}
	for (int iNode = 0; iNode < 4; iNode++)
	{
		GetSelectNode(pNode->m_pChild[iNode]);
	}
}
bool HQuadTree::Frame()
{
	m_SelectNodeList.clear();
	m_DrawNodeList.clear();
	DrawFindNode(m_pRootNode);
	return true;
}
bool HQuadTree::Render()
{
	m_pMap->PreRender();
	Draw(m_pRootNode, m_pMap->m_dxHelper.m_pContext.Get());
	return true;
}
bool HQuadTree::Draw(HNode* pNode, ID3D11DeviceContext* pContext)
{
	if (pNode == nullptr) { return false; }

	if (pNode->m_isLeaf==TRUE)
	{
		F_POSITION Pos = m_pCamera->CheckOBBInPlane(pNode->m_Box);
		if (Pos!=BACK)
		{
			pContext->IASetIndexBuffer(pNode->m_pIndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
			pContext->DrawIndexed(pNode->m_IndexList.size(), 0, 0);
		}
	
	}
	for (int iNode = 0; iNode < 4; iNode++)
	{
		Draw(pNode->m_pChild[iNode], pContext);
	}
}
void HQuadTree::CreateIndexList(HNode* pNode)
{
	DWORD dwTL = pNode->m_dwCorner[0];
	DWORD dwTR = pNode->m_dwCorner[1];
	DWORD dwBL = pNode->m_dwCorner[2];
	DWORD dwBR = pNode->m_dwCorner[3];

	DWORD dwSize = (dwTR - dwTL)*(dwTR - dwTL) * 2 * 3;

	pNode->m_IndexList.resize(dwSize);

	DWORD dwStartRow = dwTL / m_pMap->m_iRowNum;
	DWORD dwEndRow = dwBL / m_pMap->m_iRowNum;

	DWORD dwStartCol = dwTL % m_pMap->m_iRowNum;
	DWORD dwEndCol = dwTR % m_pMap->m_iRowNum;

	DWORD dwIndex = 0;
	for (int iRow = dwStartRow; iRow < dwEndRow; iRow++)
	{

		for (int iCol = dwStartCol; iCol < dwEndCol; iCol++)
		{
			pNode->m_IndexList[dwIndex++] = iRow * m_pMap->m_iColumNum + iCol;
			pNode->m_IndexList[dwIndex++] = iRow * m_pMap->m_iColumNum + iCol+1;
			pNode->m_IndexList[dwIndex++] = (iRow+1) * m_pMap->m_iColumNum+iCol;

			pNode->m_IndexList[dwIndex++] = (iRow + 1) * m_pMap->m_iColumNum + iCol;
			pNode->m_IndexList[dwIndex++] = iRow * m_pMap->m_iColumNum + iCol + 1;
			pNode->m_IndexList[dwIndex++] = (iRow + 1) * m_pMap->m_iColumNum + iCol+1;

		}
	}
	pNode->m_pIndexBuffer.Attach(DX::CreateIndexBuffer(
		m_pMap->m_dxHelper.m_pd3dDevice.Get(), 
		&pNode->m_IndexList.at(0),
		pNode->m_IndexList.size(), sizeof(DWORD)));



}
bool HQuadTree::Release()
{
	SAFE_DEL(m_pRootNode);

	return true;
}


void HQuadTree::DrawFindNode(HNode* pNode)
{
	if (pNode == nullptr) return;
	F_POSITION pos = m_pCamera->CheckOBBInPlane(pNode->m_Box);

	if (pNode->m_isLeaf == TRUE && pos != BACK)
	{
		m_DrawNodeList.push_back(pNode);
		if (pNode->m_ObjList.size() > 0)
		{
			m_DrawObjNodeList.push_back(pNode);
		}
		return;
	}
	if (pos == FRONT)
	{
		VisibleNode(pNode);
		return;
	}

	if (pNode->m_ObjList.size() > 0)
	{
		m_DrawObjNodeList.push_back(pNode);
	}

	for (int iNode = 0; iNode < 4; iNode++)
	{
		DrawFindNode(pNode->m_pChild[iNode]);
	}
}

void HQuadTree::VisibleNode(HNode* pNode)
{
	if (pNode == nullptr) return;
	if (pNode->m_isLeaf == TRUE)
	{
		m_DrawNodeList.push_back(pNode);
		if (pNode->m_ObjList.size() > 0)
		{
			m_DrawObjNodeList.push_back(pNode);
		}
		return;
	}
	if (pNode->m_ObjList.size() > 0)
	{
		m_DrawObjNodeList.push_back(pNode);
	}
	for (int iNode = 0; iNode < 4; iNode++)
	{
		VisibleNode(pNode->m_pChild[iNode]);
	}
}

HQuadTree::HQuadTree()
{
	float m_fTimer = 0.0f;
	m_pRootNode = nullptr;
}
HQuadTree::~HQuadTree()
{
	Release();
}

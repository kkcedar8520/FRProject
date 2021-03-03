#include "QuadTree.h"
#include"JH_Input.h"
#include"JH_PogMgr.h"
#include"JH_Map.h"

	//bool HQuadTree::FindInterSection()
	//{
	//	D3DXVECTOR3 v0, v1, v2, vIntersection;
	//	m_fTimer += g_SecondPerFrame;
	//	if (G_Input.KeyCheck(VK_LBUTTON))//&& m_fTimer >=0.5)
	//	{

	//		m_fTimer = 0.0f;
	//		GetSelectNode(m_pRootNode);

	//		for (int iNode = 0; iNode <
	//			m_SelectNodeList.size(); iNode++)
	//		{
	//			DWORD dwFace = m_SelectNodeList[iNode]->m_IndexList.size() / 3;
	//			for (int iFace = 0; iFace < dwFace; iFace++)
	//			{
	//				DWORD i0 = m_SelectNodeList[iNode]->m_IndexList[iFace * 3 + 0];
	//				DWORD i1 = m_SelectNodeList[iNode]->m_IndexList[iFace * 3 + 1];
	//				DWORD i2 = m_SelectNodeList[iNode]->m_IndexList[iFace * 3 + 2];
	//				v0 = m_pMap->m_VertexData[i0].p;
	//				v1 = m_pMap->m_VertexData[i1].p;
	//				v2 = m_pMap->m_VertexData[i2].p;

	//				D3DXVECTOR3 vDIR = I_Select.m_Ray.vDirection;
	//				D3DXVECTOR3 vEnd = I_Select.m_Ray.vOrigin + vDIR * m_pMap->m_pCamera->m_fFar;

	//				D3DXVECTOR3 vNormal;
	//				D3DXVECTOR3 e0 = v1 - v0;
	//				D3DXVECTOR3 e1 = v2 - v0;
	//				D3DXVec3Cross(&vNormal, &e0, &e1);
	//				float t = 0.0f;
	//				if (I_Select.PickCheck(&t, v0, v1, v2)); //CJH version
	//				{
	//					vIntersection = I_Select.GetIntersection(t);




	//					if (m_pMap->m_bMapEdit)
	//					{
	//						SPHERE RangeSphere;
	//						RangeSphere.vCenter = vIntersection;
	//						RangeSphere.Radius = 10;
	//					}
	//				}
	//				/*if (I_Select.GetIntersection(
	//					I_Select.m_Ray.m_Orig,
	//					vEnd,
	//					vNormal,
	//					v0, v1, v2))
	//				{
	//					if (I_Select.PointInPolygon(
	//						I_Select.m_vIntersection,
	//						vNormal,
	//						v0, v1, v2))
	//					{
	//						vIntersection = I_Select.m_vIntersection;
	//						TCHAR szBuffer[256] = { 0, };
	//						swprintf_s(szBuffer,
	//							L"전체[%02d],%10.4f:%10.4f:%10.4f:",
	//							m_QuadTree->m_SelectNodeList.size(),
	//							vIntersection.x,
	//							vIntersection.y,
	//							vIntersection.z);
	//						m_Write.Add(szBuffer);

	//					}
	//				}*/
	//			}
	//		}
	//	}
	//	return true;
	//}

	void HQuadTree::Set()
	{
		m_BoxLine = std::make_shared<JH_ShapeLine>();

		m_BoxLine->Create(m_pMap->m_dxHelper.GetDevice(),
			m_pMap->m_dxHelper.GetDeviceContext(),
			L"../../data/shader/LineShader.txt", nullptr,nullptr,"VS", "PS");
	}
	void HQuadTree::CreateBB(JH_Node* pNode)
	{



		DWORD dwTL = pNode->m_dwCorner[0];
		DWORD dwTR = pNode->m_dwCorner[1];
		DWORD dwBL = pNode->m_dwCorner[2];
		DWORD dwBR = pNode->m_dwCorner[3];

		pNode->m_Box.vMin.x = m_pMap->m_VertexData[dwTL].p.x;
		pNode->m_Box.vMin.y = 999999999.0f;						//젤 작은 x값을찾기위해
		pNode->m_Box.vMin.z = m_pMap->m_VertexData[dwBL].p.z;
		pNode->m_Box.vMax.x = m_pMap->m_VertexData[dwTR].p.x;
		pNode->m_Box.vMax.y = -999999999.0f;
		pNode->m_Box.vMax.z = m_pMap->m_VertexData[dwTL].p.z;

		//렉트의 높이와 넓이 *3 만큼으로 
		DWORD dwSize = (dwTR - dwTL)*(dwTR - dwTL) * 2 * 3;
		//pNode->m_IndexList.resize(dwSize);

		DWORD dwStartCol = dwTL / m_pMap->m_iRowNum;
		DWORD dwEndCol = dwBL / m_pMap->m_iRowNum;;

		DWORD dwStartRow = dwTL % m_pMap->m_iRowNum;
		DWORD dwEndRoW = dwTR % m_pMap->m_iRowNum;

		DWORD dwIndex = 0;


		//박스의 MinMax를 찾는과정 AABB 박스를 만들기위해
		if (pNode->m_ObjList.size() <= 0)
		{
			for (DWORD dwCol = dwStartCol; dwCol <= dwEndCol; dwCol++)
			{
				for (DWORD dwRow = dwStartRow; dwRow <= dwEndRoW; dwRow++)
				{
					dwIndex = dwCol * m_pMap->m_iRowNum + dwRow;
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
		}
		else
		{
			//오브젝트들이 있을땐 오브젝트 크기에맞춰 AABX 박스를 만들어줘야함
			//그렇지않으면 캐릭터를 찍어도 인식하지못함
			D3DXVECTOR3 vAxis[3];
			std::map<int, std::shared_ptr<JH_MapObj>>::iterator iter;
		/*	for (iter = pNode->m_ObjList.begin(); iter != pNode->m_ObjList.end(); iter++)
			{
				if (pNode->m_Box.vMin.y > iter->second->GetObj()->GetCharBox().vMin.y)
				{
					pNode->m_Box.vMin.y = iter->second->GetObj()->GetCharBox().vMin.y;
				}
				if (pNode->m_Box.vMax.y < iter->second->GetObj()->GetCharBox().vMax.y)
				{
					pNode->m_Box.vMax.y = iter->second->GetObj()->GetCharBox().vMax.y;
				}
			}*/
		}
		//AABB 세팅
		pNode->m_Box.vCenter = (pNode->m_Box.vMax + pNode->m_Box.vMin) / 2;
		pNode->m_Box.vAxis[0] = D3DXVECTOR3(1, 0, 0);
		pNode->m_Box.vAxis[1] = D3DXVECTOR3(0, 1, 0);
		pNode->m_Box.vAxis[2] = D3DXVECTOR3(0, 0, 1);
		D3DXVECTOR3 vHalf = pNode->m_Box.vMax - pNode->m_Box.vCenter;
		pNode->m_Box.fExtent[0] = pNode->m_Box.vMax.x - pNode->m_Box.vCenter.x;
		pNode->m_Box.fExtent[1] = pNode->m_Box.vMax.y - pNode->m_Box.vCenter.y;
		pNode->m_Box.fExtent[2] = pNode->m_Box.vMax.z - pNode->m_Box.vCenter.z;
		

		D3DXVECTOR3 BoxVertex[8];



		BoxVertex[0] = D3DXVECTOR3(pNode->m_Box.vMin.x, pNode->m_Box.vMin.y, pNode->m_Box.vMin.z);
		BoxVertex[1] = D3DXVECTOR3(pNode->m_Box.vMin.x, pNode->m_Box.vMax.y, pNode->m_Box.vMin.z);
		BoxVertex[2] = D3DXVECTOR3(pNode->m_Box.vMax.x, pNode->m_Box.vMax.y, pNode->m_Box.vMin.z);
		BoxVertex[3] = D3DXVECTOR3(pNode->m_Box.vMax.x, pNode->m_Box.vMin.y, pNode->m_Box.vMin.z);

		BoxVertex[4] = D3DXVECTOR3(pNode->m_Box.vMin.x, pNode->m_Box.vMin.y, pNode->m_Box.vMax.z);
		BoxVertex[5] = D3DXVECTOR3(pNode->m_Box.vMin.x, pNode->m_Box.vMax.y, pNode->m_Box.vMax.z);
		BoxVertex[6] = D3DXVECTOR3(pNode->m_Box.vMax.x, pNode->m_Box.vMax.y, pNode->m_Box.vMax.z);
		BoxVertex[7] = D3DXVECTOR3(pNode->m_Box.vMax.x, pNode->m_Box.vMin.y, pNode->m_Box.vMax.z);

		// 노말 방향 안쪽으로
		pNode->m_BoxPlane[0].CreatePlane(BoxVertex[5], BoxVertex[0], BoxVertex[1]);	// 좌 평면(left)
		pNode->m_BoxPlane[1].CreatePlane(BoxVertex[3], BoxVertex[6], BoxVertex[2]);	// 우 평면(right)
		pNode->m_BoxPlane[2].CreatePlane(BoxVertex[5], BoxVertex[2], BoxVertex[6]);	// 상 평면(top)
		pNode->m_BoxPlane[3].CreatePlane(BoxVertex[0], BoxVertex[7], BoxVertex[3]);	// 하 평면(bottom)
		pNode->m_BoxPlane[4].CreatePlane(BoxVertex[0], BoxVertex[2], BoxVertex[1]);	// 근 평면(near)
		pNode->m_BoxPlane[5].CreatePlane(BoxVertex[6], BoxVertex[4], BoxVertex[5]);	// 원 평면(far)
	}

	void HQuadTree::ChangeBB(JH_Node* pNode, JH_Box Box)
	{
		pNode->m_Box = Box;
	}
	JH_Node* HQuadTree::CreateNode(JH_Node* pParent, DWORD dwTL, DWORD dwTR, DWORD dwBL, DWORD dwBR)
	{
		JH_Node* pNode = 0;
		SAFE_NEW(pNode, JH_Node);


		//코너 지정
		pNode->m_dwCorner[0] = dwTL;
		pNode->m_dwCorner[1] = dwTR;
		pNode->m_dwCorner[2] = dwBL;
		pNode->m_dwCorner[3] = dwBR;





		pNode->m_iQuadTreeIndex = m_iQuadTreeIndex;

		//노드 바운딩 박스 생성
		CreateBB(pNode);

		//나누기연산의 몫과 나머지 둘다 추출하는함수 
		//LOD 작업에 필요
		ldiv_t divValue = ldiv(dwTL, m_dwWidth);
		pNode->m_dwPositionIndex[0] = divValue.rem / (dwTR - dwTL);//rem -> m_dwWidth를 dwTL로 나눈 나머지
		pNode->m_dwPositionIndex[1] = divValue.quot / (dwTR - dwTL);

		//아래로 내려갈때마다 깊이값추가
		if (pParent != nullptr)
			pNode->m_dwDepth = pParent->m_dwDepth + 1;
		else
		{
			pNode->m_dwDepth = 0;
		}
		m_NodeList.emplace(std::make_pair(m_iQuadTreeIndex, pNode));
		//m_NodeList.insert(std::make_pair(m_iQuadTreeIndex, pNode));
		m_iQuadTreeIndex++;

		
		return pNode;

	}

	BOOL HQuadTree::Build(JH_Map* pMap, JHCamera* pCamera)
	{
		if (pMap == nullptr)return FALSE;
		m_pMap = pMap;
		m_pMap->m_pCamera = pCamera;
		m_dwWidth = m_pMap->m_iRowNum;
		m_dwHeight = m_pMap->m_iColumNum;
		m_iNumFace = (m_dwWidth - 1)*(m_dwHeight - 1) * 2;
		Release();//전 데이터 삭제

		Set();
		DWORD dwTL = 0;
		DWORD dwTR = m_pMap->m_iRowNum - 1;
		DWORD dwBL = m_pMap->m_iColumNum*(m_pMap->m_iRowNum - 1);
		DWORD dwBR = m_pMap->m_iColumNum*m_pMap->m_iRowNum - 1;
		m_pRootNode = CreateNode(nullptr, dwTL, dwTR, dwBL, dwBR);

		InitLevelOrder(m_pRootNode, 3);//LOD데이터 생성
		BuildTree(m_pRootNode);
		SetNeighborNode(m_pRootNode);// 이웃노드 추가
		//이웃노드를 추가해야 검색이 빠름

		return TRUE;
	}
	//재귀함수 자식노드를 타고 내려가며 노드생성
	BOOL HQuadTree::BuildTree(JH_Node* pNode)
	{
		if (DivideNode(pNode))
		{
			for (int iNode = 0; iNode < 4; iNode++)
			{
				//LOD작업
				if (pNode->m_pChild[iNode])
				{
					DWORD dwIndex = pNode->m_pChild[iNode]->m_dwPositionIndex[1] * pow(2.0f, pNode->m_pChild[iNode]->m_dwDepth)
						+ pNode->m_pChild[iNode]->m_dwPositionIndex[0];

					DWORD dwValue = pNode->m_pChild[iNode]->m_dwDepth;
					m_LevelList[dwValue][dwIndex] = pNode->m_pChild[iNode];

				}
				BuildTree(pNode->m_pChild[iNode]);
			}
		}
		return TRUE;
	}
	BOOL HQuadTree::DivideNode(JH_Node*pNode)
	{
		//dwTL		c0			dwTR




		//c1		c2			c3
		//dwBL		c4			dwBR
		if (pNode->m_dwDepth < 3)
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
			pNode->m_pChild[3] = CreateNode(pNode, c2, c3, c4, dwBR);

			return TRUE;
		}
		else
		{
			pNode->m_isLeaf = TRUE;
			CreateIndexList(pNode);
		}


		return FALSE;

	}
	void HQuadTree::DirectSelect(JH_Node* pNode)
	{

	}
	void HQuadTree::DrawNodeLine(JH_Node* pNode)
	{
		if (pNode == nullptr) { return; }

		if (pNode->m_isLeaf == TRUE)
		{
			int Pos = m_pMap->m_pCamera->CheckOBBInPlane(pNode->m_Box);
			if (Pos != P_BACK)
			{
				DrawLine(pNode);
			}

		}
		for (int iNode = 0; iNode < 4; iNode++)
		{

			DrawNodeLine(pNode->m_pChild[iNode]);
		}

	}

	//속해있는 오브젝트 박스라인 그리기
	void HQuadTree::DrawObjectBoxLine()
	{
		m_BoxLine->SetMatrix(nullptr,
			&m_pMap->m_pCamera->m_matView,
			&m_pMap->m_pCamera->m_matProj);


		D3DXVECTOR3 vS;
		D3DXVECTOR3 vE;
		JH_Box Box;

		D3DXVECTOR3 vEAxisX, vEAxisY, vEAxisZ;

		for (auto Obj : m_DrawObjectList)
		{
		//	Box = Obj->GetObj()->GetCharBox();
			D3DXMATRIX matTransform=Obj->GetObj()->GetTransform();
			D3DXVECTOR3 TRANS = D3DXVECTOR3(matTransform._41, matTransform._42, matTransform._43);

			vEAxisX = (Box.vAxis[0] * Box.fExtent[0]);
			vEAxisY = (Box.vAxis[1] * Box.fExtent[1]);
			vEAxisZ = (Box.vAxis[2] * Box.fExtent[2]);


			vS = -vEAxisX + vEAxisY + vEAxisZ + TRANS;
			vE = vEAxisX + vEAxisY + vEAxisZ + TRANS;
			m_BoxLine->Draw(vE, vS, D3DXVECTOR4(0, 1, 0, 1));

			vS = vEAxisX + vEAxisY - vEAxisZ + TRANS;
			m_BoxLine->Draw(vE, vS, D3DXVECTOR4(0, 1, 0, 1));

			vE = -vEAxisX + vEAxisY - vEAxisZ + TRANS;
			m_BoxLine->Draw(vE, vS, D3DXVECTOR4(0, 1, 0, 1));

			vS = -vEAxisX + vEAxisY + vEAxisZ + TRANS;
			m_BoxLine->Draw(vE, vS, D3DXVECTOR4(0, 1, 0, 1));


			vS = -vEAxisX - vEAxisY + vEAxisZ + TRANS;
			vE = +vEAxisX - vEAxisY + vEAxisZ + TRANS;
			m_BoxLine->Draw(vE, vS, D3DXVECTOR4(0, 1, 0, 1));

			vS = vEAxisX - vEAxisY - vEAxisZ + TRANS;
			m_BoxLine->Draw(vE, vS, D3DXVECTOR4(0, 1, 0, 1));

			vE = -vEAxisX - vEAxisY - vEAxisZ + TRANS;
			m_BoxLine->Draw(vE, vS, D3DXVECTOR4(0, 1, 0, 1));

			vS = -vEAxisX - vEAxisY + vEAxisZ + TRANS;
			m_BoxLine->Draw(vE, vS, D3DXVECTOR4(0, 1, 0, 1));


			vS = -vEAxisX + vEAxisY + vEAxisZ + TRANS;
			vE = -vEAxisX - vEAxisY + vEAxisZ + TRANS;
			m_BoxLine->Draw(vE, vS, D3DXVECTOR4(0, 1, 0, 1));

			vS = -vEAxisX - vEAxisY - vEAxisZ + TRANS;
			m_BoxLine->Draw(vE, vS, D3DXVECTOR4(0, 1, 0, 1));

			vE = -vEAxisX + vEAxisY - vEAxisZ + TRANS;
			m_BoxLine->Draw(vE, vS, D3DXVECTOR4(0, 1, 0, 1));

			vS = -vEAxisX + vEAxisY + vEAxisZ + TRANS;
			m_BoxLine->Draw(vE, vS, D3DXVECTOR4(0, 1, 0, 1));


			vS = vEAxisX + vEAxisY + vEAxisZ + TRANS;
			vE = +vEAxisX - vEAxisY + vEAxisZ + TRANS;
			m_BoxLine->Draw(vE, vS, D3DXVECTOR4(0, 1, 0, 1));

			vS = +vEAxisX - vEAxisY - vEAxisZ + TRANS;
			m_BoxLine->Draw(vE, vS, D3DXVECTOR4(0, 1, 0, 1));

			vE = +vEAxisX + vEAxisY - vEAxisZ + TRANS;
			m_BoxLine->Draw(vE, vS, D3DXVECTOR4(0, 1, 0, 1));

			vS = +vEAxisX + vEAxisY + vEAxisZ + TRANS;
			m_BoxLine->Draw(vE, vS, D3DXVECTOR4(0, 1, 0, 1));

		}



	}
	void HQuadTree::DrawLine(JH_Node* pNode)
	{

		m_BoxLine->SetMatrix(nullptr,
			&m_pMap->m_pCamera->m_matView,
			&m_pMap->m_pCamera->m_matProj);

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
	void HQuadTree::FindSelectPoint()
	{
		JH_Node* pNode = nullptr;
		GetSelectNode(m_pRootNode);


		D3DXVECTOR3 v0, v1, v2;
		if (m_SelectNodeList.size() <= 0) return ;
		//노드들에서 평면 교점찾기
		for (int iNode = 0; iNode <
			m_SelectNodeList.size(); iNode++)
		{
			DWORD dwFace =m_SelectNodeList[iNode]->m_IndexList.size() / 3;
			for (int iFace = 0; iFace < dwFace; iFace++)
			{
				DWORD i0 = m_SelectNodeList[iNode]->m_IndexList[iFace * 3 + 0];
				DWORD i1 = m_SelectNodeList[iNode]->m_IndexList[iFace * 3 + 1];
				DWORD i2 = m_SelectNodeList[iNode]->m_IndexList[iFace * 3 + 2];
				v0 = m_pMap->m_VertexData[i0].p;
				v1 = m_pMap->m_VertexData[i1].p;
				v2 = m_pMap->m_VertexData[i2].p;

				D3DXVECTOR3 vDIR = I_Select.m_Ray.vDirection;
				D3DXVECTOR3 vEnd = I_Select.m_Ray.vOrigin + vDIR * m_pMap->m_pCamera->m_fFar;

				D3DXVECTOR3 vNormal;
				D3DXVECTOR3 e0 = v1 - v0;
				D3DXVECTOR3 e1 = v2 - v0;
				D3DXVec3Cross(&vNormal, &e0, &e1);

				if (I_Select.PickCheck(v0, v1, v2))
				{
					pNode =m_SelectNodeList[iNode];
					m_SelectNodeList.clear();

					m_SelectNodeList.emplace_back(pNode);
					break;
				}
			}
		}
	}

	void HQuadTree::GetSelectNode(JH_Node* pNode)
	{

		if (pNode == nullptr) return;

		if (I_Select.OBBToRay(&pNode->m_Box) == false) return;

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
	bool HQuadTree::GetCotainObjNode(JH_Node* pNode)
	{
		if (pNode == nullptr) return false;

		if (pNode->m_ObjList.size() > 0)
		{
			m_ContainObjNode.push_back(pNode);

		}
		for (int iNode = 0; iNode < 4; iNode++)
		{
			GetCotainObjNode(pNode->m_pChild[iNode]);
		}
		return true;
	}

	void HQuadTree::GetSelectObj(JH_Node* pNode)
	{
		if (pNode == nullptr) return;



		/*for (auto Obj : m_ObjectList)
		{
			JH_Box Box = Obj.second->GetObj()->GetCharBox();

			if (I_Select.OBBToRay(&Box))
			{
				float vInterLength = D3DXVec3Length(&(I_Select.m_vIntersection - m_pMap->m_pCamera->m_Pos));  ///잠시 주석처리
				if (m_fInterval > vInterLength)
				{
					m_fInterval = vInterLength;
					m_pSelectObj = Obj.second;

				}

			}
		}
*/
		m_fInterval = 9999999.0f;
		return;
	}

	bool HQuadTree::GetObjectAddNode(std::shared_ptr < JH_MapObj> Obj)
	{
		bool b = false;
		//if (!m_pRootNode) return false;
		//JH_Node* pNode = nullptr;

		//JH_Box Box = Obj->GetObj()->GetCharBox();
		//int pos = CheckOBBNodePlane(m_pRootNode, Box);
		//if (pos == P_FRONT)
		//{
		//	pNode = FindNode(m_pRootNode, Obj.get());
		//	if (pNode)
		//	{
		//		std::map<int, JH_MapObj*>::iterator iter;


		//		Obj->SetQuadIndex(pNode->m_iQuadTreeIndex);
		//		Obj->SetNode(pNode);
		//		pNode->m_ObjList.insert(make_pair(Obj->GetID(), Obj));
		//		m_ObjectList.insert(make_pair(Obj->GetID(), Obj));
		//		b = true;
		//		return b;
		//	}
		//}



		return b;

	}
	bool HQuadTree::ChangeObjectNode(std::shared_ptr<JH_MapObj> Obj)
	{
		bool b = false;
		//if (!m_pRootNode) return false;
		//JH_Node* pNode = nullptr;
		//Obj->GetObj()->SetMatrix(&Obj->GetObj()->m_matWorld, &m_pMap->m_pCamera->m_View, &m_pMap->m_pCamera->m_Proj);
		//JH_Box Box = Obj->GetObj()->GetCharBox();
		//int pos = CheckOBBNodePlane(m_pRootNode, Box);
		//if (pos == P_FRONT)
		//{
		//	pNode = FindNode(m_pRootNode, Obj.get());

		//	if (pNode)
		//	{
		//		JH_Node* beforeNode = (JH_Node*)Obj->GetNode();
		//		auto iter = beforeNode->m_ObjList.find(Obj->GetID());
		//		//assert(iter != beforeNode->m_ObjList.end());
		//		if (pNode->m_iQuadTreeIndex != beforeNode->m_ObjList[Obj->GetID()]->GetQuadIndex())
		//			beforeNode->m_ObjList.erase(Obj->GetID());

		//		Obj->SetNode(pNode);
		//		Obj->SetQuadIndex(pNode->m_iQuadTreeIndex);
		//		pNode->m_ObjList.insert(make_pair(Obj->GetID(), Obj));





		//		//CreateBB(pNode);
		//		b = true;
		//		return b;
		//	}

		//}



		return b;
	}
	JH_Node* HQuadTree::FindNode(JH_Node* pNode, JH_MapObj* Obj)
	{
		//std::queue<JH_Node*>   m_QueueList;
		//do {
		//	for (int iChild = 0; iChild < 4; iChild++)
		//	{
		//		if (pNode->m_pChild[iChild] == nullptr) break;
		//		JH_Box Box = Obj->GetObj()->GetCharBox();
		//		int pos = CheckOBBNodePlane(pNode->m_pChild[iChild], Box);
		//		if (pos == P_FRONT)
		//		{
		//			m_QueueList.push(pNode->m_pChild[iChild]);
		//		}
		//	}
		//	if (m_QueueList.empty()) break;
		//	pNode = m_QueueList.front();
		//	m_QueueList.pop();

		//} while (pNode);
		return pNode;
	}
	JH_Node* HQuadTree::FindIDNode(JH_Node* pNode, JH_MapObj* Obj)
	{
		if (pNode == nullptr) return false;
		if (m_pFindNode != nullptr)return nullptr;
		std::map<int, std::shared_ptr<JH_MapObj>>::iterator iter;
		iter = pNode->m_ObjList.find(Obj->GetID());
		if ((pNode->m_iQuadTreeIndex == Obj->GetQuadIndex() && iter != pNode->m_ObjList.end()))
		{
			m_pFindNode = pNode;
			return pNode;

		}
		for (int iNode = 0; iNode < 4; iNode++)
		{
			FindIDNode(pNode->m_pChild[iNode], Obj);
		}
		return nullptr;
	}
	int	HQuadTree::CheckOBBNodePlane(JH_Node* pNode, JH_Box& box)
	{
		D3DXVECTOR3 vDir;
		float  fDistance = 0.0f;
		float  fPlaneToCenterDistance = 0.0f;
		int t_Pos = P_FRONT;

		for (int iPlane = 0; iPlane < 4; iPlane++)
		{
			vDir = box.vAxis[0] * box.fExtent[0];
			fDistance = fabs(pNode->m_BoxPlane[iPlane].fA *
				vDir.x +
				pNode->m_BoxPlane[iPlane].fB *
				vDir.y +
				pNode->m_BoxPlane[iPlane].fC *
				vDir.z);

			vDir = box.vAxis[1] * box.fExtent[1];
			fDistance += fabs(pNode->m_BoxPlane[iPlane].fA *
				vDir.x +
				pNode->m_BoxPlane[iPlane].fB *
				vDir.y +
				pNode->m_BoxPlane[iPlane].fC *
				vDir.z);

			vDir = box.vAxis[2] * box.fExtent[2];
			fDistance += fabs(pNode->m_BoxPlane[iPlane].fA *
				vDir.x +
				pNode->m_BoxPlane[iPlane].fB *
				vDir.y +
				pNode->m_BoxPlane[iPlane].fC *
				vDir.z);

			fPlaneToCenterDistance =
				pNode->m_BoxPlane[iPlane].fA *
				box.vCenter.x +
				pNode->m_BoxPlane[iPlane].fB *
				box.vCenter.y +
				pNode->m_BoxPlane[iPlane].fC *
				box.vCenter.z +
				pNode->m_BoxPlane[iPlane].fD;

			if (fPlaneToCenterDistance <= fDistance)
			{
				t_Pos = P_SPANNING;
			}

			if (fPlaneToCenterDistance < -fDistance)
			{
				return  P_BACK;
			}
		}
		return t_Pos;
	}

	void  HQuadTree::FindObjectNode(JH_Node* pNode, std::shared_ptr<JH_MapObj> Obj)
	{
		if (pNode == nullptr) return;
		if (m_bFind) { return; }

		if (pNode->m_iQuadTreeIndex == Obj->GetQuadIndex())
		{
			m_pFindNode = pNode;
			m_bFind = true;
			return;
		}
		for (int iNode = 0; iNode < 4; iNode++)
		{
			FindObjectNode(pNode->m_pChild[iNode], Obj);

		}

		m_bFind = false;
	}

	void HQuadTree::FindNearInterSectionNode(JH_Node* pNode, D3DXVECTOR3 vInterSection)
	{

		float distance = D3DXVec3Length(&(vInterSection - m_pMap->m_pCamera->m_vPos));

		if (m_fdistance > distance)
		{
			m_fdistance = distance;
			m_pNearPointNode = pNode;
		}
	}
	void HQuadTree::SetNeighborNode(JH_Node* pNode)
	{
		if (pNode == nullptr) return;
		FindNeighborNode(pNode);
		for (int iNode = 0; iNode < 4; iNode++)
		{
			SetNeighborNode(pNode->m_pChild[iNode]);
		}
	}
	void HQuadTree::FindNeighborNode(JH_Node* pNode)
	{
		pNode->m_NeighborNodeList.resize(8);

		DWORD dwNumPatchCount = (DWORD)pow(2.0f, (float)pNode->m_dwDepth);

		DWORD dwNeighborCol, dwNeighborRow;
		if (pNode->m_dwPositionIndex[1] > 0 && pNode->m_dwPositionIndex[0] > 0)  // 북서
		{
			dwNeighborCol = pNode->m_dwPositionIndex[0];
			dwNeighborRow = (pNode->m_dwPositionIndex[1] - 1) * dwNumPatchCount;
			pNode->m_NeighborNodeList[0] = m_LevelList[pNode->m_dwDepth][dwNeighborRow + dwNeighborCol];

		}
		if (pNode->m_dwPositionIndex[1] > 0)  // 상
		{
			dwNeighborCol = pNode->m_dwPositionIndex[0];
			dwNeighborRow = (pNode->m_dwPositionIndex[1] - 1) * dwNumPatchCount;
			pNode->m_NeighborNodeList[1] = m_LevelList[pNode->m_dwDepth][dwNeighborRow + dwNeighborCol];
		}
		if (pNode->m_dwPositionIndex[1] > 0 && pNode->m_dwPositionIndex[0] < dwNumPatchCount - 1)  // 북동
		{
			dwNeighborCol = pNode->m_dwPositionIndex[0];
			dwNeighborRow = (pNode->m_dwPositionIndex[1] - 1) * dwNumPatchCount;
			pNode->m_NeighborNodeList[2] = m_LevelList[pNode->m_dwDepth][dwNeighborRow + dwNeighborCol];
		}


		if (pNode->m_dwPositionIndex[0] > 0) // 좌
		{
			dwNeighborCol = pNode->m_dwPositionIndex[0] - 1;
			dwNeighborRow = pNode->m_dwPositionIndex[1] * dwNumPatchCount;
			pNode->m_NeighborNodeList[3] = m_LevelList[pNode->m_dwDepth][dwNeighborRow + dwNeighborCol];
		}
		if (pNode->m_dwPositionIndex[0] < dwNumPatchCount - 1) // 우
		{
			dwNeighborCol = pNode->m_dwPositionIndex[0] + 1;
			dwNeighborRow = pNode->m_dwPositionIndex[1] * dwNumPatchCount;
			pNode->m_NeighborNodeList[4] = m_LevelList[pNode->m_dwDepth][dwNeighborRow + dwNeighborCol];
		}

		if (pNode->m_dwPositionIndex[1] < dwNumPatchCount - 1 && pNode->m_dwPositionIndex[0] > 0) // 남서
		{
			dwNeighborCol = pNode->m_dwPositionIndex[0];
			dwNeighborRow = (pNode->m_dwPositionIndex[1] + 1) * dwNumPatchCount;
			pNode->m_NeighborNodeList[5] = m_LevelList[pNode->m_dwDepth][dwNeighborRow + dwNeighborCol];
		}
		if (pNode->m_dwPositionIndex[1] < dwNumPatchCount - 1) // 하
		{
			dwNeighborCol = pNode->m_dwPositionIndex[0];
			dwNeighborRow = (pNode->m_dwPositionIndex[1] + 1) * dwNumPatchCount;
			pNode->m_NeighborNodeList[6] = m_LevelList[pNode->m_dwDepth][dwNeighborRow + dwNeighborCol];
		}
		if (pNode->m_dwPositionIndex[1] < dwNumPatchCount - 1 & pNode->m_dwPositionIndex[0] < dwNumPatchCount - 1) // 남동
		{
			dwNeighborCol = pNode->m_dwPositionIndex[0];
			dwNeighborRow = (pNode->m_dwPositionIndex[1] + 1) * dwNumPatchCount;
			pNode->m_NeighborNodeList[7] = m_LevelList[pNode->m_dwDepth][dwNeighborRow + dwNeighborCol];
		}

	}

	bool HQuadTree::Frame()
	{
		m_SelectNodeList.clear();
		m_DrawObjNodeList.clear();
		m_DrawNodeList.clear();
		m_DrawObjectList.clear();
		FindDrawNode(m_pRootNode);




		return true;
	}
	bool HQuadTree::Render()
	{



		ID3D11ShaderResourceView* SRVLIST[10] = { nullptr };

		int iSPTNum = m_pMap->m_vSplattTextureList.size();//스플래팅 텍스쳐 개수


		for (int i = 0; i < m_pMap->m_vSplattTextureList.size(); i++)
		{

			if (i >= 8)
			{
				iSPTNum = 8; //100 개이상 넘어가면 더이상 추가하지않음 
				break;
			}
			SRVLIST[i] = m_pMap->m_vSplattTextureList[i]->m_pTextureRV;

		}

		if (iSPTNum > 0)
		{
			m_pMap->m_dxHelper.GetDeviceContext()->PSSetShaderResources(3,
				iSPTNum, SRVLIST);
			m_pMap->m_CBSubData.MapSubData.x = iSPTNum;
			m_pMap->m_dxHelper.GetDeviceContext()->UpdateSubresource(m_pMap->m_CBSub.Get(), 0, 0, &m_pMap->m_CBSubData, 0, 0);
		}


		DX::GetContext()->PSSetShaderResources(2, 1, m_pMap->m_pCopySrv.GetAddressOf());

		for (int iNode = 0; iNode < m_DrawNodeList.size(); iNode++)
		{
			JH_Node* pNode = m_DrawNodeList[iNode];
			DX::GetContext()->IASetIndexBuffer(pNode->m_pIndexBuffer.Get(), DXGI_FORMAT_R32_UINT,0);
			DX::GetContext()->DrawIndexed(pNode->m_IndexList.size(), 0, 0);
		}
		return true;
	}
	bool HQuadTree::Draw(JH_Node* pNode, ID3D11DeviceContext* pContext)
	{
		if (pNode == nullptr) { return false; }

		if (pNode->m_isLeaf == TRUE)
		{
			int Pos = m_pMap->m_pCamera->CheckOBBInPlane(pNode->m_Box);
			if (Pos != P_BACK)
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
	void HQuadTree::CreateIndexList(JH_Node* pNode)
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
				pNode->m_IndexList[dwIndex++] = iRow * m_pMap->m_iColumNum + iCol + 1;
				pNode->m_IndexList[dwIndex++] = (iRow + 1) * m_pMap->m_iColumNum + iCol;

				pNode->m_IndexList[dwIndex++] = (iRow + 1) * m_pMap->m_iColumNum + iCol;
				pNode->m_IndexList[dwIndex++] = iRow * m_pMap->m_iColumNum + iCol + 1;
				pNode->m_IndexList[dwIndex++] = (iRow + 1) * m_pMap->m_iColumNum + iCol + 1;

			}
		}
		pNode->m_pIndexBuffer.Attach(DX::CreateIndexBuffer(
			m_pMap->m_dxHelper.GetDevice(),
			&pNode->m_IndexList.at(0),
			pNode->m_IndexList.size(), sizeof(DWORD)));



	}
	bool HQuadTree::Release()
	{
		SAFE_DEL(m_pRootNode);
		
		return true;
	}


	void HQuadTree::FindDrawNode(JH_Node* pNode)
	{
		if (pNode == nullptr) return;
		P_POSITION pos = m_pMap->m_pCamera->CheckOBBInPlane(pNode->m_Box);
		for (auto obj : pNode->m_ObjList)
		{
		/*	JH_Box Box = obj.second->GetObj()->GetCharBox();
			int Objpos = m_pMap->m_pCamera->CheckOBBInPlane(Box);

			if (Objpos != P_BACK || pos != P_BACK)
			{
				m_DrawObjectList.push_back(obj.second);
			}*/
		}

		//if (pNode->m_isLeaf == TRUE && pos != P_BACK)
		//{
		//	m_DrawNodeList.push_back(pNode);
		//	return;
		//}

	
		// 리프노드 일 경우는 완전히 제외되지 않았다면(걸쳐 있거나 완전 포함)추가한다.
		if (pNode->m_isLeaf &&  pos != P_BACK)
		{
			m_DrawNodeList.push_back(pNode);
			//VisibleObject(pNode);
			return;
		}
		// 완전히 포함되어 있으면 자식을 탐색하지 않고 노드를 추가한다.
		if (pos == P_FRONT)
		{
			m_DrawNodeList.push_back(pNode);
			VisibleNode(pNode);
			return;
		}

		 //걸쳐져 있는 노드에 포함된 오브젝트 체크
	/*	if (t_Pos == P_SPANNING)
		{
			VisibleObject(pNode);
		}*/
		for (int iNode = 0; iNode < 4; iNode++)
		{
			FindDrawNode(pNode->m_pChild[iNode]);
		}
	}

	void HQuadTree::VisibleNode(JH_Node* pNode)
	{
		if (pNode == nullptr) return;
		if (pNode->m_isLeaf == TRUE)
		{
			m_DrawNodeList.push_back(pNode);

			return;
		}
		for (int iNode = 0; iNode < 4; iNode++)
		{
			VisibleNode(pNode->m_pChild[iNode]);
		}
	}


	HQuadTree::HQuadTree()
	{
		m_bFind = false;
		float m_fTimer = 0.0f;
		m_fdistance = 100000.0f;
		m_pRootNode = nullptr;
		m_pNearPointNode = nullptr;
		m_iQuadTreeIndex = 0;
		m_fInterval = 99999999.0;
	}
	HQuadTree::~HQuadTree()
	{
		Release();
	}

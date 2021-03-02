#include"ToolCore.h"

//bool ToolCore::MapUpDown()
//{
//	HQuadTree* pQuadTree=I_MapMgr.GetCurrentQuadTree().get();
//	JH_Node* pNode = nullptr;
//	JH_Map*  pMap = nullptr;
//	//일차로 쿼드트리 OBB 박스로 최적화
//	pQuadTree->GetSelectNode(pQuadTree->m_pRootNode);
//	
//	pMap = pQuadTree->m_pMap;
//	D3DXVECTOR3 v0, v1, v2;
//
//	//노드들에서 평면 교점찾기
//	for (int iNode = 0; iNode <
//		pQuadTree->m_SelectNodeList.size(); iNode++)
//	{
//		DWORD dwFace = pQuadTree->m_SelectNodeList[iNode]->m_IndexList.size() / 3;
//		for (int iFace = 0; iFace < dwFace; iFace++)
//		{
//			DWORD i0 = pQuadTree->m_SelectNodeList[iNode]->m_IndexList[iFace * 3 + 0];
//			DWORD i1 = pQuadTree->m_SelectNodeList[iNode]->m_IndexList[iFace * 3 + 1];
//			DWORD i2 = pQuadTree->m_SelectNodeList[iNode]->m_IndexList[iFace * 3 + 2];
//			v0 = pQuadTree->m_pMap->m_VertexData[i0].p;
//			v1 = pQuadTree->m_pMap->m_VertexData[i1].p;
//			v2 = pQuadTree->m_pMap->m_VertexData[i2].p;
//
//			D3DXVECTOR3 vDIR = I_Select.m_Ray.vDirection;
//			D3DXVECTOR3 vEnd = I_Select.m_Ray.vOrigin + vDIR * m_pMainCamera->m_fFar;
//
//			D3DXVECTOR3 vNormal;
//			D3DXVECTOR3 e0 = v1 - v0;
//			D3DXVECTOR3 e1 = v2 - v0;
//			D3DXVec3Cross(&vNormal, &e0, &e1);
//
//			if (I_Select.InterSectionTriAngle(v0, v1, v2))
//			{
//				pNode = pQuadTree->m_SelectNodeList[iNode]; 
//				pQuadTree->m_SelectNodeList.clear();
//				break;
//			}
//		}
//	}
//
//
//		D3DXVECTOR3 vCenter =I_Select.m_vIntersection;
//
//		m_Sphere.vCenter = I_Select.m_vIntersection;
//	
//
//		//원의 반지름 거리에 있는 정점만 올림 
//		float fDistance;
//		DWORD dwFace = pNode->m_IndexList.size() / 3;
//		
//			for (int iFace = 0; iFace < dwFace; iFace++)
//			{
//				for (int iV = 0; iV < 3; iV++)
//				{
//					DWORD i0 = pNode->m_IndexList[iFace * 3 + iV];
//
//					
//					fDistance = sqrt((pQuadTree->m_pMap->m_VertexData[i0].p.x - m_Sphere.vCenter.x)*
//						(pQuadTree->m_pMap->m_VertexData[i0].p.x - m_Sphere.vCenter.x) +
//						(pQuadTree->m_pMap->m_VertexData[i0].p.z - m_Sphere.vCenter.z)*
//						(pQuadTree->m_pMap->m_VertexData[i0].p.z - m_Sphere.vCenter.z));
//
//					//코사인함수를 이용하여 원형으로 올림
//					float  fDet = (fDistance / m_Sphere.Radius)*D3DX_PI / 2.0;
//
//					float value = cos(fDet)*g_fProgramTime;
//					if (m_Sphere.Radius > fDistance)
//					{
//						pQuadTree->m_pMap->MapUpDown(i0, value);
//						
//
//						//NorMalUpdate
//						DWORD i0 = pNode->m_IndexList[iFace * 3 + 0];
//						DWORD i1 = pNode->m_IndexList[iFace * 3 + 1];
//						DWORD i2 = pNode->m_IndexList[iFace * 3 + 2];
//
//						D3DXVECTOR3 vFaceNormal, E0, E1;
//						E0 = pQuadTree->m_pMap->m_VertexData[i1].p - pQuadTree->m_pMap->m_VertexData[i0].p;
//						E1 = pQuadTree->m_pMap->m_VertexData[i2].p - pQuadTree->m_pMap->m_VertexData[i0].p;
//
//						D3DXVec3Cross(&vFaceNormal, &E0, &E1);
//						D3DXVec3Normalize(&vFaceNormal, &vFaceNormal);
//
//						pQuadTree->m_pMap->m_VertexData[i0].n = vFaceNormal;
//						pQuadTree->m_pMap->m_VertexData[i1].n = vFaceNormal;
//						pQuadTree->m_pMap->m_VertexData[i2].n = vFaceNormal;
//					}
//
//
//				}
//
//			}
//			DX::GetContext()->UpdateSubresource(pQuadTree->m_pMap->m_dxHelper.GetVertexBuffer(), 0, 0, &pMap->m_VertexData.at(0), 0, 0);
//
//			return true;
//}

#include"pch.h"
#include "pch.h"
#include "ToolCore.h"
bool ToolCore::MapUpDown()
{
	HQuadTree* pQuadTree = I_MapMgr.GetCurrentQuadTree().get();
	JH_Node* pNode = nullptr;
	JH_Map*  pMap = nullptr;
	//일차로 쿼드트리 OBB 박스로 최적화
	pQuadTree->GetSelectNode(pQuadTree->m_pRootNode);

	pMap = pQuadTree->m_pMap;
	D3DXVECTOR3 v0, v1, v2;
	if (pQuadTree->m_SelectNodeList.size() <= 0) return false;
	//노드들에서 평면 교점찾기
	for (int iNode = 0; iNode <
		pQuadTree->m_SelectNodeList.size(); iNode++)
	{
		DWORD dwFace = pQuadTree->m_SelectNodeList[iNode]->m_IndexList.size() / 3;
		for (int iFace = 0; iFace < dwFace; iFace++)
		{
			DWORD i0 = pQuadTree->m_SelectNodeList[iNode]->m_IndexList[iFace * 3 + 0];
			DWORD i1 = pQuadTree->m_SelectNodeList[iNode]->m_IndexList[iFace * 3 + 1];
			DWORD i2 = pQuadTree->m_SelectNodeList[iNode]->m_IndexList[iFace * 3 + 2];
			v0 = pQuadTree->m_pMap->m_VertexData[i0].p;
			v1 = pQuadTree->m_pMap->m_VertexData[i1].p;
			v2 = pQuadTree->m_pMap->m_VertexData[i2].p;

			D3DXVECTOR3 vDIR = I_Select.m_Ray.vDirection;
			D3DXVECTOR3 vEnd = I_Select.m_Ray.vOrigin + vDIR * m_pMainCamera->m_fFar;

			D3DXVECTOR3 vNormal;
			D3DXVECTOR3 e0 = v1 - v0;
			D3DXVECTOR3 e1 = v2 - v0;
			D3DXVec3Cross(&vNormal, &e0, &e1);

			if (I_Select.PickCheck(v0, v1, v2))
			{
				pNode = pQuadTree->m_SelectNodeList[iNode];
				pQuadTree->m_SelectNodeList.clear();
				break;
			}
		}
	}


	D3DXVECTOR3 vCenter = I_Select.m_vIntersection;

	m_Sphere.vCenter = I_Select.m_vIntersection;


	//원의 반지름 거리에 있는 정점만 올림 
	float fDistance;

	if (pNode == nullptr)return false;
	DWORD dwFace = pNode->m_IndexList.size() / 3;

	for (int iFace = 0; iFace < dwFace; iFace++)
	{
		for (int iV = 0; iV < 3; iV++)
		{
			DWORD i0 = pNode->m_IndexList[iFace * 3 + iV];


			fDistance = D3DXVec3Length(&D3DXVECTOR3(m_Sphere.vCenter - pQuadTree->m_pMap->m_VertexData[i0].p));

			//코사인함수를 이용하여 원형으로 올림
			float  fDet = (fDistance / m_Sphere.Radius)*D3DX_PI / 2.0;

			float value = cos(fDet)*g_SecondPerFrame;
			if (m_Sphere.Radius > fDistance)
			{
				pQuadTree->m_pMap->MapUpDown(i0, value);


				//NorMalUpdate
				DWORD i0 = pNode->m_IndexList[iFace * 3 + 0];
				DWORD i1 = pNode->m_IndexList[iFace * 3 + 1];
				DWORD i2 = pNode->m_IndexList[iFace * 3 + 2];

				D3DXVECTOR3 vFaceNormal, E0, E1;
				E0 = pQuadTree->m_pMap->m_VertexData[i1].p - pQuadTree->m_pMap->m_VertexData[i0].p;
				E1 = pQuadTree->m_pMap->m_VertexData[i2].p - pQuadTree->m_pMap->m_VertexData[i0].p;

				D3DXVec3Cross(&vFaceNormal, &E0, &E1);
				D3DXVec3Normalize(&vFaceNormal, &vFaceNormal);

				pQuadTree->m_pMap->m_VertexData[i0].n = vFaceNormal;
				pQuadTree->m_pMap->m_VertexData[i1].n = vFaceNormal;
				pQuadTree->m_pMap->m_VertexData[i2].n = vFaceNormal;
			}


		}

	}
	DX::GetContext()->UpdateSubresource(pQuadTree->m_pMap->m_dxHelper.GetVertexBuffer(), 0, 0, &pMap->m_VertexData.at(0), 0, 0);

	return true;
}

bool ToolCore::Init()
{


	m_pMainCamera->CreateViewMatrix(D3DXVECTOR3(0, 0, -50.0f), D3DXVECTOR3(0, 0, 0));
	m_pMainCamera->UpdateBasisVector();


	float fAspect = (float)g_rtClient.right / g_rtClient.bottom;
	m_pMainCamera->CreateProjMatrix(1.0F, 10000.0F, D3DX_PI*0.5, fAspect);

	m_DebugLine.Create(DX::GetDevice().Get(), DX::GetContext().Get(), L"../../data/shader/LineShader.txt", nullptr);
	I_LIGHT_MGR.Create(L"../../data/shader/LightShader.txt",L"../../data/LightSrc/LightInfo.txt");
	return true;
}
bool ToolCore::Frame()
{

	I_LIGHT_MGR.Frame();
	I_LIGHT_MGR.m_cbLight.vEyeDir[0] = { m_pMainCamera->m_vLookup,30 };
	I_LIGHT_MGR.m_cbLight.vEyePos[0] = { m_pMainCamera->m_vPos,30 };

	I_MapMgr.Frame();

	m_DebugLine.SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);

	switch (m_eState)
	{
	case TOOLSTATE::HEIGHT:
	{
		if(G_Input.KeyCheck(VK_LBUTTON))
		MapUpDown();
	}
	default:
		break;
	}
	return true;
}
bool ToolCore::Render()
{
	I_MapMgr.Render();
	m_DebugLine.Draw(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(100, 0, 0), D3DXVECTOR4(1, 0, 0, 1));
	m_DebugLine.Draw(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 100, 0), D3DXVECTOR4(0, 1, 0, 1));
	m_DebugLine.Draw(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 100), D3DXVECTOR4(0, 0, 1, 1));
	return true;
}
bool ToolCore::Release()
{
	return true;
}



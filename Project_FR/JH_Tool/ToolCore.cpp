#include "pch.h"
#include "ToolCore.h"
void ToolCore::FlattingMap()
{
	HQuadTree* pQuadTree = I_MapMgr.GetCurrentQuadTree().get();
	JH_Node* pNode = nullptr;
	JH_Map*  pMap = nullptr;


	pQuadTree->FindSelectPoint();


	m_Sphere.vCenter = I_Select.m_vIntersection;

	if (pQuadTree->m_SelectNodeList.size() <= 0)return ;
	pNode = pQuadTree->m_SelectNodeList[0];
	//원의 반지름 거리에 있는 정점만 올림 
	float fDistance;

	if (pNode == nullptr)return ;
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
				pQuadTree->m_pMap->FlattingMap(i0);


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
	DX::GetContext()->UpdateSubresource(pQuadTree->m_pMap->GetVertexBuffer(), 0, 0, &pQuadTree->m_pMap->m_VertexData.at(0), 0, 0);

	return ;
}
bool ToolCore::UpDownMap()
{
	HQuadTree* pQuadTree = I_MapMgr.GetCurrentQuadTree().get();
	JH_Node* pNode = nullptr;
	JH_Map*  pMap = nullptr;


	pQuadTree->FindSelectPoint();


	m_Sphere.vCenter = I_Select.m_vIntersection;

	if (pQuadTree->m_SelectNodeList.size() <= 0)return false;
	pNode = pQuadTree->m_SelectNodeList[0];
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
				pQuadTree->m_pMap->UpDownMap(i0, value);


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
	DX::GetContext()->UpdateSubresource(pQuadTree->m_pMap->GetVertexBuffer(), 0, 0, &pQuadTree->m_pMap->m_VertexData.at(0), 0, 0);

	return true;
}
bool ToolCore::SplattingMap()
{

	if (!I_MapMgr.GetCurrentQuadTree()->FindSelectPoint()) { return false; }
	m_Sphere.vCenter = I_Select.m_vIntersection;


	//월드좌표를 텍스쳐 좌표 uv 값으로 변경
	m_CSBuf.vPickPos = D3DXVECTOR3(m_Sphere.vCenter.x + ((m_CSBuf.iRow) / 2.0f),
		0, -(m_Sphere.vCenter.z) + ((m_CSBuf.iCol) / 2.0f));
	//구조체버퍼 갱신
	DX::GetContext()->UpdateSubresource((ID3D11Resource*)m_CS.m_pStructureBF.Get(), NULL, nullptr, &m_CSBuf, NULL, NULL);
	// ComputeShaderExcute 스레드그룹을 나눈숫자 만큼 나눈다
	m_CS.RunComputeShaderSplatting(m_CSBuf.iRow / 16, m_CSBuf.iCol / 16, 1);
	
	return true;
}
void ToolCore::CollocateObject()
{
	int IObj;

	//노드 교점찾기

	if (!I_MapMgr.GetCurrentQuadTree()->FindSelectPoint()) { return; }
	m_Sphere.vCenter = I_Select.m_vIntersection;

	IObj = I_ObjMgr.CreateObject(m_ObjFileName);
	 if(IObj==-1) { return ; }
	 JH_Obj* pObj=I_ObjMgr.GetPtr(IObj);
	 pObj->SetPos(m_Sphere.vCenter);
	 pObj->GetColliderBox().SetPos(D3DXVECTOR3(0, 5, 0));
	 pObj->GetColliderBox().SetScale(D3DXVECTOR3(5, 5, 5));




	I_ObjMgr.SetCamera(IObj,m_pMainCamera.get());
	//노드에 저장실패시 오브젝트 삭제
	if (!I_MapMgr.GetCurrentQuadTree()->ObjectAddNode(pObj))
		I_ObjMgr.DeleteObject(IObj);
}
void ToolCore::SelectObject()
{
	if (!I_MapMgr.GetCurrentQuadTree()->FindSelectPoint()) { return; }
	m_Sphere.vCenter = I_Select.m_vIntersection;
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
	I_ObjMgr.Frame();

	m_DebugLine.SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);

	switch (m_eState)
	{
		case TOOLSTATE::HEIGHT:
		{
			if(G_Input.KeyCheck(VK_LBUTTON))
			UpDownMap();
			break;
		}
		case TOOLSTATE::SPLATTING:
		{
			if (G_Input.KeyCheck(VK_LBUTTON))
			SplattingMap();
			break;
		}
		case TOOLSTATE::FLATTING:
		{
			if (G_Input.KeyCheck(VK_LBUTTON))
				FlattingMap();
			break;
		}
		
		case TOOLSTATE::OBJECTNEW:
		{
			if (G_Input.KeyCheck(VK_LBUTTON)==KEY_PUSH)
				CollocateObject();
				break;
		}
		case TOOLSTATE::OBJECTEDIT:
		{
			if (G_Input.KeyCheck(VK_LBUTTON) == KEY_PUSH)
				SelectObject();
			break;
		}
		
		default:
			break;
		}
	return true;
}
bool ToolCore::Render()
{

	I_MapMgr.Render();
	I_ObjMgr.Render();

	m_DebugLine.Draw(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(100, 0, 0), D3DXVECTOR4(1, 0, 0, 1));
	m_DebugLine.Draw(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 100, 0), D3DXVECTOR4(0, 1, 0, 1));
	m_DebugLine.Draw(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 100), D3DXVECTOR4(0, 0, 1, 1));
	return true;
}
bool ToolCore::Release()
{
	return true;
}



#pragma once
#include "pch.h"
#include "Sample.h"
#include"JH_DxState.h"
#include"JH_Input.h"
#include "JH_ShapePlane.h"
#include"LightMgr.h"


#pragma warning( disable:4005 )
HRESULT Sample::MapSplatting(SPHERE Sphere, const TCHAR* TextureFileName)
{
	HRESULT hr;
	int iNumTex = I_Texture.Add(m_pd3dDevice.Get(), TextureFileName);
	m_pTexture=I_Texture.GetPtr(iNumTex);
	D3D11_TEXTURE2D_DESC td;

	

	td.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	td.CPUAccessFlags = 0;
	td.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	td.Width = m_Map->m_iRowNum;
	td.Height = m_Map->m_iColumNum;
	td.Usage = D3D11_USAGE_DEFAULT;
	td.MipLevels = 1;
	td.ArraySize = 1;
	td.SampleDesc.Count = 1;
	td.SampleDesc.Quality = 0;
	td.MiscFlags = 0;


	if (FAILED(hr = m_pd3dDevice->CreateTexture2D(&td, NULL, m_SplattingTex.GetAddressOf())))
	{
		return hr;
	}
	
	D3D11_MAPPED_SUBRESOURCE MapSrc;
	
	if (SUCCEEDED(m_pImmediateContext->Map((ID3D11Resource*)m_SplattingTex.Get(), NULL, D3D11_MAP_READ_WRITE, NULL, &MapSrc)))
	{

		UCHAR* pTexcell = (UCHAR*)MapSrc.pData;
		for (int iRow = 0; iRow < td.Height; iRow++)
		{
			int irowStart = MapSrc.RowPitch*iRow;
			for (int iCol = 0; iCol < td.Width; iCol++)
			{
				float fDistance = sqrt((Sphere.vCenter.x - irowStart)*(Sphere.vCenter.x - irowStart) +
					(Sphere.vCenter.y - iCol)*(Sphere.vCenter.y - iCol));
				if (fDistance <= Sphere.Radius)
				{
					pTexcell[irowStart + iCol * 4]=1.0f;
				}

				
			}

		}
		m_pImmediateContext->Unmap((ID3D11Resource*)m_SplattingTex.Get(), D3D11CalcSubresource(0, 0, 1));

	}



	if (FAILED(hr = m_pd3dDevice->CreateShaderResourceView(
		m_SplattingTex.Get(), NULL,
		m_pSplSrv.GetAddressOf())))
	{
		return hr;
	}
	m_pImmediateContext->PSSetShaderResources(2, 1, m_pSplSrv.GetAddressOf());
	m_pImmediateContext->PSSetShaderResources(3, 1,&m_pTexture->m_pTextureRV);
}
void Sample::GetNearPoint()
{
	D3DXVECTOR3 v0, v1, v2, vIntersection;
	m_NearPoint = I_Select.m_Ray.vDirection*m_pMainCamera->m_fFar;
	m_fTimer += g_SecondPerFrame;

		m_fTimer = 0.0f;
		m_QuadTree->GetSelectNode(m_QuadTree->m_pRootNode);

		for (int iNode = 0; iNode <
			m_QuadTree->m_SelectNodeList.size(); iNode++)
		{
			DWORD dwFace = m_QuadTree->m_SelectNodeList[iNode]->m_IndexList.size() / 3;
			for (int iFace = 0; iFace < dwFace; iFace++)
			{
				DWORD i0 = m_QuadTree->m_SelectNodeList[iNode]->m_IndexList[iFace * 3 + 0];
				DWORD i1 = m_QuadTree->m_SelectNodeList[iNode]->m_IndexList[iFace * 3 + 1];
				DWORD i2 = m_QuadTree->m_SelectNodeList[iNode]->m_IndexList[iFace * 3 + 2];
				v0 = m_Map->m_VertexData[i0].p;
				v1 = m_Map->m_VertexData[i1].p;
				v2 = m_Map->m_VertexData[i2].p;

				D3DXVECTOR3 vDIR = I_Select.m_Ray.vDirection;
				D3DXVECTOR3 vEnd = I_Select.m_Ray.vOrigin + vDIR * m_pMainCamera->m_fFar;

				D3DXVECTOR3 vNormal;
				D3DXVECTOR3 e0 = v1 - v0;
				D3DXVECTOR3 e1 = v2 - v0;
				D3DXVec3Cross(&vNormal, &e0, &e1);

				if (I_Select.GetIntersection(
					I_Select.m_Ray.vOrigin,
					vEnd,
					vNormal,
					v0, v1, v2))
				{

					if (D3DXVec3Length(&(m_pMainCamera->m_vPos - m_NearPoint)) >
						D3DXVec3Length(&(m_pMainCamera->m_vPos - I_Select.m_vIntersection)))
					{
						m_NearPoint = I_Select.m_vIntersection;
					}
				}
			}
		}
	
}
void Sample::MapUpDown(SPHERE sphere)
{
	D3DXVECTOR3 v0, v1, v2;
	

	for (size_t iNode = 0; iNode < m_QuadTree->m_DrawNodeList.size(); iNode++)
	{
		float fDistance = sqrt((m_QuadTree->m_DrawNodeList[iNode]->m_Box.vCenter.x - sphere.vCenter.x)*
			(m_QuadTree->m_DrawNodeList[iNode]->m_Box.vCenter.x - sphere.vCenter.x) +
			(m_QuadTree->m_DrawNodeList[iNode]->m_Box.vCenter.z - sphere.vCenter.z)*
				(m_QuadTree->m_DrawNodeList[iNode]->m_Box.vCenter.z - sphere.vCenter.z));
		DWORD dwFace = m_QuadTree->m_DrawNodeList[iNode]->m_IndexList.size() / 3;
		if (sphere.Radius > fDistance)
		{
			for (int iFace = 0; iFace < dwFace; iFace++)
			{
				for (int iV = 0; iV < 3; iV++)
				{
					DWORD i0 = m_QuadTree->m_DrawNodeList[iNode]->m_IndexList[iFace * 3 + iV];


					fDistance = sqrt((m_Map->m_VertexData[i0].p.x - sphere.vCenter.x)*
						(m_Map->m_VertexData[i0].p.x - sphere.vCenter.x) +
						(m_Map->m_VertexData[i0].p.z - sphere.vCenter.z)*
						(m_Map->m_VertexData[i0].p.z - sphere.vCenter.z));

					float  fDet = (fDistance / sphere.Radius)*D3DX_PI / 2.0;
					if (sphere.Radius > fDistance)
					{
						float value = cos(fDet)*g_SecondPerFrame;
						m_Map->m_VertexData[i0].p.y += value;

					}
				}


			}
		}

	}
	m_pImmediateContext->UpdateSubresource(m_Map->m_dxHelper.m_pVertexBuffer, 0, 0, &m_Map->m_VertexData.at(0), 0, 0);

	
}
bool Sample::CreateMap(int iWidth,
	int iHeight,
	int iCellCount,
	int iCellSize,
	const TCHAR* pTexturFileName,
	const TCHAR* pNormalMapFileName)
{

	
	if (m_Map!=nullptr) m_Map->Release();
	m_Map = 0;

	m_Map = make_shared<JH_Map>();
	if (false)
	{
		m_Map->CreateHeightMap(m_pd3dDevice.Get(), m_pImmediateContext.Get(), L"../../data/map/heightMap513.bmp");
	}
	else
	{
		m_Map->m_iRowNum = iCellCount * iWidth + 1;
		m_Map->m_iColumNum = iCellCount * iHeight + 1;
	}

	
	m_Map->SetMapDesc(pTexturFileName, L"../../data/Shader/LightShader.txt", m_Map->m_iRowNum, m_Map->m_iColumNum, iCellSize, 2.0f);


	m_Map->m_pNormMapFileName=pNormalMapFileName;
	m_Map->Load(m_pd3dDevice.Get(), m_pImmediateContext.Get());
	
	
	m_QuadTree->Build(m_Map.get(), m_pMainCamera);


	return true;
}
int Sample::CreateObj(const TCHAR* pFileName, D3DXMATRIX& m_matWorld)
{

	static int i;
	if (pFileName == nullptr)
	{
		return  -1;
	}
	CurrentObjIndex = i;
	
	m_CurrentObj.reset();
	m_CurrentObj = make_shared<MaxObj>();

	m_CurrentObj->Load(m_pd3dDevice.Get(), m_pImmediateContext.Get(), pFileName);

	bAttach = true;
	return i++;

}
bool Sample::Init()
{

	I_LIGHT_MGR.GetDevice(m_pd3dDevice.Get());
	I_LIGHT_MGR.GetContext(m_pImmediateContext.Get());

	I_LIGHT_MGR.Init();

	m_pBox = make_shared<JHShapeBox>();
	m_pBox->Create(m_pd3dDevice.Get(), m_pImmediateContext.Get(),
		L"../../data/Shader/LightShader.txt", L"../../data/Resource/powerbattles_BG.gif");
	
	
	
	m_vp.Width = 150;
	m_vp.Height = 150;
	m_vp.TopLeftX = 0;
	m_vp.TopLeftY = 0;
	m_vp.MinDepth = 0;
	m_vp.MaxDepth = 1.0f;
	m_RenderTarget.Cretae(m_pd3dDevice.Get());
	m_QuadTree = make_shared<HQuadTree>();


	D3DXVECTOR3 p = D3DXVECTOR3(0, 50, 0);
	D3DXVECTOR3 a = D3DXVECTOR3(0, 0, 1);
	D3DXVECTOR3 u = D3DXVECTOR3(0, 1, 0); 
	D3DXMatrixLookAtLH(&m_matTopView,
		&p,
		&a,
		&u);

	D3DXMatrixPerspectiveFovLH(&m_matTopProj,
		D3DX_PI * 0.4f, 1, 1, 20000);

	m_DebugLine = make_shared<JH_ShapeLine>();
	m_DebugLine->Create(m_pd3dDevice.Get(), m_pImmediateContext.Get(), L"../../data/Shader/ColorBlend.txt", nullptr, "VSLine", "PSLine");

	m_pMainCamera->CreateViewMatrix(D3DXVECTOR3(0, 100, -50.0f), D3DXVECTOR3(0, 0, 0));
	m_pMainCamera->UpdateBasisVector();


	float fAspect = (float)g_rtClient.right / g_rtClient.bottom;
	m_pMainCamera->CreateProjMatrix(0.1F, 1000.0F, D3DX_PI*0.4F, fAspect);


	m_MiniMap.Create(m_pd3dDevice.Get(), m_pImmediateContext.Get(), L"../../data/Shader/LightShader.txt", nullptr);


	return true;
}
bool Sample::Frame()
{
	if (m_Map == nullptr)return true;

	//if (bAttach&&m_CurrentObj)
	//{
	//	D3DXMatrixIdentity(&m_CurrentObj->m_matWorld);
	//	

	//	m_CurrentObj->m_matWorld._11 = 0.1;
	//	m_CurrentObj->m_matWorld._22 = 0.1;
	//	m_CurrentObj->m_matWorld._33 = 0.1;

	//	m_CurrentObj->m_matWorld._41 = I_Select.m_Ray.vPoint.x;
	//	m_CurrentObj->m_matWorld._42 = I_Select.m_Ray.vPoint.y;
	//	m_CurrentObj->m_matWorld._43 = I_Select.m_Ray.vPoint.z;
	//	bAttach = false;
	//}
	 //test/adsfadsf
	D3DXVECTOR3 v0, v1, v2, vIntersection;
	I_LIGHT_MGR.Frame();
	I_LIGHT_MGR.m_cbLight.vEyeDir = { m_pMainCamera->m_vLookup,30 };
	I_LIGHT_MGR.m_cbLight.vEyePos = { m_pMainCamera->m_vPos,30 };

	if (G_Input.KeyCheck(VK_LBUTTON))//&& m_fTimer >=0.5)
	{
		if (m_Map->m_bMapEdit)
		{
			GetNearPoint();
			SPHERE sphere;
			sphere.vCenter = m_NearPoint;
			sphere.Radius = 5;
			MapUpDown(sphere);

		}
		
	}
	
	
		if (bSplatting)
		{
			if (G_Input.KeyCheck(VK_LBUTTON))//&& m_fTimer >=0.5)
			{
				GetNearPoint();
				SPHERE sphere;
				sphere.vCenter = m_NearPoint;
				sphere.Radius = 5;
				MapSplatting(sphere, L"../../data/map/Tile20.jpg");
			}
		}

	
	m_QuadTree->Frame();


	JH_DebugCamera* DebugCamera = (JH_DebugCamera*)m_pMainCamera;
	/*DebugCamera->UpdateCameraHeight(m_Map.GetHeight(m_pMainCamera->m_vPos.x, m_pMainCamera->m_vPos.z) + 10);*/

	m_RenderTarget.Begin(m_pImmediateContext.Get(), D3DXVECTOR4(1, 1, 1, 1));
	if (m_Map != nullptr)
	{
	
		m_Map->SetMatrix(nullptr,
			&m_matTopView,
			&m_matTopProj);
		//m_Map->Render();
		m_QuadTree->Render();
	}
	m_RenderTarget.End(m_pImmediateContext.Get());
	return true;
}
bool Sample::Render()
{

	if (m_Map == nullptr)return true;
	else
	{
		m_Map->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
		ID3D11Buffer*               pBuffers[3];
		pBuffers[0] = I_LIGHT_MGR.m_pLightConstantBuffer[0].Get();

		m_Map->UpdateConstantBuffer(I_LIGHT_MGR.m_pLightConstantBuffer[0].Get(), &I_LIGHT_MGR.m_cbLight);





		
		UINT offset = 0;
		UINT stride = sizeof(D3DXVECTOR3);
		m_Map->m_dxHelper.m_pContext->PSSetShaderResources(1, 1,&m_Map->m_pTexture->m_pTextureRV);
		m_Map->m_dxHelper.m_pContext->IASetVertexBuffers(1, 1, &m_Map->m_pTangentVB,&stride,&offset);
		m_Map->m_dxHelper.m_pContext->PSSetConstantBuffers(1, 1, pBuffers);
		
		//for (int i = 0; i < g_iLightNum; i++)
		//{
		//	I_LIGHT_MGR.m_LightObjList[i].SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
		//	I_LIGHT_MGR.m_LightObjList[i].Render();
		//}

		
		m_QuadTree->Render();
		if (m_CurrentObj)
		{
			m_CurrentObj->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
			m_CurrentObj->Render();
		}
	

	}

	for (auto obj : m_ObjList)
	{
		obj.second->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
		obj.second->Render();
		D3DXMatrixIdentity(&obj.second->m_matWorld);
		
	}
	m_MiniMap.SetMatrix(NULL, NULL, NULL);
	m_pImmediateContext->RSSetViewports(1, &m_vp);




	if (m_RenderTarget.m_pTexture != nullptr)
	{

		m_MiniMap.PreRender();
		m_pImmediateContext->PSSetShaderResources(0, 1,
			m_RenderTarget.m_pSRV.GetAddressOf());
		m_MiniMap.PostRender();

	}
	m_pImmediateContext->RSSetViewports(1, &m_ViewPort);

	//m_DebugLine->SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
	//m_DebugLine->Draw(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(100, 0, 0), D3DXVECTOR4(1, 0, 0, 1));
	//m_DebugLine->Draw(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 100, 0), D3DXVECTOR4(0, 1, 0, 1));
	//m_DebugLine->Draw(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 100), D3DXVECTOR4(0, 0, 1, 1));


	//m_pImmediateContext->UpdateSubresource(m_pLightConstantBuffer.Get(), 0, nullptr, &m_cbLight, 0, 0);*/


	
	//m_Map.m_dxHelper.m_pContext->PSSetConstantBuffers(2, 1, m_pLightConstantBuffer->GetAddressOf());
	
//	m_QuadTree->DrawNodeLine(m_QuadTree->m_pRootNode);
	






	return true;
}
bool Sample::Release()
{


	m_DebugLine->Release();

	return true;
}
Sample::Sample()
{
	m_fTimer = 0.0f;
	bAttach = false;
	bSplatting = false;
	
	CurrentObjIndex = -1;
}


Sample::~Sample()
{
}

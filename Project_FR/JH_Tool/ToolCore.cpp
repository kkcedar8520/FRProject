#include "pch.h"
#include "ToolCore.h"

bool ToolCore::Init()
{


	m_pMainCamera->CreateViewMatrix(D3DXVECTOR3(0, 0, -50.0f), D3DXVECTOR3(0, 0, 0));
	m_pMainCamera->UpdateBasisVector();


	float fAspect = (float)g_rtClient.right / g_rtClient.bottom;
	m_pMainCamera->CreateProjMatrix(0.1F, 1000.0F, D3DX_PI*0.4F, fAspect);

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
//bool ToolCore::CreateMap(int iWidth,
//	int iHeight,
//	int iCellCount,
//	int iCellSize,
//	const TCHAR* pTexturFileName,
//	const TCHAR* pNormalMapFileName ,
//	const TCHAR* pHeightMapFileName ,
//	const TCHAR* pLightShaderName )
//{
//	I_MapMgr.CreateMap(L"Stadard", iWidth, iHeight, iCellCount, iCellSize, pTexturFileName, pNormalMapFileName, pLightShaderName);
//	return true;
//}


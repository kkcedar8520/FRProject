#include "Project_FR.h"



bool Project_FR::Init()
{

	TestObj.Create(m_pd3dDevice.Get(), m_pImmediateContext.Get(),L"../../data/Shader/DefaultShader.txt",nullptr);

	m_ModleLoader.ModelLoad("Box", TestObj,m_pd3dDevice.Get());

	m_pMainCamera->CreateViewMatrix(D3DXVECTOR3(0, 0, -50.0f), D3DXVECTOR3(0, 0, 0));
	m_pMainCamera->UpdateBasisVector();


	float fAspect = (float)g_rtClient.right / g_rtClient.bottom;
	m_pMainCamera->CreateProjMatrix(0.1F, 1000.0F, D3DX_PI*0.4F, fAspect);
	
	return true;
}
bool Project_FR::Frame()
{
	TestObj.SetMatrix(nullptr,&m_pMainCamera->m_matView,&m_pMainCamera->m_matProj);


	return true;
}
bool Project_FR::Render()
{
	TestObj.Render();
	return true;
}
bool Project_FR::Release()
{
	return true;
}

Project_FR::Project_FR()
{

}
Project_FR:: ~Project_FR()
{

}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow) {
	Project_FR game;
	game.m_hinstance = hInstance;
	RECT rtClient = { 0,0,1000,600 };
	if (!game.InitWindow(L"ModelAseViewer", rtClient))
	{
		std::cout << "윈도우 생성 실패";
		return false;
	}
	game.Run();
	return 0;
}
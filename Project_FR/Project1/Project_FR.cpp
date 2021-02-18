#include "Project_FR.h"



bool Project_FR::Init()
{

 	m_ModleLoader.ModelLoad("pov_pilot_medium_bloodhound_LOD0", TestObj,m_pd3dDevice.Get());
	
	//test.Create(DX::GetDevice().Get(), DX::GetContext().Get(), L"../../data/shader/DefaultShader.txt",L"cncr25S.bmp");
	TestObj.Init();
	

	m_pMainCamera->CreateViewMatrix(D3DXVECTOR3(0, 0, -50.0f), D3DXVECTOR3(0, 0, 0));
	m_pMainCamera->UpdateBasisVector();


	float fAspect = (float)g_rtClient.right / g_rtClient.bottom;
	m_pMainCamera->CreateProjMatrix(0.1F, 1000.0F, D3DX_PI*0.4F, fAspect);
	
	return true;
}
bool Project_FR::Frame()
{




	TestObj.SetTransform(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);
	TestObj.Frame();
	
	//test.SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);


	return true;
}
bool Project_FR::Render()
{
	TestObj.Render();
//	test.Render();
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

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Project_FR game;
	game.m_hinstance = hInstance;
	RECT rtClient = { 0,0,1000,600 };
	if (!game.InitWindow(L"ModelAseViewer", rtClient))
	{
		std::cout << "윈도우 생성 실패";
		return false;
	}
	game.Run();

	_CrtSetBreakAlloc(217);
	
	return 0;
}


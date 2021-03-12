#include "Project_FR.h"



bool Project_FR::Init()
{

 	m_ModleLoader.ModelLoad("Box",m_pd3dDevice.Get());
	
	//test.Create(DX::GetDevice().Get(), DX::GetContext().Get(), L"../../data/shader/DefaultShader.txt",L"cncr25S.bmp");
	TestObj.ReadFile("Box");

	
	m_pMainCamera->CreateViewMatrix(D3DXVECTOR3(0, 0, -50.0f), D3DXVECTOR3(0, 0, 0));
	m_pMainCamera->UpdateBasisVector();

	

	float fAspect = (float)g_rtClient.right / g_rtClient.bottom;
	m_pMainCamera->CreateProjMatrix(0.1F, 1000.0F, D3DX_PI*0.4F, fAspect);
	TestObj.SetCamera(m_pMainCamera.get());
	TestObj.GetColliderBox().SetScale(D3DXVECTOR3(5,5,5));
	TestObj.SetScale(D3DXVECTOR3(1, 2, 1));

	m_DebugLine.Create(DX::GetDevice().Get(), DX::GetContext().Get(), L"../../data/shader/LineShader.txt", nullptr);
	return true;
}
bool Project_FR::Frame()
{



	m_DebugLine.SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);


	TestObj.Frame();
	

	//test.SetMatrix(nullptr, &m_pMainCamera->m_matView, &m_pMainCamera->m_matProj);


	return true;
}
bool Project_FR::Render()
{

	m_DebugLine.Draw(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(100, 0, 0), D3DXVECTOR4(1, 0, 0, 1));
	m_DebugLine.Draw(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 100, 0), D3DXVECTOR4(0, 1, 0, 1));
	m_DebugLine.Draw(D3DXVECTOR3(0, 0, 0), D3DXVECTOR3(0, 0, 100), D3DXVECTOR4(0, 0, 1, 1));


	TestObj.Frame();
	TestObj.Render();
	TestObj.RenderCollider();

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


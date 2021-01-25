#include "Project_FR.h"



bool Project_FR::Init()
{

	TestObj.Create(m_pd3dDevice.Get(), m_pImmediateContext.Get(),L"../../data/Shader/DefaultShader.txt",nullptr);

	m_ModleLoader.ModelLoad("Turret_Deploy", TestObj,m_pd3dDevice.Get());


	
	return true;
}
bool Project_FR::Frame()
{
	return true;
}
bool Project_FR::Render()
{
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
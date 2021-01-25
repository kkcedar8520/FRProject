#include "JHDXCore.h"
#include"JH_Input.h"
#include"JH_DxState.h"
#include"JH_Select.h"



LRESULT  JHDXCore::JWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (m_pMainCamera == nullptr) return -1;
	m_pMainCamera->MsgProc(hWnd, msg, wParam, lParam);
	return -1;
}
HRESULT JHDXCore::DeleteDXResource()
{
	m_Write.DiscardDeviceResources();
	return S_OK;
}
HRESULT	JHDXCore::CreateDXResource()
{
	if (m_pSwapChain == nullptr) return true;
	IDXGISurface*  pSurface;
	m_pSwapChain->GetBuffer(0,
		__uuidof(IDXGISurface),
		(void**)&pSurface);

	if (pSurface) pSurface->Release();

	
	m_Write.CreateDeviceResources(pSurface);
	return S_OK;

	float fAspect = (float)g_rtClient.right / (float)g_rtClient.bottom;

	m_pMainCamera->CreateProjMatrix(
		m_pMainCamera->m_fNear,
		m_pMainCamera->m_fFar,
		m_pMainCamera->m_fFovY,
		fAspect);
}
bool JHDXCore::Init()
{
	return true;
}
bool JHDXCore::Render()
{
	
	return true;
}
bool JHDXCore::Frame()
{
	return true;
}
bool JHDXCore::Release()
{
	return true;
}
bool JHDXCore::CoreInit()
{
	
	m_gamerun = true;
	
	if (FAILED(InitDevice()))
	{
		return false;
	}
	JDX::JH_DxState::SetState(m_pd3dDevice.Get());
	

	m_Timer.Init();
	
	
	G_Input.Init();

	
	m_DefaultCamera.SetViewProj();

	m_DebugCamera = std::make_shared<JH_DebugCamera>();
	m_ModelCamera = std::make_shared<ModelView>();
	m_pBackViewCamera = std::make_shared<JH_BackViewCamera>();



	m_pMainCamera = m_pBackViewCamera.get();


	
	IDXGISurface*  pSurface;
	m_pSwapChain->GetBuffer(0,
		__uuidof(IDXGISurface),
		(void**)&pSurface);

	m_Write.Set(m_hwnd, m_SwapChainDesc.BufferDesc.Width, m_SwapChainDesc.BufferDesc.Height, pSurface);
	if (pSurface) pSurface->Release();
	return Init();
}
bool JHDXCore::PreRender()
{
	float clearColor[] = {1,1,1,1 };
	m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView.Get(), clearColor);
	m_pImmediateContext->ClearDepthStencilView(
		m_pDepthStencilView.Get(),
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	m_pImmediateContext->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	JDX::ApplyBS(GetContext().Get(), JDX::JH_DxState::g_pAlpahBlend);
	JDX::ApplySS(GetContext().Get(), JDX::JH_DxState::g_pSamplerState);
	JDX::ApplyRS(GetContext().Get(), JDX::JH_DxState::g_pRSSold);
	if (m_bWireFrame == true)
	{
		JDX::ApplyRS(GetContext().Get(), JDX::JH_DxState::g_pRSWireFrame);
	}
	JDX::ApplyDSS(GetContext().Get(), JDX::JH_DxState::g_pDSS);
	SetViewPort();
	return true;
}

bool JHDXCore::CoreRender()
{
	PreRender();
	Render();
	PostRender();
	return true;
}

bool JHDXCore::PostRender()
{
	
	m_Timer.Render();
	m_Write.Render();
	DrawDebug();

	m_pSwapChain->Present(0, 0);
	return true;
}

bool JHDXCore::CoreFrame()
{
	
	G_Input.Frame();
	m_Timer.Frame();


	I_Select.SetMatrix(NULL,
		&m_pMainCamera->m_matView,
		&m_pMainCamera->m_matProj);

	Frame();
	m_pMainCamera->Frame();
	if (G_Input.KeyCheck(VK_F4) == KEY_PUSH)
	{
		m_bWireFrame = !m_bWireFrame;
	}
	return true;
}
bool JHDXCore::CoreRelease()
{
	m_Write.Release();
	G_Input.Release();
	m_Timer.Release();


	ReleaseDevice();
	return Release();
}
bool JHDXCore::Run()
{
	if (CoreInit() == false)
	{
		return false;
	}
	MSG msg;
	memset(&msg, 0, sizeof(msg));
	while (m_gamerun)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			if (msg.message == WM_QUIT)
			{
				break;
			}
		}
		else
		{
			if (CoreFrame() == false)
			{
				return false;
			}
			if (CoreRender() == false)
			{
				return false;
			}
		}
	}
	if (CoreRelease() == false)
	{
		return false;
	}
	return true;
}

void JHDXCore::DrawDebug()
{
#ifdef _DEBUG
	TCHAR pBuffer[256];
	memset(pBuffer, 0, sizeof(TCHAR) * 256);
	_stprintf_s(pBuffer, _T("FPS:%d"), m_Timer.GetFPS());
	RECT r1 = { 500.0f,300.0f,100.0f,100.0f };
	m_Write.Begin();
	m_Write.Add(m_Timer.m_SzBuffer, D2D1::ColorF(1, 0, 0, 1), r1);
	m_Write.DrawText(r1, pBuffer, D2D1::ColorF(1.0f, 0.0f, 0.0f, 1.0));;
	m_Write.End();
#endif
}
JHDXCore::JHDXCore()
{
	m_bWireFrame = false;
	m_gamerun = false;
}


JHDXCore::~JHDXCore()
{
}
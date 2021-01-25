#include "Device.h"



HRESULT Device::DeleteDXResource()
{
	HRESULT hr=S_OK;
	return hr;

}
HRESULT Device::CreateDXResource()
{
	HRESULT hr=S_OK;
	return hr;
}
HRESULT Device::InitDevice()
{
	HRESULT hr = S_OK;
	if (FAILED(hr = CreateDevice())) //SUCCEEDED(hr)
	{
		return false;
	}
	if (FAILED(hr = CreateGIFactory())) //SUCCEEDED(hr)
	{
		return false;
	}

	if (FAILED(hr = CreateSwapChain())) //SUCCEEDED(hr)
	{
		return false;
	}
	if (FAILED(hr = SetRenderTargetView())) //SUCCEEDED(hr)
	{
		return false;
	}
	SetViewPort();

	if (FAILED(hr = m_pGIFactory->MakeWindowAssociation(
		m_hwnd, DXGI_MWA_NO_WINDOW_CHANGES |
		DXGI_MWA_NO_ALT_ENTER)))
	{
		return true;
	}

	return hr;

}
void Device::SetViewPort()
{

	m_ViewPort.TopLeftX = 0;
	m_ViewPort.TopLeftY = 0;
	m_ViewPort.Width = g_rtClient.right;
	m_ViewPort.Height = g_rtClient.bottom;
	m_ViewPort.MinDepth = 0;
	m_ViewPort.MaxDepth = 1;
	m_pImmediateContext->RSSetViewports(1, &m_ViewPort);
	m_pImmediateContext->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

}
HRESULT  Device::CreateGIFactory()
{
	HRESULT hr = S_OK;

	IDXGIDevice* pDXGIDevice;
	hr = m_pd3dDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)&pDXGIDevice);

	IDXGIAdapter* pDXGIAdapter;
	hr = pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&pDXGIAdapter);

	pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_pGIFactory);

	pDXGIDevice->Release();
	pDXGIAdapter->Release();
	
	return hr;
	
}
HRESULT  Device::CreateDevice()
{
	HRESULT hr = S_OK;
	D3D_FEATURE_LEVEL retFeaturLevel;
	D3D_DRIVER_TYPE DriverType = D3D_DRIVER_TYPE_HARDWARE;
	UINT Flags = 0;
#ifdef  _DEBUG
	Flags |= D3D11_CREATE_DEVICE_DEBUG; //디버그 돌릴 때 세부정보 보기위한 설정
#endif   _DEBUG

	UINT createDeviceFlag = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
	createDeviceFlag |= D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_FEATURE_LEVEL pFeatureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT FeatureLevels = 2;
	hr = D3D11CreateDevice(
		NULL,
		DriverType,
		NULL,
		createDeviceFlag,
		pFeatureLevels,
		FeatureLevels,
		D3D11_SDK_VERSION,
		m_pd3dDevice.GetAddressOf(),
		&retFeaturLevel,
		&m_pImmediateContext);
	if (FAILED(hr))
	{
		return hr;
	}
	return hr;
}
HRESULT  Device::CreateSwapChain()
{
	HRESULT hr = S_OK;
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));

	sd.BufferCount = 1;
	sd.BufferDesc.Width = g_rtClient.right;
	sd.BufferDesc.Height = g_rtClient.bottom;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.SampleDesc.Count = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = g_hwnd;
	sd.Windowed = TRUE;
	
	hr = m_pGIFactory->CreateSwapChain( 
		m_pd3dDevice.Get(), &sd, m_pSwapChain.GetAddressOf()); //CreateSwapChain() 함수가 DXGIFACTORY에 포함 되어있음
	
	if (FAILED(hr))
	{
		return false;
	}
	if (FAILED(hr=m_pSwapChain->GetDesc(&m_SwapChainDesc)))//속성 넘겨주기
	{
		return false;
	}
	return hr;
}
HRESULT  Device::SetRenderTargetView()
{
	HRESULT hr = S_OK;

	ID3D11Texture2D* pBackBuffer;
	if (FAILED(hr=m_pSwapChain->GetBuffer(0,__uuidof(ID3D11Texture2D),(LPVOID*)&pBackBuffer))) //Back buffer 생성
	{
		return false;
	}
	if (FAILED (hr=m_pd3dDevice->CreateRenderTargetView(pBackBuffer,NULL,&m_pRenderTargetView)))
	{
		return false;
	}
	pBackBuffer->Release();

#pragma region dss용 텍스처 생성
	ID3D11Texture2D* pDepthTex;
	D3D11_TEXTURE2D_DESC td;
	ZeroMemory(&td, sizeof(D3D11_TEXTURE2D_DESC));
	td.Width = m_SwapChainDesc.BufferDesc.Width;
	td.Height = m_SwapChainDesc.BufferDesc.Height;
	td.MipLevels = 1;
	td.ArraySize = 1;
	td.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	td.SampleDesc.Count = 1;
	td.SampleDesc.Quality = 0;
	td.Usage = D3D11_USAGE_DEFAULT;
	td.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	hr = m_pd3dDevice->CreateTexture2D(&td, NULL, &pDepthTex);
#pragma endregion

#pragma region 깊이스텐실버퍼 생성
	D3D11_DEPTH_STENCIL_VIEW_DESC dsv;
	ZeroMemory(&dsv, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	dsv.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsv.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	dsv.Texture2D.MipSlice = 0;
	hr = m_pd3dDevice->CreateDepthStencilView(
		pDepthTex,
		&dsv,
		&m_pDepthStencilView);
#pragma endregion

	pDepthTex->Release();
	m_pImmediateContext->OMSetRenderTargets(1, m_pRenderTargetView.GetAddressOf(), m_pDepthStencilView.Get());// 렌더 장치와 병합
	return hr;
}
bool Device::ResizeDevice(UINT width, UINT height)
{
	if (m_pd3dDevice==NULL||m_pRenderTargetView==NULL) 
	{
		return true;
	}
	HRESULT hr = S_OK;

	if (FAILED(hr=DeleteDXResource()))
	{
		return hr;
	}
	m_pImmediateContext->OMSetRenderTargets(0, NULL, NULL);
	m_pRenderTargetView->Release();

	if (FAILED(hr=m_pSwapChain->ResizeBuffers(
		m_SwapChainDesc.BufferCount,
		width,height,
		m_SwapChainDesc.BufferDesc.Format,
		m_SwapChainDesc.Flags)))
	{
		return hr;
	}

	if (FAILED(hr=m_pSwapChain->GetDesc(&m_SwapChainDesc)))
	{
		return false;
	}
	if (FAILED(hr = SetRenderTargetView()))
	{
		return false;
	}
	SetViewPort();


	if (FAILED(hr = CreateDXResource()))
	{
		return hr;
	}
	return true;
}


bool Device::ReleaseDevice()
{
	//m_pDepthStencilView->Release();
	//m_pRenderTargetView->Release();
	//m_pSwapChain->Release();
	//m_pd3dDevice->Release();
	//m_pImmediateContext->Release();
	//m_pGIFactory->Release();

	
	

	return true;
}

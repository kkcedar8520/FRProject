#pragma once
#include"JH_DXStd.h"
#include"JHWindow.h"


class Device:public JHWindow
{
public:
	D3D11_VIEWPORT m_ViewPort;
	ComPtr<ID3D11Device> m_pd3dDevice;
	ComPtr<ID3D11DeviceContext> m_pImmediateContext;
	ComPtr<IDXGISwapChain> m_pSwapChain;
	ComPtr<ID3D11RenderTargetView> m_pRenderTargetView;
	ComPtr<IDXGIFactory> m_pGIFactory;
	ComPtr<ID3D11DepthStencilView> m_pDepthStencilView;
	DXGI_SWAP_CHAIN_DESC m_SwapChainDesc;

	ComPtr<ID3D11Device>GetDevice() {
		return m_pd3dDevice;
	}
	ComPtr<ID3D11DeviceContext>GetContext() {
		return m_pImmediateContext;
	}

public:
	void SetViewPort();
	bool ReleaseDevice();
public:
	HRESULT InitDevice();
	HRESULT CreateGIFactory();
	HRESULT CreateDevice();
	HRESULT CreateSwapChain();
	HRESULT SetRenderTargetView();
	bool ResizeDevice(UINT width,UINT height) override;
public:
	virtual HRESULT DeleteDXResource();
	virtual HRESULT	CreateDXResource();
public:

	Device() {}
	virtual ~Device(){}
};


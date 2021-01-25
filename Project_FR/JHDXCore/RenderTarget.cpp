#include "RenderTarget.h"


HRESULT RenderTarget::Cretae(ID3D11Device* pd3divice, float width, float height)
{
	
	HRESULT hr;

	D3D11_TEXTURE2D_DESC td;

	

	td.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	td.CPUAccessFlags = 0;
	td.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	td.Width = width;
	td.Height = height;
	td.Usage = D3D11_USAGE_DEFAULT;
	td.MipLevels = 1;
	td.ArraySize = 1;
	td.SampleDesc.Count = 1;
	td.SampleDesc.Quality = 0;
	td.MiscFlags = 0;


	if (FAILED(hr= pd3divice->CreateTexture2D(&td,NULL,m_pTexture.GetAddressOf())))
	{
		return hr;
	}
	if (FAILED(hr = pd3divice->CreateRenderTargetView(
		m_pTexture.Get(), NULL,
		m_pRenderTarget.GetAddressOf())))
	{
		return hr;
	}
	if (FAILED(hr = pd3divice->CreateShaderResourceView(
		m_pTexture.Get(), NULL,
		m_pSRV.GetAddressOf())))
	{
		return hr;
	}


	m_vp.Width = width;
	m_vp.Height = height;
	m_vp.TopLeftX = 0;
	m_vp.TopLeftY = 0;
	m_vp.MinDepth = 0;
	m_vp.MaxDepth = 1.0f;
}

bool RenderTarget::Begin(ID3D11DeviceContext* pContext,
	D3DXVECTOR4 vColor)
{
	m_iViewPorts = 1;
	pContext->RSGetViewports(&m_iViewPorts, m_vpOld);
	pContext->OMGetRenderTargets(1, &m_pOldRTV, &m_pOldDSV);

	ID3D11RenderTargetView* pNullRTV = NULL;
	ID3D11DepthStencilView* pNullDepth = nullptr;
	pContext->OMSetRenderTargets(1, &pNullRTV, pNullDepth);
	pContext->OMSetRenderTargets(1, m_pRenderTarget.GetAddressOf(),
		NULL);
	pContext->RSSetViewports(1, &m_vp);
	pContext->ClearRenderTargetView(m_pRenderTarget.Get(), vColor);
	return true;
}
bool RenderTarget::End(ID3D11DeviceContext* pContext)
{
	pContext->RSSetViewports(m_iViewPorts, m_vpOld);
	pContext->OMSetRenderTargets(1, &m_pOldRTV, m_pOldDSV);
	SAFE_RELEASE(m_pOldRTV);
	SAFE_RELEASE(m_pOldDSV);
	//SaveFile(pContext, L"save.png");
	return true;
}
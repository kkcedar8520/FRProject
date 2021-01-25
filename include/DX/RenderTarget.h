#pragma once
#include"JH_DxState.h"
#include"JH_DXStd.h"
class RenderTarget
{

public:

	ComPtr<ID3D11RenderTargetView>	 m_pRenderTarget;
	ComPtr<ID3D11Texture2D>			 m_pTexture;
	ComPtr<ID3D11DepthStencilView> m_pDepthStencilView;
	ComPtr<ID3D11ShaderResourceView> m_pSRV;
	D3D11_VIEWPORT			m_vp;

	D3D11_VIEWPORT			m_vpOld[D3D11_VIEWPORT_AND_SCISSORRECT_MAX_INDEX];
	UINT					m_iViewPorts;
	ID3D11RenderTargetView* m_pOldRTV;
	ID3D11DepthStencilView* m_pOldDSV;
public:
	HRESULT Cretae(ID3D11Device* p3Divice,float width=1024.0f,float height=1024.0f);
	bool Begin(ID3D11DeviceContext* pContext,
		D3DXVECTOR4 vColor);
	bool End(ID3D11DeviceContext* pContext);
};


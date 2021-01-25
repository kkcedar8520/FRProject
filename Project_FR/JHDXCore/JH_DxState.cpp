#include "JH_DxState.h"

namespace JDX
{
	ID3D11SamplerState*		JH_DxState::g_pSamplerState = nullptr;

	ID3D11BlendState*		JH_DxState::g_pAlpahBlend = nullptr;
	ID3D11BlendState*		JH_DxState::g_pAlpahBlendDisable = nullptr;

	ID3D11RasterizerState*	JH_DxState::g_pRSWireFrame = nullptr;
	ID3D11RasterizerState*	JH_DxState::g_pRSSold = nullptr;

	ID3D11DepthStencilState* JH_DxState::g_pDSS = nullptr;
	ID3D11DepthStencilState* JH_DxState::g_pDSSDisable = nullptr;


	Microsoft::WRL::ComPtr<ID3D11SamplerState>	JH_DxState::g_pSSEdit = 0;
	Microsoft::WRL::ComPtr<ID3D11BlendState>		JH_DxState::g_pBSEdit = 0;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState>	JH_DxState::g_pRSEdit = 0;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> JH_DxState::g_pDSSEdit = 0;
	D3D11_SAMPLER_DESC JH_DxState::g_SamplerDesc;
	D3D11_BLEND_DESC JH_DxState::g_BlendDesc = { 0, };
	D3D11_RASTERIZER_DESC JH_DxState::g_RasterizerDesc;
	D3D11_DEPTH_STENCIL_DESC JH_DxState::g_DepthStencilDesc = { 0, };

	HRESULT JH_DxState::SetState(ID3D11Device* pd3dDevice)
	{
		HRESULT hr;
		D3D11_SAMPLER_DESC descSamp;
		ZeroMemory(&descSamp, sizeof(D3D11_SAMPLER_DESC));
		descSamp.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		descSamp.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		descSamp.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		descSamp.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

		hr = pd3dDevice->CreateSamplerState(
			&descSamp,
			&g_pSamplerState);

		D3D11_BLEND_DESC bs;
		ZeroMemory(&bs, sizeof(D3D11_BLEND_DESC));
		//bs.AlphaToCoverageEnable;
		bs.IndependentBlendEnable = TRUE;;
		bs.RenderTarget[0].BlendEnable = TRUE;
		bs.RenderTarget[0].SrcBlend =
			D3D11_BLEND_SRC_ALPHA;
		bs.RenderTarget[0].DestBlend =
			D3D11_BLEND_INV_SRC_ALPHA;
		bs.RenderTarget[0].BlendOp =
			D3D11_BLEND_OP_ADD;
		bs.RenderTarget[0].SrcBlendAlpha =
			D3D11_BLEND_ONE;
		bs.RenderTarget[0].DestBlendAlpha =
			D3D11_BLEND_ZERO;
		bs.RenderTarget[0].BlendOpAlpha =
			D3D11_BLEND_OP_ADD;

		bs.RenderTarget[0].RenderTargetWriteMask =
			D3D11_COLOR_WRITE_ENABLE_ALL;

		hr = pd3dDevice->CreateBlendState(&bs,
			&g_pAlpahBlend);

		bs.RenderTarget[0].BlendEnable = FALSE;
		hr = pd3dDevice->CreateBlendState(&bs,
			&g_pAlpahBlendDisable);

		D3D11_RASTERIZER_DESC rd;
		ZeroMemory(&rd, sizeof(rd));
		rd.FillMode = D3D11_FILL_SOLID;
		rd.CullMode = D3D11_CULL_NONE;
		pd3dDevice->CreateRasterizerState(&rd, &g_pRSSold);
		rd.FillMode = D3D11_FILL_WIREFRAME;
		rd.CullMode = D3D11_CULL_NONE;
		pd3dDevice->CreateRasterizerState(&rd, &g_pRSWireFrame);


		D3D11_DEPTH_STENCIL_DESC dsd;
		ZeroMemory(&dsd, sizeof(D3D11_DEPTH_STENCIL_DESC));
		// Z 버퍼 비교 활성화
		dsd.DepthEnable = TRUE;
		// z값 버퍼에 저장
		dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		// 비교 연산
		dsd.DepthFunc = D3D11_COMPARISON_LESS;
		pd3dDevice->CreateDepthStencilState(&dsd, &g_pDSS);
		dsd.DepthEnable = FALSE;
		pd3dDevice->CreateDepthStencilState(&dsd, &g_pDSSDisable);
		return true;
	}
	HRESULT JH_DxState::SetSamplerState(ID3D11Device* pd3dDevice,
		ID3D11DeviceContext* pContext,
		D3D11_SAMPLER_DESC* pDesc,
		UINT StartSlot,
		UINT NumSamplers)
	{
		HRESULT hr;
		g_pSSEdit.Reset();

		D3D11_SAMPLER_DESC* applyDesc = &g_SamplerDesc;
		if (pDesc != nullptr)
		{
			applyDesc = pDesc;
		}
		g_SamplerDesc = *applyDesc;
		hr = pd3dDevice->CreateSamplerState(applyDesc,
			g_pSSEdit.GetAddressOf());
		if (FAILED(hr))
		{
			return hr;
		}
		ApplySS(pContext, g_pSSEdit.Get(), StartSlot, NumSamplers);
		return hr;
	}
	HRESULT JH_DxState::SetBlendState(ID3D11Device* pd3dDevice,
		ID3D11DeviceContext* pContext,
		D3D11_BLEND_DESC* pDesc,
		FLOAT BlendFactor[],
		UINT SampleMask)
	{
		HRESULT hr;
		g_pBSEdit.Reset();

		D3D11_BLEND_DESC* applyDesc = &g_BlendDesc;
		if (pDesc != nullptr)
		{
			applyDesc = pDesc;
		}
		g_BlendDesc = *applyDesc;
		hr = pd3dDevice->CreateBlendState(applyDesc,
			g_pBSEdit.GetAddressOf());
		if (FAILED(hr))
		{
			return hr;
		}
		ApplyBS(pContext, g_pBSEdit.Get(), BlendFactor, SampleMask);
		return hr;
	}
	HRESULT JH_DxState::SetRasterizerState(ID3D11Device* pd3dDevice,
		ID3D11DeviceContext* pContext,
		D3D11_RASTERIZER_DESC* pDesc)
	{
		HRESULT hr;
		g_pRSEdit.Reset();

		D3D11_RASTERIZER_DESC* applyDesc = &g_RasterizerDesc;
		if (pDesc != nullptr)
		{
			applyDesc = pDesc;
		}
		g_RasterizerDesc = *applyDesc;

		hr = pd3dDevice->CreateRasterizerState(applyDesc,
			g_pRSEdit.GetAddressOf());
		if (FAILED(hr))
		{
			return hr;
		}
		ApplyRS(pContext, g_pRSEdit.Get());
		return hr;
	}
	HRESULT JH_DxState::SetDepthStencilState(ID3D11Device* pd3dDevice,
		ID3D11DeviceContext* pContext,
		D3D11_DEPTH_STENCIL_DESC* pDesc,
		UINT StencilRef)
	{
		HRESULT hr;
		g_pDSSEdit.Reset();

		D3D11_DEPTH_STENCIL_DESC* applyDesc = &g_DepthStencilDesc;
		if (pDesc != nullptr)
		{
			applyDesc = pDesc;
		}
		g_DepthStencilDesc = *applyDesc;
		hr = pd3dDevice->CreateDepthStencilState(applyDesc,
			g_pDSSEdit.GetAddressOf());
		if (FAILED(hr))
		{
			return hr;
		}
		ApplyDSS(pContext, g_pDSSEdit.Get(), StencilRef);
		return hr;
	}

	bool JH_DxState::Release()
	{
		//g_pSSEdit;
		//g_pBSEdit;
		//g_pRSEdit;
		//g_pDSSEdit;

		g_pDSS->Release();
		g_pSamplerState->Release();
		g_pAlpahBlend->Release();
		g_pAlpahBlendDisable->Release();
		g_pRSWireFrame->Release();
		g_pRSSold->Release();
		g_pDSSDisable->Release();

		return true;
	}
	JH_DxState::JH_DxState()
	{
	}


	JH_DxState::~JH_DxState()
	{
		Release();
	}

	JH_DxState g_DxState;
}

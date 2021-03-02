#include "JH_SkyBox.h"


	bool	JH_SkyBox::CreateSkyBox(ID3D11Device* pDevice,
		ID3D11DeviceContext*pContext,
		const TCHAR* pLoadShaderFile,
		const TCHAR* pLoadTextureString)
	{
		Create(pDevice, pContext, pLoadShaderFile, pLoadTextureString,nullptr,"VS", "PS_Cube");
		D3DXMatrixScaling(&m_matWorld, 100000.0f, 100000.0f, 100000.0f);
		return true;
	}
	bool	JH_SkyBox::Render()
	{



		D3DXMATRIX matSkyBoxView = m_matView;
		matSkyBoxView._41 = 0;
		matSkyBoxView._42 = 0;
		matSkyBoxView._43 = 0;

	
		DX::ApplyDSS(m_dxHelper.GetDeviceContext(), DX::JH_DxState::g_pDSSDisable.Get());

		ID3D11SamplerState* ppSamplerStates[2] = { DX::JH_DxState::g_pSSClampPoint.Get(),DX::JH_DxState::g_pSSClampLinear.Get() };
		m_dxHelper.GetDeviceContext()->PSSetSamplers(0, 2, ppSamplerStates);

		SetMatrix(&m_matWorld, &matSkyBoxView, &m_matProj);

		PreRender();


		m_dxHelper.GetDeviceContext()->PSSetShaderResources(3, 1, m_pCubeTexSRV.GetAddressOf());
		m_dxHelper.GetDeviceContext()->DrawIndexed(36, 0, 0);

		DX::ApplyDSS(m_dxHelper.GetDeviceContext(), DX::JH_DxState::g_pDSS.Get());
		DX::ApplyRS(m_dxHelper.GetDeviceContext(), DX::JH_DxState::g_pRSSold.Get());
		DX::ApplySS(m_dxHelper.GetDeviceContext(), DX::JH_DxState::g_pSamplerState.Get());
		return true;
	}
	//HRESULT JH_SkyBox::LoadTextures(ID3D11Device* pDevice, const TCHAR* pLoadTextureString)
	//{
	//
	//}
	HRESULT  JH_SkyBox::CreateTexutureArray(
		ID3D11Device* pDevice,
		ID3D11DeviceContext* pContext,
		const TCHAR** TextureArray)
	{
		HRESULT hr = S_OK;
		const TCHAR* g_szSkyTexture[] =
		{
			L"..\\..\\data\\sky\\st00_cm_front.bmp",
			L"..\\..\\data\\sky\\st00_cm_back.bmp",
			L"..\\..\\data\\sky\\st00_cm_right.bmp",
			L"..\\..\\data\\sky\\st00_cm_left.bmp",
			L"..\\..\\data\\sky\\st00_cm_up.bmp",
			L"..\\..\\data\\sky\\st00_cm_down.bmp"
		};

		int iNumTexture = sizeof(g_szSkyTexture) / sizeof(g_szSkyTexture[0]);

		for (int iTex = 0; iTex < iNumTexture; iTex++)
		{
			D3DX11CreateShaderResourceViewFromFile(m_dxHelper.GetDevice(),
				g_szSkyTexture[iTex],
				NULL, NULL,
				&m_pTexSRV[iTex],
				NULL);
		}
		return hr;
	}

	HRESULT  JH_SkyBox::CreateTexuture(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, const TCHAR* Texture)
	{

		HRESULT hr = S_OK;
		if (FAILED(hr = D3DX11CreateShaderResourceViewFromFile(m_dxHelper.GetDevice(),
			Texture,
			NULL, NULL,
			m_pCubeTexSRV.GetAddressOf(),
			NULL)));
		return hr;
	}
	bool JH_SkyBox::Frame()
	{
		float Angle = g_SecondPerFrame * D3DX_PI / 100.0f;
		D3DXMATRIX matRot;
		D3DXMatrixRotationY(&matRot, Angle);

		m_matWorld *= matRot;

		return true;
	}
	JH_SkyBox::JH_SkyBox()
	{
	}


	JH_SkyBox::~JH_SkyBox()
	{
	}

#include "JH_DXHelperEX.h"
#include"JH_DXStd.h"
#pragma warning( disable:4005 )

extern ComPtr<ID3D11Device>			g_pd3dDevice=nullptr;
extern ComPtr<ID3D11DeviceContext>  g_pd3dDeviceContext=nullptr;

void JH_DXHelperEX::PreRender()
{
	HRESULT hr = S_OK;
	UINT stride=m_iVertexSize;
	UINT offset = 0;
	
	m_pContext->IASetVertexBuffers(
		0, 1, m_pVertexBuffer.GetAddressOf(), &stride, &offset);

	m_pContext->IASetIndexBuffer(m_pIndexBuffer.Get(),
		DXGI_FORMAT_R32_UINT, 0);

	m_pContext->VSSetShader(m_pVS.Get(), NULL, 0);
	m_pContext->PSSetShader(m_pPS.Get(), NULL, 0);

	m_pContext->VSSetConstantBuffers(0, 1, m_pConstantBuffer.GetAddressOf());
	m_pContext->PSSetConstantBuffers(0, 1, m_pConstantBuffer.GetAddressOf());
	m_pContext->IASetInputLayout(m_pVertexLayout.Get());
	m_pContext->PSSetShaderResources(0, 1, m_pSRV.GetAddressOf());
	
}
void JH_DXHelperEX::Render()
{
	PreRender();
	PostRender();
}
void JH_DXHelperEX::PostRender()
{
	if (m_iNumIndex>0)
	{
		m_pContext->DrawIndexed(m_iNumIndex, 0, 0);
	}
	else
	{
		m_pContext->Draw(m_iNumVertex, 0);
	}
}
JH_DXHelperEX::JH_DXHelperEX()
{
	m_iVertexSize = 0;
	m_iNumVertex = 0;
	m_iNumIndex = 0;
	m_pVertexBuffer = nullptr;
	m_pIndexBuffer = nullptr;
	m_pVertexLayout = nullptr;
	m_pConstantBuffer = nullptr;
	m_pVS = nullptr;
	m_pPS = nullptr;
	m_pSRV = nullptr;
}


JH_DXHelperEX::~JH_DXHelperEX()
{
	//if (m_pVertexBuffer) m_pVertexBuffer->Release();
	//if (m_pIndexBuffer)m_pIndexBuffer->Release();
	//if (m_pVertexLayout)m_pVertexLayout->Release();
	//if (m_pVS)m_pVS->Release();
	//if (m_pPS)m_pPS->Release();
	//if (m_pSRV)m_pSRV->Release();
	//if (m_pVertexCode)m_pVertexCode->Release();
	//if (m_pPixelCode)m_pPixelCode->Release();
}

namespace DX
{
	ID3D11Buffer* MakeConstantBuffer(ID3D11Device* m_pDevice, void* Data, int iSize, int Num, bool bDynamic)
	{
		HRESULT hr;

		ID3D11Buffer* TempBuffer;


		D3D11_BUFFER_DESC pDesc;
		ZeroMemory(&pDesc, sizeof(D3D11_BUFFER_DESC));

		if (bDynamic == true)
		{
			pDesc.Usage = D3D11_USAGE_DYNAMIC;
			pDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		}
		else
		{
			pDesc.Usage = D3D11_USAGE_DEFAULT;
			pDesc.CPUAccessFlags = 0;
		}

		pDesc.ByteWidth = iSize * Num;
		pDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;


		D3D11_SUBRESOURCE_DATA pInitialData;
		ZeroMemory(&pInitialData,
			sizeof(D3D11_SUBRESOURCE_DATA));
		pInitialData.pSysMem = Data;

		if (Data != nullptr)
		{
			if (FAILED(hr = m_pDevice->CreateBuffer(&pDesc,
				&pInitialData,
				&TempBuffer)))
			{
				return nullptr;
			}
		}
		else
		{
			if (FAILED(hr = m_pDevice->CreateBuffer(&pDesc,
				NULL,
				&TempBuffer)))
			{
				return nullptr;
			}
		}

		return std::move(TempBuffer);
	}


	ID3D11Buffer* CreateIndexBuffer(ID3D11Device*  pd3dDevice, void *indices, UINT iNumIndex,
		UINT iSize, bool bDynamic)
	{
		HRESULT hr = S_OK;
		ID3D11Buffer* pBuffer = nullptr;
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		D3D11_SUBRESOURCE_DATA InitData;
		ZeroMemory(&InitData, sizeof(InitData));
		if (bDynamic)
		{
			bd.Usage = D3D11_USAGE_DYNAMIC;
			bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		}
		else
		{
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.CPUAccessFlags = 0;
		}
		bd.ByteWidth = iSize * iNumIndex;
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		InitData.pSysMem = indices;
		if (indices != NULL)
		{
			if (FAILED(hr = pd3dDevice->CreateBuffer(&bd, &InitData, &pBuffer)))
			{
				H(hr);
				return nullptr;
			}
		}
		else
		{
			if (FAILED(hr = pd3dDevice->CreateBuffer(&bd, NULL, &pBuffer)))
			{
				H(hr);
				return nullptr;
			}
		}
		return pBuffer;
	}
	ID3D11ShaderResourceView*	CreateShaderResourceView(ID3D11Device* pDevice, const TCHAR* strFilePath)
	{
		HRESULT hr = S_OK;
		if (strFilePath == NULL) return nullptr;
		ID3D11ShaderResourceView* pSRV = nullptr;
		if (FAILED(hr = D3DX11CreateShaderResourceViewFromFile(pDevice, strFilePath, NULL,
			NULL, &pSRV, NULL)))
		{
			H(hr);
			return nullptr;
		}
		return pSRV;
	}
	ID3D11Buffer* CreateVertexBuffer(
		ID3D11Device*  pd3dDevice,
		void *vertices,
		UINT iNumVertex,
		UINT iVertexSize,
		bool bDynamic)
	{
		HRESULT hr = S_OK;
		ID3D11Buffer* pBuffer = nullptr;
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(bd));
		if (bDynamic)
		{
			bd.Usage = D3D11_USAGE_DYNAMIC;
			bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		}
		else
		{
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.CPUAccessFlags = 0;
		}
		bd.ByteWidth = iVertexSize * iNumVertex;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA InitData;
		ZeroMemory(&InitData, sizeof(InitData));
		InitData.pSysMem = vertices;
		if (vertices != NULL)
		{
			if (FAILED(hr = pd3dDevice->CreateBuffer(&bd, &InitData, &pBuffer)))
			{
				H(hr);
				return nullptr;
			}
		}
		else
		{
			if (FAILED(hr = pd3dDevice->CreateBuffer(&bd, NULL, &pBuffer)))
			{
				H(hr);
				return nullptr;
			}
		}
		return pBuffer;
	}

	ComPtr<ID3D11Device> GetDevice()
	{
		return g_pd3dDevice;
	}

	ComPtr<ID3D11DeviceContext> GetContext()
	{
		return g_pd3dDeviceContext;
	}

	void SetDXGlobal(ComPtr<ID3D11Device>	pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dDeviceContext)
	{
		g_pd3dDevice = pd3dDevice;
		g_pd3dDeviceContext = pd3dDeviceContext;

	}


	
}
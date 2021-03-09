#include "JH_DXHelperEX.h"
#include"JH_DXStd.h"
#pragma warning( disable:4005 )

extern ComPtr<ID3D11Device>			g_pd3dDevice=nullptr;
extern ComPtr<ID3D11DeviceContext>  g_pd3dDeviceContext=nullptr;





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
	//
	HRESULT CreateComputeShader(LPCWSTR pSrcFile, LPCSTR pFunctionName, ID3D11Device* pDevice, ID3D11ComputeShader** ppShaderOut)
	{
		HRESULT hr;

		DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG ) 
		dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

		const D3D_SHADER_MACRO defines[] =
		{
	#ifdef USE_STRUCTURED_BUFFERS
			"USE_STRUCTURED_BUFFERS", "1",
	#endif
			NULL, NULL
		};

		// We generally prefer to use the higher CS shader profile when possible as CS 5.0 is better performance on 11-class hardware
		LPCSTR pProfile = (pDevice->GetFeatureLevel() >= D3D_FEATURE_LEVEL_11_0) ? "cs_5_0" : "cs_4_0";

		ID3DBlob* pErrorBlob = NULL;
		ID3DBlob* pBlob = NULL;
		hr = D3DX11CompileFromFile(pSrcFile, defines, NULL, pFunctionName, pProfile,
			dwShaderFlags, NULL, NULL, &pBlob, &pErrorBlob, NULL);
		if (FAILED(hr))
		{
			if (pErrorBlob)
				OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());

			if (pErrorBlob)
			{
				pErrorBlob->Release();
				pErrorBlob = NULL;
			}
			if (pBlob)
			{
				pBlob->Release();
				pBlob = NULL;
			}

			return hr;
		}

		hr = pDevice->CreateComputeShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), NULL, ppShaderOut);

		if (pErrorBlob)
		{
			pErrorBlob->Release();
			pErrorBlob = NULL;
		}
		if (pBlob)
		{
			pBlob->Release();
			pBlob = NULL;
		}

		return hr;
	}
	HRESULT CreateStructuredBuffer(ID3D11Device* pd3dDevice, UINT uElementSize, UINT uCount, VOID* pInitData, ID3D11Buffer** ppBufOut)
	{
		HRESULT hr = S_OK;
		*ppBufOut = NULL;

		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;
		desc.ByteWidth = uElementSize * uCount;
		desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		desc.StructureByteStride = uElementSize;

		if (pInitData)
		{
			D3D11_SUBRESOURCE_DATA InitData;
			ZeroMemory(&InitData, sizeof(D3D11_SUBRESOURCE_DATA));
			InitData.pSysMem = pInitData;
			hr = pd3dDevice->CreateBuffer(&desc, &InitData, ppBufOut);
			return hr;
		}
		else
		{
			hr = pd3dDevice->CreateBuffer(&desc, NULL, ppBufOut);
			return hr;
		}
	}
	HRESULT CreateBufferSRV(ID3D11Device* pd3dDevice, ID3D11Buffer* buf, ID3D11ShaderResourceView** srv)
	{
		HRESULT hr = S_OK;
		D3D11_BUFFER_DESC descBuf;
		ZeroMemory(&descBuf, sizeof(descBuf));
		buf->GetDesc(&descBuf);

		D3D11_SHADER_RESOURCE_VIEW_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.ViewDimension = D3D11_SRV_DIMENSION_BUFFEREX;
		desc.BufferEx.FirstElement = 0;

		desc.Format = DXGI_FORMAT_UNKNOWN;
		desc.BufferEx.NumElements = descBuf.ByteWidth / descBuf.StructureByteStride;

		hr = pd3dDevice->CreateShaderResourceView(buf, &desc, srv);
		return hr;
	}

	HRESULT CreateBufferUAV(ID3D11Device* pd3dDevice, ID3D11Buffer* pBuffer, ID3D11UnorderedAccessView** ppSRVOut)
	{
		HRESULT hr = S_OK;
		D3D11_BUFFER_DESC descBuf;
		ZeroMemory(&descBuf, sizeof(descBuf));
		pBuffer->GetDesc(&descBuf);

		D3D11_UNORDERED_ACCESS_VIEW_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
		desc.Buffer.FirstElement = 0;

		if (descBuf.MiscFlags & D3D11_RESOURCE_MISC_BUFFER_ALLOW_RAW_VIEWS)
		{
			// This is a Raw Buffer

			desc.Format = DXGI_FORMAT_R32_TYPELESS; // Format must be DXGI_FORMAT_R32_TYPELESS, when creating Raw Unordered Access View
			desc.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_RAW;
			desc.Buffer.NumElements = descBuf.ByteWidth / 4;
		}
		else
			if (descBuf.MiscFlags & D3D11_RESOURCE_MISC_BUFFER_STRUCTURED)
			{
				// This is a Structured Buffer

				desc.Format = DXGI_FORMAT_UNKNOWN;      // Format must be must be DXGI_FORMAT_UNKNOWN, when creating a View of a Structured Buffer
				desc.Buffer.NumElements = descBuf.ByteWidth / descBuf.StructureByteStride;
			}
			else
			{
				return E_INVALIDARG;
			}
		hr = pd3dDevice->CreateUnorderedAccessView(pBuffer, &desc, ppSRVOut);
		return hr;
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
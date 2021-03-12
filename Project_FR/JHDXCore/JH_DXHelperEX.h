#pragma once
#include"JH_DXHelper.h"
#include<vector>

extern ComPtr<ID3D11Device>			g_pd3dDevice;
extern ComPtr<ID3D11DeviceContext>  g_pd3dDeviceContext;
namespace DX
{
	ID3D11Buffer* MakeConstantBuffer(ID3D11Device* m_pDevice, void* Data, int iSize, int Num, bool bDynamic=false);
	ID3D11Buffer* CreateIndexBuffer(ID3D11Device*  pd3dDevice, void *indices, UINT iNumIndex,
		UINT iSize, bool bDynamic = false);
	ID3D11ShaderResourceView*	CreateShaderResourceView(ID3D11Device* pDevice, const TCHAR* strFilePath);
	ID3D11Buffer* CreateVertexBuffer(
		ID3D11Device*  pd3dDevice,
		void *vertices,
		UINT iNumVertex,
		UINT iVertexSize,
		bool bDynamic=false);

	HRESULT CreateComputeShader(LPCWSTR pSrcFile, LPCSTR pFunctionName, ID3D11Device* pDevice, ID3D11ComputeShader** ppShaderOut);

	HRESULT CreateBufferSRV(ID3D11Device* pd3dDevice, ID3D11Buffer* buf, ID3D11ShaderResourceView** srv);
	HRESULT CreateBufferUAV(ID3D11Device* pd3dDevice, ID3D11Buffer* pBuffer, ID3D11UnorderedAccessView** ppSRVOut);
	HRESULT CreateStructuredBuffer(ID3D11Device* pd3dDevice, UINT uElementSize, UINT uCount, VOID* pInitData, ID3D11Buffer** ppBufOut);


	ComPtr<ID3D11Device> GetDevice();
	ComPtr<ID3D11DeviceContext> GetContext();
	
	void SetDXGlobal(ComPtr<ID3D11Device>	pd3dDevice, ComPtr<ID3D11DeviceContext> pd3dDeviceContext);

	D3DXMATRIX DecomposeMtrixMultiply(D3DXMATRIX  mat1, D3DXMATRIX  mat2);
}

class JH_DXHelperEX
{
public:

public:
	JH_DXHelperEX();
	virtual ~JH_DXHelperEX();
};


#pragma once
#include"JH_DXHelper.h"

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
}

class JH_DXHelperEX
{
public:
	UINT	m_iVertexSize;
	UINT	m_iNumVertex;
	UINT	m_iNumIndex;
public:
	ComPtr<ID3D11Device>			m_pd3dDevice;
	ComPtr<ID3D11DeviceContext>	m_pContext;

	ComPtr<ID3D11Buffer>			m_pVertexBuffer;
	ComPtr<ID3D11Buffer>			m_pIndexBuffer;
	ComPtr<	ID3D11Buffer>	m_pConstantBuffer;
	ComPtr<ID3D11InputLayout>		m_pVertexLayout;
	ComPtr<ID3D11VertexShader>		m_pVS;
	ComPtr<ID3D11PixelShader>		m_pPS;
	ComPtr<ID3D11ShaderResourceView>  m_pSRV;



	ComPtr<ID3DBlob> m_pVertexCode;
	ComPtr<ID3DBlob> m_pPixelCode;
public:
	void PreRender();
	void Render();
	void PostRender();
public:
	JH_DXHelperEX();
	virtual ~JH_DXHelperEX();
};


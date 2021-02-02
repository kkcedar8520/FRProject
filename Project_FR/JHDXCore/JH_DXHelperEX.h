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
private:
	ComPtr<ID3D11Device>		m_pd3dDevice;
	ComPtr<ID3D11DeviceContext>	m_pContext;

	ComPtr<ID3D11Buffer>				m_pVertexBuffer;
	ComPtr<ID3D11Buffer>				m_pIndexBuffer;
	ComPtr<	ID3D11Buffer>				m_pConstantBuffer;
	ComPtr<ID3D11InputLayout>			m_pVertexLayout;
	ComPtr<ID3D11VertexShader>			m_pVS;
	ComPtr<ID3D11PixelShader>			m_pPS;
	ComPtr<ID3D11ShaderResourceView>	m_pSRV;



	ComPtr<ID3DBlob> m_pVertexCode;
	ComPtr<ID3DBlob> m_pPixelCode;
public:

	
	ID3D11Device*		 GetDevice()				{ return m_pd3dDevice.Get(); }
	ID3D11DeviceContext* GetDeviceContext()		    { return m_pContext.Get(); }
	ID3D11Buffer*		 GetConstantBuffer()		{ return m_pConstantBuffer.Get(); }
	ID3D11Buffer*		 GetVertexBuffer()			{ return m_pVertexBuffer.Get(); }
	ID3D11Buffer**		 GetVertexBufferAddress()	{ return m_pVertexBuffer.GetAddressOf(); }

	ID3D11Buffer*		 GetIndexBuffer()			{ return m_pIndexBuffer.Get(); }
	ID3D11Buffer**		 GetIndexBufferAddress()	{ return m_pIndexBuffer.GetAddressOf(); }


	ID3DBlob*			 GetVertexCode()				{ return m_pVertexCode.Get(); }
	ID3DBlob*		     GetPixelCode()					{ return m_pPixelCode.Get(); }

	ID3DBlob**			 GetVertexCodeAddress()			{ return m_pVertexCode.GetAddressOf(); }
	ID3DBlob**		     GetPixelCodeAddress()			{ return m_pPixelCode.GetAddressOf(); }

	ID3D11VertexShader*	 GetVertexShader()				{ return m_pVS.Get(); }
	ID3D11PixelShader*   GetPixelShader()				{ return m_pPS.Get(); }

	ID3D11VertexShader** GetVertexShaderAddress()		{ return m_pVS.GetAddressOf(); }
	ID3D11PixelShader**  GetPixelShaderAddress()		{ return m_pPS.GetAddressOf(); }

	ID3D11InputLayout**  GetLayoutAdress()				{ return m_pVertexLayout.GetAddressOf(); }

	
	ID3D11ShaderResourceView*  GetShaderResourceView() { return m_pSRV.Get(); }
	ID3D11ShaderResourceView** GetShaderResourceViewAddress() { return m_pSRV.GetAddressOf(); }

	//Set
	void				 SetConstantBuffer(ID3D11Buffer* ConstantBuffer)		{  m_pConstantBuffer=ConstantBuffer; }
	void				 SetDevice(ID3D11Device* pDevice)						{  m_pd3dDevice=pDevice; }
	void				 SetDeviceContext(ID3D11DeviceContext* pContext)		{  m_pContext=pContext; }
public:
	void PreRender();
	void Render();
	void PostRender();
public:
	JH_DXHelperEX();
	virtual ~JH_DXHelperEX();
};


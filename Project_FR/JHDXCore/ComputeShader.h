#pragma once
#include"JH_DXStd.h"
class ComputeShader
{
public:
	ComPtr<ID3D11ComputeShader> m_pCS; 
	//Input Output Texture
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_pStructureBF;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	m_pBufSrv;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>				pUAVTexture;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>				pReadTexture;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>				pWriteTexture;

	Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView>	m_pUAV;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	m_pReadSrv;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	m_pDescSrv;
public:


	HRESULT SetStructureBuffer(void* Buf,int size);
	HRESULT CreateComputeShader(const std::wstring FileName, const std::string MainFunc);
	HRESULT CreateStreamSRV(UINT iWidth, UINT iHeight);
	//Excute
	void 	RunComputeShaderSplatting(UINT X, UINT Y, UINT Z);

};



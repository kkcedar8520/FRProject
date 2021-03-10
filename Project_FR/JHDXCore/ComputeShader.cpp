#include "ComputeShader.h"
HRESULT ComputeShader::CreateStreamSRV(UINT iWidth, UINT iHeight)
{


	// 읽기용 텍스쳐 소스텍스쳐
	HRESULT hr = S_OK;
	//before dispatch
	D3D11_TEXTURE2D_DESC td;
	ZeroMemory(&td, sizeof(td));
	td.Width = iWidth;
	td.Height = iHeight;
	td.MipLevels = 1;
	td.MiscFlags = 0;
	td.ArraySize = 1;
	td.SampleDesc.Count = 1;
	td.SampleDesc.Quality = 0;
	td.Usage = D3D11_USAGE_DEFAULT;
	td.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;
	td.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	hr = DX::GetDevice()->CreateTexture2D(&td, NULL, pUAVTexture.GetAddressOf());


	hr = DX::GetDevice()->CreateTexture2D(&td, NULL, pReadTexture.GetAddressOf());

	// GPU 에서 읽고쓰기위한 UAV UnorderedView 

	D3D11_UNORDERED_ACCESS_VIEW_DESC viewDescUAV;
	ZeroMemory(&viewDescUAV, sizeof(viewDescUAV));
	viewDescUAV.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	viewDescUAV.ViewDimension = D3D11_UAV_DIMENSION_TEXTURE2D;
	viewDescUAV.Texture2D.MipSlice = 0;
	hr = DX::GetDevice()->CreateUnorderedAccessView(pUAVTexture.Get(), &viewDescUAV, m_pUAV.GetAddressOf());

	//the getSRV function after dispatch.



	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MipLevels = 1;
	srvDesc.Texture2D.MostDetailedMip = 0;
	hr = DX::GetDevice()->CreateShaderResourceView(pUAVTexture.Get(), &srvDesc, m_pReadSrv.GetAddressOf());
	hr = DX::GetDevice()->CreateShaderResourceView(pReadTexture.Get(), &srvDesc, m_pDescSrv.GetAddressOf());

	return hr;
}
HRESULT ComputeShader::SetStructureBuffer(void* Buf, int size)
{

	// 컴퓨터쉐이더에서 상수버퍼형식으로 필요한데이터를 버퍼에 담아 넘겨줌 그 버퍼는 쉐이더리소스 뷰 형식으로 넘겨야한다 
	HRESULT hr = S_OK;
	hr=(DX::CreateStructuredBuffer(DX::GetDevice().Get(), size, 1, Buf, m_pStructureBF.GetAddressOf()));
	if (hr == S_FALSE)return hr;
	hr=(DX::CreateBufferSRV(DX::GetDevice().Get(), m_pStructureBF.Get(), m_pBufSrv.GetAddressOf()));

	return hr;
}
HRESULT ComputeShader::CreateComputeShader(const std::wstring FileName, const std::string MainFunc)
{
	HRESULT hr=S_OK;
	hr=DX::CreateComputeShader(FileName.c_str(), MainFunc.c_str(), DX::GetDevice().Get(), m_pCS.GetAddressOf());

	return hr;
}

void 	ComputeShader::RunComputeShaderSplatting(UINT X, UINT Y,UINT Z)
{

	ID3D11ShaderResourceView* ppSRVNULL[2] = { nullptr, nullptr };
	//DX::GetContext()->CSSetShaderResources(0, 2, ppSRVNULL);
	//DX::GetContext()->CSSetShaderResources(1, 2, ppSRVNULL);
	ID3D11UnorderedAccessView* ppUAViewNULL[1] = { nullptr };
	//DX::GetContext()->CSSetUnorderedAccessViews(0, 1, ppUAViewNULL, NULL);
	//DX::GetContext()->CSSetShader(NULL, NULL, 0);

	DX::GetContext()->CSSetShader(m_pCS.Get(), NULL, 0);


	DX::GetContext()->CSSetShaderResources(0, 1, m_pReadSrv.GetAddressOf());
	DX::GetContext()->CSSetShaderResources(1, 1, m_pBufSrv.GetAddressOf());



	DX::GetContext()->CSSetUnorderedAccessViews(0, 1, m_pUAV.GetAddressOf(), NULL);
	ID3D11Buffer* ppCBNULL[1] = { NULL };
	DX::GetContext()->CSSetConstantBuffers(0, 1, ppCBNULL);

	//NVIDIA 에서 지원하는 쿠다코어의 개수에 배수형식으로 하는것이 효율로 좋은데 보통 256을많이쓴다
	DX::GetContext()->Dispatch(X, Y, Z);





	// CS 세팅 해제
	DX::GetContext()->CSSetShader(NULL, NULL, 0);



	DX::GetContext()->CSSetUnorderedAccessViews(0, 1, ppUAViewNULL, NULL);


	DX::GetContext()->CSSetShaderResources(0, 2, ppSRVNULL);
	DX::GetContext()->CSSetShaderResources(1, 2, ppSRVNULL);


	DX::GetContext()->CSSetConstantBuffers(0, 1, ppCBNULL);


	//GPU에있는 계산완료된 데이터를 CPU 데이터로 옮겨온다
	DX::GetContext()->CopyResource((ID3D11Resource*)pReadTexture.Get(), (ID3D11Resource*)pUAVTexture.Get());



}
bool ComputeShader::Release()
{
	m_pCS.ReleaseAndGetAddressOf();
	m_pStructureBF.ReleaseAndGetAddressOf();
	m_pBufSrv.ReleaseAndGetAddressOf();
	pUAVTexture.ReleaseAndGetAddressOf();
	pReadTexture.ReleaseAndGetAddressOf();
	pWriteTexture.ReleaseAndGetAddressOf();

	m_pUAV.ReleaseAndGetAddressOf();
	m_pReadSrv.ReleaseAndGetAddressOf();
	m_pDescSrv.ReleaseAndGetAddressOf();
	return false;
}
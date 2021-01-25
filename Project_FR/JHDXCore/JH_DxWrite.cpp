#include "JH_DxWrite.h"

bool JH_DxWrite::Set(HWND hWnd, int iWidth,
	int iHeight, IDXGISurface* pSurface)
{
	if (FAILED(CreateDeviceIndependentResources()))
	{
		return false;
	}
	if (FAILED(CreateDeviceResources(pSurface)))
	{
		return false;
	}
	return true;
}
HRESULT JH_DxWrite::CreateDeviceIndependentResources()
{
	HRESULT hr = S_OK;

	hr = D2D1CreateFactory(
		D2D1_FACTORY_TYPE_MULTI_THREADED,
		&m_pD2DFactory);

	m_pD2DFactory->GetDesktopDpi(&m_fdpiX, &m_fdpiY);
	m_fDPIScaleX = m_fdpiX / 96.0f;
	m_fDPIScaleY = m_fdpiY / 96.0f;

	hr = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		(IUnknown**)&m_pDWriteFactory);
	hr = m_pDWriteFactory->CreateTextFormat(
		L"°íµñ",
		NULL,
		DWRITE_FONT_WEIGHT_BOLD,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		30,
		L"ko-kr", // en-us
		&m_pTextFormat
	);
	return hr;
}
HRESULT JH_DxWrite::CreateDeviceResources(IDXGISurface* pSurface)
{
	HRESULT hr = S_OK;
	D2D1_RENDER_TARGET_PROPERTIES props;// = D2D1::RenderTargetProperties(
											//	D2D1_RENDER_TARGET_TYPE_DEFAULT,
											//	D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED),
											//	static_cast<float>(m_fdpiX),
											//	static_cast<float>(m_fdpiY) );

	props.type = D2D1_RENDER_TARGET_TYPE_DEFAULT;
	props.pixelFormat = D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED);
	props.dpiX = static_cast<float>(m_fdpiX);
	props.dpiY = static_cast<float>(m_fdpiY);
	props.usage = D2D1_RENDER_TARGET_USAGE_NONE;
	props.minLevel = D2D1_FEATURE_LEVEL_DEFAULT;


	//D3D11_CREATE_DEVICE_BGRA_SUPPORT
	hr = m_pD2DFactory->CreateDxgiSurfaceRenderTarget(
		pSurface, &props, &m_pRT
	);

	m_pRT->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0, 1), &m_pBlackBrush);


	return hr;
}
bool JH_DxWrite::Release()
{
	DiscardDeviceResources();

	m_pTextFormat->Release();
	m_pDWriteFactory->Release();
	m_pD2DFactory->Release();
	return true;
}
bool JH_DxWrite::DiscardDeviceResources()
{
	m_pBlackBrush->Release();
	m_pRT->Release();
	return true;
}
bool JH_DxWrite::Begin() {
	if (m_pRT)
	{
		m_pRT->BeginDraw();
		//D2D1_POINT_2F center;
		//center.x = 0;
		//center.y = 0;
		//D2D1::Matrix3x2F matScale = D2D1::Matrix3x2F::Identity();
		//matScale._11 = 3.5f;
		//matScale._22 = 3.5f;
		//D2D1::Matrix3x2F matRotation = D2D1::Matrix3x2F::Rotation(35, center);
		D2D1::Matrix3x2F matWorld = D2D1::Matrix3x2F::Identity();
		m_pRT->SetTransform(matWorld);
	}
	return true;
}
bool JH_DxWrite::DrawText(RECT rt,
	const TCHAR* pText,
	D2D1::ColorF color)
{
	D2D_RECT_F layoutRect;
	layoutRect.top = static_cast<FLOAT>(rt.top) / m_fDPIScaleX;
	layoutRect.left = static_cast<FLOAT>(rt.left) / m_fDPIScaleY;
	layoutRect.right = static_cast<FLOAT>(rt.right) / m_fDPIScaleX;
	layoutRect.bottom = static_cast<FLOAT>(rt.bottom) / m_fDPIScaleY;
	m_pBlackBrush->SetColor(color);

	m_pRT->DrawText(pText, wcslen(pText),
		m_pTextFormat, layoutRect, m_pBlackBrush);
	return true;
}
void JH_DxWrite::Add(const TCHAR* pMsg,
	D2D1::ColorF color,
	RECT rt)
{
	tMsg item;
	item.msg = pMsg;
	item.color = color;
	item.rt = rt;

	if (m_textList.size() > 3)
	{
		m_textList.pop_front();
	}
	m_textList.push_back(item);
}

bool JH_DxWrite::Render()
{
	Begin();
	int iTop = 0;
	for (auto& item : m_textList)
	{
		D2D1::ColorF color(item.color.r, item.color.g, item.color.b, item.color.a);
		item.rt.top = iTop++ * 30;
		DrawText(item.rt,
			item.msg.c_str(),
			color);
	}
	End();
	return true;
}
bool JH_DxWrite::End()
{
	if (m_pRT)
	{
		m_pRT->EndDraw();
		m_textList.clear();
	}
	return true;
}
void JH_DxWrite::OnResize(UINT with, UINT height,
	IDXGISurface* pSurface)
{
	DiscardDeviceResources();
	CreateDeviceResources(pSurface);
}
JH_DxWrite::JH_DxWrite()
{
}


JH_DxWrite::~JH_DxWrite()
{
}

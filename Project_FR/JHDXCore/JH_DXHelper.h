	
#pragma once
#include <d3d11.h>
#include <dxgi.h>
#include <d3dcompiler.h>
#include <d3dx11.h> // sdk
#include <D3DX10Math.h> // D3DXMatrixLookAtLH 외부 기호
#include <wrl.h>
#include <memory>

using namespace std;
using namespace Microsoft::WRL;
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#if defined(_DEBUG)
#pragma comment(lib, "d3dx11d.lib")
#pragma comment(lib, "d3dx10d.lib")
#else
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")
#endif
class JH_DxHelper
{
public:
public:
	JH_DxHelper() {};
	~JH_DxHelper() {};

};
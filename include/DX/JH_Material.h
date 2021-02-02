#pragma once
#include"JH_DXStd.h"
#include"TextureMgr.h"
class JH_Obj;
struct CB_MT
{
	D3DXVECTOR4 AmbientColor;
	D3DXVECTOR4 DiffuseColor;
	D3DXVECTOR4 SpecularColor;
	D3DXVECTOR4 EmissiveColor;
};
class JH_Material
{
	friend class JH_Model;
public:
	std::wstring Name;

	D3DXVECTOR4 AmbientColor;
	D3DXVECTOR4 DiffuseColor;
	D3DXVECTOR4 SpecularColor;
	D3DXVECTOR4 EmissiveColor;

	std::wstring Diffuse;
	std::wstring Specular;
	std::wstring Emissive;
	std::wstring Normal;

	ComPtr<ID3D11Buffer> m_CB;
	CB_MT				 m_CBMT;


public:
	bool Init();
	bool Render();

};


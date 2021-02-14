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
	inline std::wstring& GetDiffues() { return Diffuse; }
	inline std::wstring& GetSpecular() { return Specular; }
	inline std::wstring& GetEmissive() { return Emissive; }
	inline std::wstring& GetNormal() { return Normal; }

	inline void SetDiffues(std::wstring&& str) {  Diffuse=str; }
	inline void SetSpecular(std::wstring&& str) {  Specular = str; }
	inline void SetEmissive(std::wstring&& str) {  Emissive = str; }
	inline void SetNormal(std::wstring&& str) {  Normal = str; }

public:
	bool Init();
	bool Render();

};


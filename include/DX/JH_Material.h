#pragma once
#include"JH_DXStd.h"
class JH_Material
{
public:
	std::string Name;

	D3DXVECTOR4 AmbientColor;
	D3DXVECTOR4 DiffuseColor;
	D3DXVECTOR4 SpecularColor;
	D3DXVECTOR4 EmissiveColor;

	std::string Diffuse;
	std::string Specular;
	std::string Emissive;
	std::string Normal;
};


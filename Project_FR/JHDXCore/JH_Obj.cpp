#pragma once
#include "JH_Obj.h"
HRESULT JH_Obj::CreateVertexData()
{
	m_dxHelper.m_iVertexSize = sizeof(PNCTIW_VERTEX);
	return S_OK;
}
HRESULT JH_Obj::CreateIndexData()
{
	
	return S_OK;
}
JH_Obj::JH_Obj()
{

}
JH_Obj::~JH_Obj()
{

}

bool JH_Obj::ReadFile(const std::string file)
{
	BinaryReader Reader;

	std::string FullPath="../../data/model/binary/"+file+".md";
	Reader.Open(file);

	m_materials.resize(Reader.Int());

	if (m_materials.size() > 0)
	{
		for (int i = 0; i < m_materials.size(); i++)
		{
			JH_Material& tMat=m_materials[i];

			tMat.Name=Reader.String();
			Reader.Byte(&tMat.AmbientColor, sizeof(D3DXVECTOR4), 1);
			Reader.Byte(&tMat.DiffuseColor, sizeof(D3DXVECTOR4), 1);
			Reader.Byte(&tMat.SpecularColor, sizeof(D3DXVECTOR4), 1);
			Reader.Byte(&tMat.EmissiveColor, sizeof(D3DXVECTOR4), 1);

			tMat.Diffuse = Reader.String();
			tMat.Specular = Reader.String();
			tMat.Emissive = Reader.String();
			tMat.Normal = Reader.String();

		}
	}

	return true;
}

bool JH_Obj::Init()
{
	return true;
}
bool JH_Obj::Frame()
{
	return true;
}
bool JH_Obj::Render()
{
	return true;
}
bool JH_Obj::Release()
{
	return true;
}
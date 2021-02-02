#pragma once
#include "JH_Obj.h"


bool JH_Obj::ReadFile(const std::string file)
{
	BinaryReader Reader;

	std::string FullPath="../../data/model/binary/"+file+".md";
	Reader.Open(FullPath);

	m_materials.resize(Reader.Int());

	if (m_materials.size() > 0)
	{
		for (int i = 0; i < m_materials.size(); i++)
		{
			JH_Material& tMat=m_materials[i];

			tMat.Name=Reader.WString();
			Reader.Byte(&tMat.AmbientColor, sizeof(D3DXVECTOR4), 1);
			Reader.Byte(&tMat.DiffuseColor, sizeof(D3DXVECTOR4), 1);
			Reader.Byte(&tMat.SpecularColor, sizeof(D3DXVECTOR4), 1);
			Reader.Byte(&tMat.EmissiveColor, sizeof(D3DXVECTOR4), 1);

			tMat.Diffuse = Reader.WString();
			tMat.Specular = Reader.WString();
			tMat.Emissive = Reader.WString();
			tMat.Normal = Reader.WString();

		}
	}
	m_Bones.resize(Reader.Int());
	if (m_Bones.size() > 0)
	{
		for (int i = 0; i < m_Bones.size(); i++)
		{
			JH_Bone& tBone = m_Bones[i];

			tBone.SetBoneName(Reader.WString());
			tBone.SetBoneIndex(Reader.Int());
			tBone.SetParentIndex(Reader.Int());
			Reader.Byte(tBone.GetWorld(), sizeof(D3DXMATRIX), 1);
		}
	}

	if (m_meshes.size() > 0)
	{
		for (int i = 0; i < m_Bones.size(); i++)
		{
			JH_Bone& tBone = m_Bones[i];

			tBone.SetBoneName(Reader.WString());
			tBone.SetBoneIndex(Reader.Int());
			tBone.SetParentIndex(Reader.Int());
			Reader.Byte(tBone.GetWorld(), sizeof(D3DXMATRIX), 1);
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
	UINT offset = 0;
	UINT Stride = 0;
	m_dxHelper.PreRender();
	for (auto mesh : m_meshes)
	{
		mesh.Render(m_dxHelper.GetDeviceContext());
	}
	return true;
}
bool JH_Obj::Release()
{
	return true;
}

void JH_Obj::BindingMesh()
{
	for (auto mesh : m_meshes)
	{
		mesh.Binding(this);
	}
}
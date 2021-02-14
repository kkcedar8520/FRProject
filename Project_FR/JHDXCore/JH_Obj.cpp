//#pragma once
//#include "JH_Obj.h"
//
//
//bool JH_Obj::ReadFile(const std::string file)
//{
//	BinaryReader Reader;
//
//	std::string FullPath="../../data/model/binary/"+file+".md";
//	Reader.Open(FullPath);
//
//	m_materials.resize(Reader.Int());
//
//	if (m_materials.size() > 0)
//	{
//		for (int i = 0; i < m_materials.size(); i++)
//		{
//			JH_Material& tMat=m_materials[i];
//
//			tMat.Name=Reader.WString();
//			Reader.Byte(&tMat.AmbientColor, sizeof(D3DXVECTOR4), 1);
//			Reader.Byte(&tMat.DiffuseColor, sizeof(D3DXVECTOR4), 1);
//			Reader.Byte(&tMat.SpecularColor, sizeof(D3DXVECTOR4), 1);
//			Reader.Byte(&tMat.EmissiveColor, sizeof(D3DXVECTOR4), 1);
//
//			tMat.SetDiffues(Reader.WString());
//			tMat.SetSpecular(Reader.WString());
//			tMat.SetEmissive(Reader.WString());
//			tMat.SetNormal(Reader.WString());
//
//		}
//	}
//	m_Bones.resize(Reader.Int());
//	if (m_Bones.size() > 0)
//	{
//		for (int i = 0; i < m_Bones.size(); i++)
//		{
//			JH_Bone& tBone = m_Bones[i];
//
//			tBone.SetBoneName(Reader.WString());
//			tBone.SetBoneIndex(Reader.Int());
//			tBone.SetParentIndex(Reader.Int());
//			Reader.Byte(tBone.GetWorld(), sizeof(D3DXMATRIX), 1);
//		}
//	}
//
//	m_meshes.resize(Reader.Int());
//	if (m_meshes.size() > 0)
//	{
//		for (int i = 0; i < m_meshes.size(); i++)
//		{
//			JH_Mesh& tMesh = m_meshes[i];
//
//			tMesh.SetName(Reader.WString());
//			tMesh.SetParentIndex(Reader.Int());
//
//			tMesh.SetMatrerialName(Reader.WString());
//			tMesh.GetVertexData().resize(Reader.Int());
//			Reader.Byte(&tMesh.GetVertexData()[0], sizeof(PNCTIW_VERTEX),tMesh.GetVertexData().size());
//			tMesh.GetIndexData().resize(Reader.Int());
//			Reader.Byte(&tMesh.GetIndexData()[0], sizeof(DWORD), tMesh.GetIndexData().size());
//
//			
//		}
//	}
//	BindingMesh();
//	Reader.Close();
//	return true;
//}
//
//bool JH_Obj::Init()
//{
//	return true;
//}
//bool JH_Obj::Frame()
//{
//	return true;
//}
//bool JH_Obj::Render()
//{
//	UINT offset = 0;
//	UINT Stride = 0;
//	for (auto mesh : m_meshes)
//	{
//		//mesh.Render(m_dxHelper.GetDeviceContext());
//	}
//	return true;
//}
//bool JH_Obj::Release()
//{
//	return true;
//}
//
//void JH_Obj::BindingMesh()
//{
//	for (auto& mesh : m_meshes)
//	{
//		mesh.Binding(this);
//	}
//}
//
//
//
//JH_Material& JH_Obj::MaterialFindByName(std::wstring Name)
//{
//	for (auto& Mat:m_materials )
//	{
//		if (Mat.Name == Name)
//		{
//			return Mat;
//		}
//	}
//}
//JH_Material& JH_Obj::MaterialFindByIndex(int  id)
//{
//	return m_materials[id];
//}
//
//JH_Bone& JH_Obj::BoneFindByName(std::wstring Name)
//{
//	for (auto Bone : m_Bones)
//	{
//		if (Bone.GetBoneName() == Name)
//		{
//			return Bone;
//		}
//	}
//}
////JH_Bone& JH_Obj::BoneFindByIndex(std::wstring Name)
////{
////
////}
////
////JH_Mesh& JH_Obj::MeshFindByName(std::wstring Name)
////{
////
////}
////JH_Mesh& JH_Obj::MeshFindByIndex(std::wstring Name)
////{
////
////
////}
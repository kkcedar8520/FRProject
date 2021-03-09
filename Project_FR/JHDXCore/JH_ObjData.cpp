#include "JH_ObjData.h"
bool JH_ObjData::ReadFile(const std::string file)
{
	BinaryReader Reader;

	std::string FullPath = "../../data/model/binary/" + file + ".md";
	if (!Reader.Open(FullPath)) { return false; }

	m_Name = file;
	m_materials.resize(Reader.Int());

	if (m_materials.size() > 0)
	{
		for (int i = 0; i < m_materials.size(); ++i)
		{
			JH_Material& tMat = m_materials[i];

			tMat.Name = Reader.WString();
			Reader.Byte(&tMat.AmbientColor, sizeof(D3DXVECTOR4), 1);
			Reader.Byte(&tMat.DiffuseColor, sizeof(D3DXVECTOR4), 1);
			Reader.Byte(&tMat.SpecularColor, sizeof(D3DXVECTOR4), 1);
			Reader.Byte(&tMat.EmissiveColor, sizeof(D3DXVECTOR4), 1);

			tMat.SetDiffues(Reader.WString());
			tMat.SetSpecular(Reader.WString());
			tMat.SetEmissive(Reader.WString());
			tMat.SetNormal(Reader.WString());

		}
	}
	m_Bones.resize(Reader.Int());
	if (m_Bones.size() > 0)
	{
		for (int i = 0; i < m_Bones.size(); ++i)
		{
			JH_Bone& tBone = m_Bones[i];

			tBone.SetBoneName(Reader.WString());
			tBone.SetBoneIndex(Reader.Int());
			tBone.SetParentIndex(Reader.Int());
			Reader.Byte(tBone.GetWorld(), sizeof(D3DXMATRIX), 1);
		}
	}

	m_meshes.resize(Reader.Int());
	if (m_meshes.size() > 0)
	{
		for (int i = 0; i < m_meshes.size(); ++i)
		{
			JH_Mesh& tMesh = m_meshes[i];

			tMesh.SetName(Reader.WString());
			tMesh.SetBoneIndex(Reader.Int());

			tMesh.SetMatrerialName(Reader.WString());
			tMesh.GetVertexData().resize(Reader.Int());
			Reader.Byte(&tMesh.GetVertexData()[0], sizeof(PNCTIW_VERTEX), tMesh.GetVertexData().size());
			tMesh.GetIndexData().resize(Reader.Int());
			Reader.Byte(&tMesh.GetIndexData().at(0), sizeof(DWORD), tMesh.GetIndexData().size());

		}
	}
	Reader.Close();



	return true;
}
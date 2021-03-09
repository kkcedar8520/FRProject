#pragma once
#include"JH_Mesh.h"
#include"BinaryReader.h"
class JH_ObjData
{
	
public:
	std::string									m_Name;
	std::vector<JH_Mesh>			m_meshes;
	std::vector<JH_Material>		m_materials;
	std::vector<JH_Bone>			m_Bones;
public:
	bool ReadFile(const std::string file);
public:
	std::string GetName() { return m_Name; }
	std::vector<JH_Material>& GetMaterial() { return m_materials; }
	std::vector<JH_Mesh>& GetMesh() { return m_meshes; }
	std::vector<JH_Bone>& GetBone() { return m_Bones; }
};


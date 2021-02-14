#pragma once
#include"JH_Mesh.h"
#include"JH_Material.h"
#include"BinaryReader.h"
struct SCENEINFO
{
	int FirstFrame;
	int LastFrame;
	int FrameSpeed;
	int TickPerFrame;
	int iNumMesh;		// 메쉬오브젝트 개수
	int iNumMaterial;   // 루트매터리얼 개수
	int iMaxWeight;		// 정점 당 가중치
	int iBindPose;		// 바인딩 포즈 에니메이션 여부
};
//struct Material
//{
//	std::string Name;
//
//	D3DXVECTOR4 AmbientColor;
//	D3DXVECTOR4 DiffuseColor;
//	D3DXVECTOR4 SpecularColor;
//	D3DXVECTOR4 EmissiveColor;
//
//	std::string Diffuse;
//	std::string Specular;
//	std::string Emissive;
//	std::string Normal;
//};
//struct Bone
//{
//	std::wstring BoneName;
//
//	INT iBoneIndex;
//	INT iBoneParentIndex;
//
//	D3DXMATRIX m_Matworld;
//};
class JH_Obj 
{
private:

	SCENEINFO m_Scene;

	std::vector<JH_Mesh> m_meshes;
	std::vector<JH_Material>m_materials;
	std::vector<std::shared_ptr<JH_Bone>>m_Bones;
public:
	//Data
	//std::vector<JH_Material>& GetMaterial() { return m_materials; }
	//std::vector<JH_Mesh>& GetMesh() { return m_meshes; }
	//std::vector<JH_Bone>& GetBone() { return m_Bones; }

	bool ReadFile(const std::string file);
	void BindingMesh();
public:
	JH_Material& MaterialFindByName(std::wstring Name);
	JH_Material& MaterialFindByIndex(int  id);

	JH_Bone& BoneFindByName(std::wstring Name);
	JH_Bone& BoneFindByIndex(int  id);

	JH_Mesh& MeshFindByName(std::wstring Name);
	JH_Mesh& MeshFindByIndex(int  id);

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();

};


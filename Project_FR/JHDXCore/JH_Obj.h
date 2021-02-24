#pragma once
#include"JH_Mesh.h"
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
class JH_Obj 
{
private:

	SCENEINFO m_Scene;

	std::vector<JH_Mesh>			m_meshes;
	std::vector<JH_Material>		m_materials;
	std::vector<JH_Bone>			m_Bones;
		
	CB_TF							m_sCBTF;
	ComPtr<ID3D11Buffer>			m_CBTF;

	D3DXMATRIX						m_matWorld;
	D3DXMATRIX						m_matView;
	D3DXMATRIX						m_matProj;
	D3DXMATRIX						m_matNormal;
	
	//Colider
	JH_Box							m_ColiderBox;
public:

	//Data
	std::vector<JH_Material>& GetMaterial() { return m_materials; }
	std::vector<JH_Mesh>& GetMesh() { return m_meshes; }
	std::vector<JH_Bone>& GetBone() { return m_Bones; }
	//
	D3DXMATRIX& GetTransform() { return m_matWorld; }

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
	void SetTransform(D3DXMATRIX*  world =nullptr, D3DXMATRIX*  View=nullptr, D3DXMATRIX*  Proj=nullptr);
	void UpdateTarnsformCB();
	void CreateTransformCB();
public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
public:
	JH_Obj();
	virtual ~JH_Obj();
};


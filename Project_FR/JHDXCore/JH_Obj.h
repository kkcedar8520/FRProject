#pragma once

#include"JHCamera.h"
#include"JH_ColliderBox.h"
#include"JH_ObjData.h"
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
class JH_Obj :public JH_Model
{
public:
	bool bColider = false;
private:

	SCENEINFO m_Scene;
	int m_ID;


	std::string						m_Name;


	//D3DXMATRIX						m_matTransform;
//D3DXMATRIX						m_matWorld;
//D3DXMATRIX						m_matView;
//D3DXMATRIX						m_matProj;
//D3DXMATRIX						m_matNormal;
	CB_TF							m_sCBTF;
	ComPtr<ID3D11Buffer>			m_CBTF;

	//MeshBoneMatarial
	JH_ObjData*						m_ObjData;
	
	//Colider
	JH_ColliderBox					m_ColiderBox;
	//Camera
	JHCamera*						m_pCamera;
public:

	//Data
	std::vector<JH_Material>& GetMaterial() { return m_ObjData->GetMaterial(); }
	std::vector<JH_Mesh>& GetMesh() { return m_ObjData->GetMesh(); }
	std::vector<JH_Bone>& GetBone() { return m_ObjData->GetBone(); }
	//Name
	std::string& GetName() { return m_Name; }
	//Setting
	D3DXMATRIX& GetTransform() { return m_matTransform; }
	int			GetID() { return m_ID; }
	void		SetID(int ID) { m_ID=ID; }
	//
	void		SetCamera(JHCamera* Camera) { m_pCamera = Camera; }
	JHCamera*	GetCamera()					{ return m_pCamera; }
	//
	void			CreateColiderBox(D3DXMATRIX& mat);
	JH_ColliderBox& GetColliderBox() { return m_ColiderBox; }
public:
	//Craete
	bool ReadFile(const std::string file);
	void BindingMesh();
	void InitMaterial();
public:
	JH_Material* MaterialFindByName(std::wstring Name);
	JH_Material* MaterialFindByIndex(int  id);

	JH_Bone* BoneFindByName(std::wstring Name);
	JH_Bone* BoneFindByIndex(int  id);

	JH_Mesh* MeshFindByName(std::wstring Name);
	JH_Mesh *MeshFindByIndex(int  id);
public:
	
	
	void SetMatrix(D3DXMATRIX* matWorld = nullptr, D3DXMATRIX* matView = nullptr, D3DXMATRIX* matProj = nullptr)override;
	void SetTransform(D3DXMATRIX& Mat)override;
	void SetPos(D3DXVECTOR3 vPos)override;
	void SetScale(D3DXVECTOR3 vScale)override;
	void SetRotation(D3DXMATRIX Mat)override;
	void UpdateTarnsformCB();
	void CreateTransformCB();
	void RenderCollider();
public:
	 bool Init()override;
	 bool Frame()override;
	 bool Render()override;
	 bool Release()override;
public:
	JH_Obj();
	virtual ~JH_Obj();
};


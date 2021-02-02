
#pragma once
#include"JHDXCore.h"
#include"JH_Bone.h"
#include"JH_Material.h"

class JH_Obj;
struct AnimTrack
{
	int iTick;
	D3DXVECTOR3		p;
	D3DXQUATERNION	q;
};

class JH_Mesh
{
	
private:
	C_STR		m_szName;
	C_STR		m_szParentName;
	C_STR		m_MaterialName;

	UINT		m_iTexIndex;
	UINT        m_iBaseVertex;
	UINT        m_iNumVertex;
	int			m_iParentIndex;

	

	D3DXMATRIX  m_matWorld;

	vector<PNCTIW_VERTEX>	m_VertexData;
	vector<int>				m_IndicesData;

	ComPtr<ID3D11Buffer> m_pVB;
	ComPtr<ID3D11Buffer> m_pIB;

	UINT					m_iVertexSize;

	//std::vector<PNCTIW_VERTEX> m_PNCTIWlist;
	CB_DATA     m_cbData;
private:
	//BONE
	JH_Bone m_Bone;
	//Material
	JH_Material m_Material;

public:
	//Interface

	ID3D11Buffer** GetVertexBuffer() {return  m_pVB.GetAddressOf(); }
	ID3D11Buffer* GetIndexBuffer() { return  m_pIB.Get(); }

	vector<PNCTIW_VERTEX>& GetVertexData() { return  m_VertexData; }
	vector<int>& GetIndexData() { return  m_IndicesData; }

	UINT			   GetVertexSize() { return m_iVertexSize; }
public:
	void Binding(JH_Obj* Obj);
	bool Init();
	bool Frame();
	bool Render(ID3D11DeviceContext* pContext);
	bool Release();
public:
	JH_Mesh();
	~JH_Mesh();
};
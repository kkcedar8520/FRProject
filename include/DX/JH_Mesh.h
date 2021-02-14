
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

class JH_Mesh :public JH_Model
{
	
private:
	std::wstring		m_szName;
	std::wstring		m_szParentName;
	std::wstring		m_MaterialName;

	UINT				m_iTexIndex;
	UINT				m_iBaseVertex;
	UINT				m_iNumVertex;
	int					m_iParentIndex;

	

	D3DXMATRIX				m_matWorld;

	//vector<PNCTIW_VERTEX>	m_VertexData;
	//vector<int>				m_IndicesData;

	ComPtr<ID3D11Buffer>	m_pVB;
	ComPtr<ID3D11Buffer>	m_pIB;

	UINT					m_iVertexSize;

	//std::vector<PNCTIW_VERTEX> m_PNCTIWlist;
	CB_DATA					m_cbData;
private:
	//BONE
	JH_Bone m_Bone;
	//Material
	JH_Material m_Material;

public:
	//Interface

	ID3D11Buffer**			GetVertexBuffer()	{return  m_pVB.GetAddressOf(); }
	ID3D11Buffer*			GetIndexBuffer()	{return  m_pIB.Get(); }

	vector<PNCTIW_VERTEX>&	GetVertexData()		{return  m_VertexData; }
	vector<DWORD>&			GetIndexData()		{return  m_IndexData; }

	UINT					GetVertexSize()		{return  m_iVertexSize; }
public:
	void SetName(std::wstring&& str)			{ m_szName = str; }
	void SetParentName(std::wstring&& str)		{ m_szParentName = str; }
	void SetParentIndex(int&& id)				{ m_iParentIndex = id; }
	void SetMatrerialName(std::wstring&& str)	{ m_MaterialName = str;}
	void SetWorld(D3DXMATRIX&& Mat)				{ m_matWorld = Mat; }
public:
	void Binding(JH_Obj* Obj);
	bool Init()override;
	bool Frame()override;
	bool Render()override;
	bool Release()override;

	HRESULT CreateVertexData()override;
	HRESULT CreateIndexData()override;

public:
	JH_Mesh();
	~JH_Mesh();
};
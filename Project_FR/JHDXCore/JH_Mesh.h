
#pragma once
#include"JHDXCore.h"
#include"TextureMgr.h"
#include"JH_Model.h"
#include"JH_Bone.h"
struct AnimTrack
{
	int iTick;
	D3DXVECTOR3		p;
	D3DXQUATERNION	q;
};

class JH_Mesh:public JH_Model
{
public:
	C_STR		m_szName;
	C_STR		m_szParentName;
	C_STR		m_MaterialName;

	UINT		m_iTexIndex;
	UINT        m_iBaseVertex;
	UINT        m_iNumVertex;
	int			m_iParentIndex;


	D3DXMATRIX  m_matWorld;
	D3DXMATRIX	m_matInverseWorld;
	D3DXMATRIX  m_matCalculation;

	D3DXVECTOR3		m_vAnimScale;
	D3DXQUATERNION  m_qAnimScaleRotation;
	D3DXQUATERNION  m_qAnimRotation;
	D3DXVECTOR3		m_vAnimPos;


	Texture*	m_pTexture;
	vector<JH_Mesh> subMesh;


	vector<AnimTrack> m_AnimTrackPos;
	vector<AnimTrack> m_AnimTrackRotate;
	vector<AnimTrack> m_AnimTrackScale;

	//std::vector<PNCTIW_VERTEX> m_PNCTIWlist;
	CB_DATA     m_cbData;
public:
	//BONE
	JH_Bone m_Bone;
public:
	JH_Mesh();
	~JH_Mesh();
};